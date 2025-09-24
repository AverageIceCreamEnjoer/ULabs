; ==============================================================================
; Лабораторная работа №1, Вариант 5
; Архитектура: Windows x64
; 
; Задачи:
; 1. Ввод числа X в 16-ричной системе.
; 2. Вывод X в 10-ричной системе.
; 3. Расчет полинома Y = 4*X^2 + 19*X - 2.
; 4. Вывод Y в 8-ричной системе.
; 5. Вывод Y в 10-ричной системе.
; ==============================================================================

; ------------------------------------------------------------------------------
; Объявление внешних функций из Kernel32.dll
; ------------------------------------------------------------------------------
EXTERN GetStdHandle: PROC
EXTERN WriteConsoleA: PROC
EXTERN ReadConsoleA: PROC
EXTERN ExitProcess: PROC

.DATA
    ; --------------------------------------------------------------------------
    ; Константы и переменные
    ; --------------------------------------------------------------------------
    
    ; Дескрипторы стандартных потоков ввода/вывода
    std_input_handle    QWORD ?
    std_output_handle   QWORD ?

    ; Переменные для лабораторной работы
    coeff_a             DQ 4      ; Коэффициент a
    coeff_b             DQ 19     ; Коэффициент b
    coeff_c             DQ -2     ; Коэффициент c
    input_x             DQ ?      ; Здесь будет храниться введенное число X
    result_y            DQ ?      ; Здесь будет храниться результат Y

    ; Строки для вывода сообщений пользователю
    msg_prompt_x        DB "Введите шестнадцатеричное число x: ", 0
    msg_x_dec           DB 13, 10, "Введенное число x в десятичной системе: ", 0
    msg_y_oct           DB 13, 10, "Результат y в восьмеричной системе: ", 0
    msg_y_dec           DB 13, 10, "Результат y в десятичной системе: ", 0
    msg_newline         DB 13, 10, 0 ; Перевод строки

    ; Буферы для ввода с клавиатуры и для преобразования чисел в строку
    BUFFER_SIZE         EQU 256
    input_buffer        DB BUFFER_SIZE DUP(?)
    output_buffer       DB BUFFER_SIZE DUP(?)
    chars_read          DD ?
    chars_written       DD ?

.CODE
; ==============================================================================
; Главная процедура программы
; ==============================================================================
main PROC
    ; --- Пролог: настройка стека для вызовов WinAPI ---
    sub rsp, 40 ; Выделяем теневое пространство (32 байта) и место для локальных переменных

    ; --- Получение дескрипторов стандартных потоков ---
    ; Получаем дескриптор для вывода (STDOUT)
    mov rcx, -11 ; -11 это STD_OUTPUT_HANDLE
    call GetStdHandle
    mov [std_output_handle], rax

    ; Получаем дескриптор для ввода (STDIN)
    mov rcx, -10 ; -10 это STD_INPUT_HANDLE
    call GetStdHandle
    mov [std_input_handle], rax

    ; === ШАГ 1: Ввод числа X в 16-ричной системе ===
    ; Выводим приглашение к вводу
    lea rdx, msg_prompt_x
    call PrintString
    
    ; Читаем строку с клавиатуры
    lea rdx, input_buffer
    call ReadString
    
    ; Преобразуем 16-ричную строку в 64-битное знаковое число
    lea rcx, input_buffer
    call HexStrToInt64
    mov [input_x], rax ; Сохраняем результат в переменную

    ; === ШАГ 2: Вывод X в 10-ричной системе ===
    ; Выводим поясняющую строку
    lea rdx, msg_x_dec
    call PrintString
    
    ; Преобразуем число в 10-ричную строку и выводим
    mov rcx, [input_x]
    lea rdx, output_buffer
    mov r8, 10 ; Основание системы счисления = 10
    call Int64ToStr
    lea rdx, output_buffer
    call PrintString
    
    ; === ШАГ 3: Расчет полинома Y = 4*X^2 + 19*X - 2 ===
    mov rax, [input_x]      ; rax = x
    mov rbx, [input_x]      ; rbx = x
    imul rax, rbx           ; rax = x*x = x^2
    imul rax, [coeff_a]     ; rax = a*x^2 (4*x^2)
    
    mov rbx, [input_x]      ; rbx = x
    imul rbx, [coeff_b]     ; rbx = b*x (19*x)
    
    add rax, rbx            ; rax = a*x^2 + b*x
    add rax, [coeff_c]      ; rax = a*x^2 + b*x + c
    
    mov [result_y], rax     ; Сохраняем результат в y

    ; === ШАГ 4: Вывод Y в 8-ричной системе ===
    ; Выводим поясняющую строку
    lea rdx, msg_y_oct
    call PrintString
    
    ; Преобразуем число в 8-ричную строку и выводим
    mov rcx, [result_y]
    lea rdx, output_buffer
    mov r8, 8 ; Основание системы счисления = 8
    call Int64ToStr
    lea rdx, output_buffer
    call PrintString

    ; === ШАГ 5: Вывод Y в 10-ричной системе ===
    ; Выводим поясняющую строку
    lea rdx, msg_y_dec
    call PrintString
    
    ; Преобразуем число в 10-ричную строку и выводим
    mov rcx, [result_y]
    lea rdx, output_buffer
    mov r8, 10 ; Основание системы счисления = 10
    call Int64ToStr
    lea rdx, output_buffer
    call PrintString

    ; --- Завершение работы ---
    ; Перевод строки для чистоты вывода
    lea rdx, msg_newline
    call PrintString
    
    ; Выход из программы
    mov rcx, 0
    call ExitProcess

