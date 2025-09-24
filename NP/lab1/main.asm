; ------------------------------------------------------------------------------
; ���������� ������� ������� �� ���������� Kernel32.dll, ������� �� ����� ������������.
; ------------------------------------------------------------------------------
EXTERN GetStdHandle: PROC
EXTERN WriteConsoleA: PROC
EXTERN ReadConsoleA: PROC
EXTERN ExitProcess: PROC
EXTERN SetConsoleCP: PROC
EXTERN SetConsoleOutputCP: PROC

; ==============================================================================
; ������ .DATA: ����� ����������� ��� ������������������ � ��������������������
; ���������� ���������� � ���������.
; ==============================================================================
.DATA
    ; --- ����������� ����������� ������� ---
    std_input_handle    QWORD ? ; ���������� ��� �������� ����������� ������� ��� �����.
    std_output_handle   QWORD ? ; ���������� ��� �������� ����������� ������� ��� ������.
    ; --- ������������ �������� ---
    coeff_a             DQ 4
    coeff_b             DQ 19
    coeff_c             DQ -2
    ; --- ���������� ��� �������� ����� ---
    input_x             DQ ?
    result_y            DQ ?
    ; --- ������ ��� �������������� � ������������� ---
    msg_prompt_x        DB "������� ����������������� ����� x: ", 0
    msg_x_dec           DB 13, 10, "��������� ����� x � ���������� �������: ", 0
    msg_y_oct           DB 13, 10, "��������� y � ������������ �������: ", 0
    msg_y_dec           DB 13, 10, "��������� y � ���������� �������: ", 0
    msg_newline         DB 13, 10, 0 ; ������ ��� �������� �������. 13=CR, 10=LF.
    ; --- ������ � ��������������� ���������� ---
    BUFFER_SIZE         EQU 256
    input_buffer        DB BUFFER_SIZE DUP(?) ; ����� ��� ������ ������ � ����������.
    output_buffer       DB BUFFER_SIZE DUP(?) ; ����� ��� �������������� ����� � ������ ��� ������.
    ; --- ��������������� ���������� ��� ������ ������
    chars_read          DD ?    ; DWORD (32 ����) � ������������ � API
    chars_written       DD ?    ; DWORD (32 ����) � ������������ � API

; ==============================================================================
; ������ .CODE: ����� ��������� ����������� ��� ���������.
; ==============================================================================
.CODE

; ------------------------------------------------------------------------------
; ������� ��������� ��������� (����� �����).
; ------------------------------------------------------------------------------
main PROC
    ; ������: �������� 40 ���� �� �����. 32 ����� - ��� "������� ������������",
    ; ������������ �� ���������� � ������� x64, ���� 8 ��� ������������.
    sub rsp, 40 
    ; --- ���� 1: ������������� ����� ---
    ; ������������� ������� �������� 1251 ��� ���������� ������ � ����������.
    mov rcx, 1251           ; �������� 1: ID ������� �������� (1251 ��� Windows Cyrillic)
    call SetConsoleCP       ; ������������� ��������� ��� �����.
    mov rcx, 1251
    call SetConsoleOutputCP ; ������������� ��������� ��� ������.
    ; �������� ���������� ������������ ������ ������ (�����).
    mov rcx, -11                 ; �������� 1: -11 ��� ��������� STD_OUTPUT_HANDLE.
    call GetStdHandle
    mov [std_output_handle], rax ; ��������� ���������� ����������.
    ; �������� ���������� ������������ ������ ����� (����������).
    mov rcx, -10 ; �������� 1: -10 ��� ��������� STD_INPUT_HANDLE.
    call GetStdHandle
    mov [std_input_handle], rax ; ��������� ����������.
    ; --- ���� 2: ���� � �������������� ����� X ---
    ; ������� ����������� � �����.
    lea rdx, msg_prompt_x ; �������� 1 (RDX): ����� ������ ��� ������.
    call PrintString
    ; ������ ������ � ����������.
    lea rdx, input_buffer ; �������� 1 (RDX): ����� ������ ��� ���������� ������.
    call ReadString
    ; ����������� 16-������ ������ � 64-������ �����.
    lea rcx, input_buffer ; �������� 1 (RCX): ����� ������ ��� ��������������.
    call HexStrToInt64
    mov [input_x], rax ; ��������� ��������� (�� RAX) � ����������.
    ; --- ���� 3: ����� ����������� ---
    lea rdx, msg_x_dec ; ������� X � ���������� �������.
    call PrintString 
    mov rcx, [input_x]     ; �������� 1: ����� ��� ��������������.
    lea rdx, output_buffer ; �������� 2: ����� ��� ����������.
    mov r8, 10             ; �������� 3: ��������� ������� ��������� (10).
    call Int64ToStr
    lea rdx, output_buffer ; ��������� ����� ���������� ������ � RDX.
    call PrintString       ; ��������.
    ; --- ���� 4: ���������� �������� Y ---
    mov rax, [input_x] ; rax = x
    mov rbx, [input_x] ; rbx = x
    imul rax, rbx      ; rax = x * x (x^2)
    imul rax, [coeff_a] ; rax = rax * a (a*x^2)
    mov rbx, [input_x]  ; rbx = x
    imul rbx, [coeff_b] ; rbx = rbx * b (b*x)
    add rax, rbx        ; rax = a*x^2 + b*x
    add rax, [coeff_c]  ; rax = a*x^2 + b*x + c
    mov [result_y], rax ; ��������� ��������� ��������� � ���������� Y.
    ; ������� Y � ������������ �������. 
    lea rdx, msg_y_oct
    call PrintString
    mov rcx, [result_y]     ; �������� 1: ����� Y.
    lea rdx, output_buffer  ; �������� 2: ����� ��� ����������.
    mov r8, 8               ; �������� 3: ��������� ������� ��������� (8).
    call Int64ToStr
    lea rdx, output_buffer
    call PrintString
    ; ������� Y � ���������� �������.
    lea rdx, msg_y_dec
    call PrintString
    mov rcx, [result_y]      ; �������� 1: ����� Y.
    lea rdx, output_buffer   ; �������� 2: ����� ��� ����������.
    mov r8, 10               ; �������� 3: ��������� (10).
    call Int64ToStr
    lea rdx, output_buffer
    call PrintString
    ; --- ���� 5: ���������� ������ ---
    lea rdx, msg_newline
    call PrintString
    ; ��������� ��������� �������.
    mov rcx, 0 ; �������� 1: ��� �������� (0 = �����).
    call ExitProcess
