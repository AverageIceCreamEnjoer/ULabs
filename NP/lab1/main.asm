; ==============================================================================
; Ћабораторна€ работа є1, ¬ариант 5 (‘»ЌјЋ№Ќјя ¬≈–—»я 7.0)
; »справлена критическа€ ошибка несоответстви€ размеров данных (DD vs QWORD)
; ==============================================================================

EXTERN GetStdHandle: PROC
EXTERN WriteConsoleA: PROC
EXTERN ReadConsoleA: PROC
EXTERN ExitProcess: PROC
EXTERN SetConsoleCP: PROC
EXTERN SetConsoleOutputCP: PROC

.DATA
    std_input_handle    QWORD ?
    std_output_handle   QWORD ?
    coeff_a             DQ 4
    coeff_b             DQ 19
    coeff_c             DQ -2
    input_x             DQ ?
    result_y            DQ ?

    msg_prompt_x        DB "¬ведите шестнадцатеричное число x: ", 0
    msg_x_dec           DB 13, 10, "¬веденное число x в дес€тичной системе: ", 0
    msg_y_oct           DB 13, 10, "–езультат y в восьмеричной системе: ", 0
    msg_y_dec           DB 13, 10, "–езультат y в дес€тичной системе: ", 0
    msg_newline         DB 13, 10, 0

    BUFFER_SIZE         EQU 256
    input_buffer        DB BUFFER_SIZE DUP(?)
    output_buffer       DB BUFFER_SIZE DUP(?)
    chars_read          DD ?    ; DWORD (32 бита) в соответствии с API
    chars_written       DD ?    ; DWORD (32 бита) в соответствии с API

.CODE
main PROC
    sub rsp, 40 
    mov rcx, 1251
    call SetConsoleCP
    mov rcx, 1251
    call SetConsoleOutputCP
    
    mov rcx, -11 
    call GetStdHandle
    mov [std_output_handle], rax
    mov rcx, -10 
    call GetStdHandle
    mov [std_input_handle], rax

    lea rdx, msg_prompt_x
    call PrintString
    lea rdx, input_buffer
    call ReadString
    lea rcx, input_buffer
    call HexStrToInt64
    mov [input_x], rax

    lea rdx, msg_x_dec
    call PrintString
    mov rcx, [input_x]
    lea rdx, output_buffer
    mov r8, 10
    call Int64ToStr
    lea rdx, output_buffer
    call PrintString
    
    mov rax, [input_x]
    mov rbx, [input_x]
    imul rax, rbx
    imul rax, [coeff_a]
    mov rbx, [input_x]
    imul rbx, [coeff_b]
    add rax, rbx
    add rax, [coeff_c]
    mov [result_y], rax

    lea rdx, msg_y_oct
    call PrintString
    mov rcx, [result_y]
    lea rdx, output_buffer
    mov r8, 8
    call Int64ToStr
    lea rdx, output_buffer
    call PrintString

    lea rdx, msg_y_dec
    call PrintString
    mov rcx, [result_y]
    lea rdx, output_buffer
    mov r8, 10
    call Int64ToStr
    lea rdx, output_buffer
    call PrintString

    lea rdx, msg_newline
    call PrintString
    mov rcx, 0
    call ExitProcess
main ENDP

PrintString PROC
    push rbx
    sub rsp, 40
    
    mov rbx, rdx
    xor rcx, rcx
strlen_loop:
    cmp byte ptr [rbx], 0
    je strlen_end
    inc rbx
    inc rcx
    jmp strlen_loop
strlen_end:
    
    mov r8, rcx
    mov rcx, [std_output_handle]
    lea r9, [chars_written]
    mov qword ptr [rsp+32], 0
    call WriteConsoleA
    
    add rsp, 40
    pop rbx
    ret
PrintString ENDP

ReadString PROC
    push rbx
    sub rsp, 40

    mov rbx, rdx

    mov rcx, [std_input_handle]
    mov rdx, rbx
    mov r8, BUFFER_SIZE - 1
    lea r9, [chars_read]
    mov qword ptr [rsp+32], 0
    call ReadConsoleA
    
    ; <<< ‘»ЌјЋ№Ќќ≈ »—ѕ–ј¬Ћ≈Ќ»≈ «ƒ≈—№
    ; „итаем 32-битный DWORD в EAX. RAX автоматически обнул€етс€ в старших битах.
    mov eax, [chars_read]
    
    cmp rax, 0
    je done_reading
    mov byte ptr [rbx + rax], 0
    cmp rax, 2
    jl done_reading
    cmp byte ptr [rbx + rax - 2], 0Dh 
    jne done_reading
    cmp byte ptr [rbx + rax - 1], 0Ah 
    jne done_reading
    mov byte ptr [rbx + rax - 2], 0 

done_reading:
    add rsp, 40
    pop rbx
    ret
ReadString ENDP

Int64ToStr PROC
    push rdi
    push rsi
    push rbx
    push rcx
    mov rdi, rdx
    mov rbx, r8
    mov rax, rcx
    xor rsi, rsi
    cmp rax, 0
    jne check_sign
    mov byte ptr [rdi], '0'
    inc rdi
    mov byte ptr [rdi], 0
    jmp end_conversion_final
check_sign:
    test rax, rax
    jns conversion_loop
    mov byte ptr [rdi], '-'
    inc rdi
    neg rax
conversion_loop:
    xor rdx, rdx
    div rbx
    add dl, '0'
    push rdx
    inc rsi
    cmp rax, 0
    jne conversion_loop
pop_digits_loop:
    pop rax
    mov [rdi], al
    inc rdi
    dec rsi
    cmp rsi, 0
    jne pop_digits_loop
end_conversion_final:
    mov byte ptr [rdi], 0
    pop rcx
    pop rbx
    pop rsi
    pop rdi
    ret
Int64ToStr ENDP

HexStrToInt64 PROC
    push rbx
    push rsi
    push rcx
    xor rax, rax
    mov rsi, rcx
    xor rbx, rbx
    cmp byte ptr [rsi], '-'
    jne parse_loop
    mov rbx, 1
    inc rsi
parse_loop:
    movzx rcx, byte ptr [rsi]
    cmp cl, 0
    je parse_end
    cmp cl, '9'
    jle is_digit
    cmp cl, 'F'
    jle is_upper_hex
    cmp cl, 'f'
    jle is_lower_hex
    jmp parse_end
is_digit:
    sub cl, '0'
    jmp accumulate
is_upper_hex:
    sub cl, 'A' - 10
    jmp accumulate
is_lower_hex:
    sub cl, 'a' - 10
accumulate:
    shl rax, 4
    add rax, rcx 
    inc rsi
    jmp parse_loop
parse_end:
    cmp rbx, 1
    jne done
    neg rax
done:
    pop rcx
    pop rsi
    pop rbx
    ret
HexStrToInt64 ENDP

END