main ENDP

; ==============================================================================
; Процедура: PrintString
; Назначение: Вывод строки на консоль.
; Вход: RDX = адрес строки (null-terminated).
; ==============================================================================
PrintString PROC
    ; Сохраняем регистры, которые могут быть изменены
    push rdx
    push rcx
    sub rsp, 32 ; Теневое пространство
    
    ; Определяем длину строки
    mov rbx, rdx
    xor rcx, rcx
    .strlen_loop:
        cmp byte ptr [rbx], 0
        je .strlen_end
        inc rbx
        inc rcx
    jmp .strlen_loop
    .strlen_end:
    
    ; Вызов WriteConsoleA
    mov rcx, [std_output_handle]  ; 1-й арг: дескриптор
    ; rdx уже содержит адрес строки   ; 2-й арг: буфер
    mov r8, rcx                   ; 3-й арг: длина
    lea r9, [chars_written]       ; 4-й арг: куда записать кол-во выведенных символов
    mov qword ptr [rsp+32], 0     ; 5-й арг: зарезервировано (NULL)
    call WriteConsoleA
    
    add rsp, 32 ; Очищаем стек
    pop rcx
    pop rdx
    ret
PrintString ENDP

; ==============================================================================
; Процедура: ReadString
; Назначение: Чтение строки с консоли.
; Вход: RDX = адрес буфера для сохранения.
; Выход: RAX = количество прочитанных символов (включая CR+LF).
; ==============================================================================
ReadString PROC
    push rdx
    push rcx
    sub rsp, 32

    mov rcx, [std_input_handle] ; 1-й арг: дескриптор
    ; rdx уже содержит адрес буфера ; 2-й арг: буфер
    mov r8, BUFFER_SIZE - 1     ; 3-й арг: размер буфера
    lea r9, [chars_read]        ; 4-й арг: куда записать кол-во прочитанных символов
    mov qword ptr [rsp+32], 0   ; 5-й арг: NULL
    call ReadConsoleA
    
    ; Удаляем из строки символы CR+LF (0D 0A)
    mov rbx, rdx ; rbx = адрес буфера
    mov rax, qword ptr [chars_read]
    sub rax, 2 ; Убираем 2 символа
    mov byte ptr [rbx+rax], 0 ; Ставим null-терминатор на их место
    
    add rsp, 32
    pop rcx
    pop rdx
    ret
ReadString ENDP