main ENDP

; ------------------------------------------------------------------------------
; ���������: PrintString
; ����������: ����� �� ������� ������, ������������� �����.
; ����:       RDX = ����� ������.
; ------------------------------------------------------------------------------
PrintString PROC
    ; ��������� ��������, ������� ����� ���� �������� ������ ���������.
    push rbx
    ; �������� 40 ���� �� ����� ��� �������� ������������ � ������������.
    sub rsp, 40
    ; ���� ��� ����������� ����� ������.
    mov rbx, rdx  ; rbx - ��������� �� ������� ������.
    xor rcx, rcx  ; rcx - ������� �����.
strlen_loop:
    cmp byte ptr [rbx], 0 ; ���������, �� ����� �� ������.
    je strlen_end
    inc rbx
    inc rcx
    jmp strlen_loop
strlen_end:
    ; ���������� ���������� ��� ������ WriteConsoleA.
    mov r8, rcx                  ; �������� 3 (R8): ����� ������.
    mov rcx, [std_output_handle] ; �������� 1 (RCX): ���������� ������.
     ; RDX ��� �������� ����� ������ (�������� 2).
    lea r9, [chars_written]      ; �������� 4 (R9): ����� ���������� ��� ���-�� ���������� ����.
    mov qword ptr [rsp+32], 0    ; �������� 5 (�� �����): ��������������� (NULL).
    call WriteConsoleA
    ; ��������������� ���� � ��������.
    add rsp, 40
    pop rbx
    ret
PrintString ENDP

; ------------------------------------------------------------------------------
; ���������: ReadString
; ����������: ������ ������ � ����������.
; ����:       RDX = ����� ������ ��� ���������� ������.
; ------------------------------------------------------------------------------
ReadString PROC
    ; ��������� RBX, ��� ��� ��� ��������� �������, � �� ��� ����������.
    push rbx
    ; �������� 40 ���� �� ����� ��� �������� ������������ � ������������.
    sub rsp, 40
    ; ��������� ����� ������ (�� RDX) � ����������,
    ; ��������� ������� RBX, ������ ��� RDX ����� ��������� ������� ReadConsoleA.
    mov rbx, rdx
    ; ���������� ���������� ��� ������ ReadConsoleA.
    mov rcx, [std_input_handle] ; �������� 1 (RCX): ���������� �����.
    mov rdx, rbx                ; �������� 2 (RDX): ����� ������.
    mov r8, BUFFER_SIZE - 1     ; �������� 3 (R8): ������������ ���-�� �������� ��� ������.
    lea r9, [chars_read]        ; �������� 4 (R9): ����� ���������� ��� ���-�� ����������� ����.
    mov qword ptr [rsp+32], 0   ; �������� 5 (�� �����): ��������������� (NULL).
    call ReadConsoleA
    
    ; ������ 32-������ DWORD � EAX. RAX ������������� ���������� � ������� �����.
    mov eax, [chars_read]
    ; ��������� ����������� ������: ��������� ����-�����������
    cmp rax, 0                      ; ���� ������ �� ���������, �������.
    je done_reading
    mov byte ptr [rbx + rax], 0     ; ������ \0 � ����� ����� (�� ��������� ������).
    ; ������� ������� CR (\r) � LF (\n) �� ����� ������
    cmp rax, 2
    jl done_reading
    cmp byte ptr [rbx + rax - 2], 0Dh   
    jne done_reading
    cmp byte ptr [rbx + rax - 1], 0Ah 
    jne done_reading
    mov byte ptr [rbx + rax - 2], 0 ; �������� CR �� \0, ���������� ������.

done_reading:
    ; ��������������� ���� � �������.
    add rsp, 40
    pop rbx
    ret
ReadString ENDP

; ------------------------------------------------------------------------------
; ���������: Int64ToStr
; ����������: �������������� 64-������� ��������� ����� � ������.
; ����:       RCX = �����, RDX = ����� ��� ������, R8 = ��������� �������.
; ------------------------------------------------------------------------------
Int64ToStr PROC
    push rdi
    push rsi
    push rbx
    push rcx
    mov rdi, rdx    ; rdi = ��������� �� �����.
    mov rbx, r8     ; rbx = ���������.
    mov rax, rcx    ; rax = �����.
    xor rsi, rsi    ; rsi = ������� ����.
    cmp rax, 0      ; �������� ������������ ������, ���� ����� - ����.
    jne check_sign
    mov byte ptr [rdi], '0'
    inc rdi
    mov byte ptr [rdi], 0
    jmp end_conversion_final
check_sign:
    test rax, rax            ; ��������� ���� �����.
    jns conversion_loop      ; ���� �� �������������, ��������� � �����.
    mov byte ptr [rdi], '-'  ; �����, ������ ����� � ������ ������.
    inc rdi
    neg rax                  ; � ����������� �����.
conversion_loop:
    xor rdx, rdx             ; �������� RDX ����� ��������.
    div rbx                  ; rax = rax / rbx, rdx = �������.
    add dl, '0'              ; ����������� ������� (0-9) � ������ ('0'-'9').
    push rdx                 ; ��������� ������ ����� � �����.
    inc rsi                  ; ����������� ������� ����.
    cmp rax, 0               ; ���������, ���� ����� �� ������ �����.
    jne conversion_loop
pop_digits_loop:
    pop rax                  ; ��������� ����� �� ����� (��� ����� � �������� �������).
    mov [rdi], al            ; ���������� ������ � �����.
    inc rdi
    dec rsi                  ; ��������� �������.
    cmp rsi, 0
    jne pop_digits_loop
end_conversion_final:
    mov byte ptr [rdi], 0    ; ������ ����-���������� � ����� ������.
    pop rcx
    pop rbx
    pop rsi
    pop rdi
    ret
Int64ToStr ENDP

; ------------------------------------------------------------------------------
; ���������: HexStrToInt64
; ����������: �������������� 16-������ ������ � 64-������ �������� �����.
; ����:       RCX = ����� ������.
; �����:      RAX = ���������.
; ------------------------------------------------------------------------------
HexStrToInt64 PROC
    push rbx
    push rsi
    push rcx
    xor rax, rax                ; rax = ����������� ����������.
    mov rsi, rcx                ; rsi = ��������� �� ������� ������.
    xor rbx, rbx                ; rbx = ���� �������������� �����.
    cmp byte ptr [rsi], '-'     ; ��������� ������� ����� '-'.
    jne parse_loop
    mov rbx, 1                  ; ������������� ����.
    inc rsi                     ; ���������� ������ �����.
parse_loop:
    movzx rcx, byte ptr [rsi]   ; ������ ����-������ � RCX, ������� ������� ����.
    cmp cl, 0
    je parse_end
    ; ����������� ASCII-������ � �������� �������� (0-15).
    cmp cl, '9'
    jle is_digit
    cmp cl, 'F'
    jle is_upper_hex
    cmp cl, 'f'
    jle is_lower_hex
    jmp parse_end               ; ���� ������ ������������, ���������.
is_digit:
    sub cl, '0'
    jmp accumulate
is_upper_hex:
    sub cl, 'A' - 10
    jmp accumulate
is_lower_hex:
    sub cl, 'a' - 10
accumulate:
    shl rax, 4       ; �������� ����������� �� 16.
    add rax, rcx     ; ��������� �������� ����� �����.
    inc rsi          ; ��������� � ���������� �������.
    jmp parse_loop
parse_end:
    cmp rbx, 1       ; ���� ��� ���� �������������� �����...
    jne done
    neg rax          ; ...����������� ���������.
done:
    pop rcx
    pop rsi
    pop rbx
    ret
HexStrToInt64 ENDP

END