; ==============================================================================
; Процедура: Int64ToStr (ИСПРАВЛЕННАЯ ВЕРСИЯ)
; Назначение: Преобразование 64-битного знакового числа в строку.
; Вход: RCX = число, RDX = буфер для строки, R8 = основание системы счисления.
; ==============================================================================
Int64ToStr PROC
    push rdi
    push rsi
    push rbx
    push rcx ; Сохраняем оригинальное число
    
    mov rdi, rdx ; rdi = указатель на буфер
    mov rbx, r8  ; rbx = основание (base)
    mov rax, rcx ; rax = число для преобразования
    xor rsi, rsi ; rsi = счетчик цифр
    
    ; Если число равно 0, обрабатываем отдельно
    cmp rax, 0
    jne .check_sign
    mov byte ptr [rdi], '0'
    inc rdi
    mov byte ptr [rdi], 0
    jmp .end_conversion_final

.check_sign:
    ; Проверяем знак числа
    test rax, rax
    jns .conversion_loop
    ; Если число отрицательное, ставим минус и инвертируем
    mov byte ptr [rdi], '-'
    inc rdi
    neg rax

.conversion_loop:
    ; Делим число на основание, остаток - следующая цифра
    xor rdx, rdx ; Очищаем старшую часть делимого
    div rbx      ; rax = rax / rbx, rdx = rax % rbx
    add dl, '0'  ; Преобразуем остаток в ASCII-символ
    push rdx     ; Сохраняем цифру в стеке
    inc rsi      ; Увеличиваем счетчик цифр
    
    cmp rax, 0   ; Повторяем, пока число не станет 0
    jne .conversion_loop

.pop_digits_loop:
    ; Извлекаем цифры из стека
    pop rax
    mov [rdi], al
    inc rdi
    dec rsi      ; Уменьшаем счетчик
    cmp rsi, 0
    jne .pop_digits_loop

.end_conversion_final:
    ; Ставим null-терминатор в конце строки
    mov byte ptr [rdi], 0
    
    pop rcx
    pop rbx
    pop rsi
    pop rdi
    ret
Int64ToStr ENDP

; ==============================================================================
; Процедура: HexStrToInt64
; Назначение: Преобразование 16-ричной строки в 64-битное знаковое число.
; Вход: RCX = адрес строки.
; Выход: RAX = результат.
; ==============================================================================
HexStrToInt64 PROC
    push rbx
    push rsi
    push rcx
    xor rax, rax ; rax = аккумулятор результата, обнуляем
    mov rsi, rcx ; rsi = указатель на текущий символ
    xor rbx, rbx ; rbx = флаг отрицательного числа (0 - положительное)
    
    ; Проверяем на знак "-"
    cmp byte ptr [rsi], '-'
    jne .parse_loop
    mov rbx, 1 ; Устанавливаем флаг
    inc rsi    ; Пропускаем знак
    
.parse_loop:
    mov cl, [rsi] ; cl = текущий символ
    cmp cl, 0
    je .parse_end ; Если конец строки, выходим
    
    ; Преобразуем ASCII символ в число
    ; Для '0'-'9'
    cmp cl, '9'
    jle .is_digit
    ; Для 'A'-'F'
    cmp cl, 'F'
    jle .is_upper_hex
    ; Для 'a'-'f'
    cmp cl, 'f'
    jle .is_lower_hex
    ; Некорректный символ, завершаем
    jmp .parse_end

.is_digit:
    sub cl, '0'
    jmp .accumulate

.is_upper_hex:
    sub cl, 'A' - 10
    jmp .accumulate

.is_lower_hex:
    sub cl, 'a' - 10
    
.accumulate:
    shl rax, 4 ; rax = rax * 16
    add rax, rcx ; Добавляем значение новой цифры
    inc rsi
    jmp .parse_loop

.parse_end:
    ; Если был знак "-", инвертируем результат
    cmp rbx, 1
    jne .done
    neg rax

.done:
    pop rcx
    pop rsi
    pop rbx
    ret
HexStrToInt64 ENDP

END