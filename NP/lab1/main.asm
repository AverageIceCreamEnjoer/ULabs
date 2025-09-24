; ------------------------------------------------------------------------------
; Объявление внешних функций из библиотеки Kernel32.dll, которые мы будем использовать.
; ------------------------------------------------------------------------------
EXTERN GetStdHandle: PROC
EXTERN WriteConsoleA: PROC
EXTERN ReadConsoleA: PROC
EXTERN ExitProcess: PROC
EXTERN SetConsoleCP: PROC
EXTERN SetConsoleOutputCP: PROC

; ==============================================================================
; Секция .DATA: здесь объявляются все инициализированные и неинициализированные
; глобальные переменные и константы.
; ==============================================================================
.DATA
    ; --- Дескрипторы стандартных потоков ---
    std_input_handle    QWORD ? ; Переменная для хранения дескриптора консоли для ввода.
    std_output_handle   QWORD ? ; Переменная для хранения дескриптора консоли для вывода.
    ; --- Коэффициенты полинома ---
    coeff_a             DQ 4
    coeff_b             DQ 19
    coeff_c             DQ -2
    ; --- Переменные для хранения чисел ---
    input_x             DQ ?
    result_y            DQ ?
    ; --- Строки для взаимодействия с пользователем ---
    msg_prompt_x        DB "Введите шестнадцатеричное число x: ", 0
    msg_x_dec           DB 13, 10, "Введенное число x в десятичной системе: ", 0
    msg_y_oct           DB 13, 10, "Результат y в восьмеричной системе: ", 0
    msg_y_dec           DB 13, 10, "Результат y в десятичной системе: ", 0
    msg_newline         DB 13, 10, 0 ; Строка для перевода курсора. 13=CR, 10=LF.
    ; --- Буферы и вспомогательные переменные ---
    BUFFER_SIZE         EQU 256
    input_buffer        DB BUFFER_SIZE DUP(?) ; Буфер для чтения строки с клавиатуры.
    output_buffer       DB BUFFER_SIZE DUP(?) ; Буфер для преобразования чисел в строку для вывода.
    ; --- Вспомогательные переменные для чтения строки
    chars_read          DD ?    ; DWORD (32 бита) в соответствии с API
    chars_written       DD ?    ; DWORD (32 бита) в соответствии с API

; ==============================================================================
; Секция .CODE: здесь находится исполняемый код программы.
; ==============================================================================
.CODE

; ------------------------------------------------------------------------------
; Главная процедура программы (точка входа).
; ------------------------------------------------------------------------------
main PROC
    ; Пролог: выделяем 40 байт на стеке. 32 байта - это "теневое пространство",
    ; обязательное по соглашению о вызовах x64, плюс 8 для выравнивания.
    sub rsp, 40 
    ; --- ЭТАП 1: ИНИЦИАЛИЗАЦИЯ СРЕДЫ ---
    ; Устанавливаем кодовую страницу 1251 для корректной работы с кириллицей.
    mov rcx, 1251           ; Аргумент 1: ID кодовой страницы (1251 для Windows Cyrillic)
    call SetConsoleCP       ; Устанавливаем кодировку для ввода.
    mov rcx, 1251
    call SetConsoleOutputCP ; Устанавливаем кодировку для вывода.
    ; Получаем дескриптор стандартного потока вывода (экран).
    mov rcx, -11                 ; Аргумент 1: -11 это константа STD_OUTPUT_HANDLE.
    call GetStdHandle
    mov [std_output_handle], rax ; Сохраняем полученный дескриптор.
    ; Получаем дескриптор стандартного потока ввода (клавиатура).
    mov rcx, -10 ; Аргумент 1: -10 это константа STD_INPUT_HANDLE.
    call GetStdHandle
    mov [std_input_handle], rax ; Сохраняем дескриптор.
    ; --- ЭТАП 2: ВВОД И ПРЕОБРАЗОВАНИЕ ЧИСЛА X ---
    ; Выводим приглашение к вводу.
    lea rdx, msg_prompt_x ; Аргумент 1 (RDX): адрес строки для вывода.
    call PrintString
    ; Читаем строку с клавиатуры.
    lea rdx, input_buffer ; Аргумент 1 (RDX): адрес буфера для сохранения строки.
    call ReadString
    ; Преобразуем 16-ричную строку в 64-битное число.
    lea rcx, input_buffer ; Аргумент 1 (RCX): адрес строки для преобразования.
    call HexStrToInt64
    mov [input_x], rax ; Сохраняем результат (из RAX) в переменную.
    ; --- ЭТАП 3: ВЫВОД РЕЗУЛЬТАТОВ ---
    lea rdx, msg_x_dec ; Выводим X в десятичной системе.
    call PrintString 
    mov rcx, [input_x]     ; Аргумент 1: число для преобразования.
    lea rdx, output_buffer ; Аргумент 2: буфер для результата.
    mov r8, 10             ; Аргумент 3: основание системы счисления (10).
    call Int64ToStr
    lea rdx, output_buffer ; Загружаем адрес полученной строки в RDX.
    call PrintString       ; Печатаем.
    ; --- ЭТАП 4: ВЫЧИСЛЕНИЕ ПОЛИНОМА Y ---
    mov rax, [input_x] ; rax = x
    mov rbx, [input_x] ; rbx = x
    imul rax, rbx      ; rax = x * x (x^2)
    imul rax, [coeff_a] ; rax = rax * a (a*x^2)
    mov rbx, [input_x]  ; rbx = x
    imul rbx, [coeff_b] ; rbx = rbx * b (b*x)
    add rax, rbx        ; rax = a*x^2 + b*x
    add rax, [coeff_c]  ; rax = a*x^2 + b*x + c
    mov [result_y], rax ; Сохраняем финальный результат в переменную Y.
    ; Выводим Y в восьмеричной системе. 
    lea rdx, msg_y_oct
    call PrintString
    mov rcx, [result_y]     ; Аргумент 1: число Y.
    lea rdx, output_buffer  ; Аргумент 2: буфер для результата.
    mov r8, 8               ; Аргумент 3: основание системы счисления (8).
    call Int64ToStr
    lea rdx, output_buffer
    call PrintString
    ; Выводим Y в десятичной системе.
    lea rdx, msg_y_dec
    call PrintString
    mov rcx, [result_y]      ; Аргумент 1: число Y.
    lea rdx, output_buffer   ; Аргумент 2: буфер для результата.
    mov r8, 10               ; Аргумент 3: основание (10).
    call Int64ToStr
    lea rdx, output_buffer
    call PrintString
    ; --- ЭТАП 5: ЗАВЕРШЕНИЕ РАБОТЫ ---
    lea rdx, msg_newline
    call PrintString
    ; Корректно завершаем процесс.
    mov rcx, 0 ; Аргумент 1: код возврата (0 = успех).
    call ExitProcess
main ENDP

; ------------------------------------------------------------------------------
; Процедура: PrintString
; Назначение: Вывод на консоль строки, завершающейся нулем.
; Вход:       RDX = адрес строки.
; ------------------------------------------------------------------------------
PrintString PROC
    ; Сохраняем регистры, которые могут быть изменены внутри процедуры.
    push rbx
    ; Выделяем 40 байт на стеке для теневого пространства и выравнивания.
    sub rsp, 40
    ; Цикл для определения длины строки.
    mov rbx, rdx  ; rbx - указатель на текущий символ.
    xor rcx, rcx  ; rcx - счетчик длины.
strlen_loop:
    cmp byte ptr [rbx], 0 ; Проверяем, не конец ли строки.
    je strlen_end
    inc rbx
    inc rcx
    jmp strlen_loop
strlen_end:
    ; Подготовка аргументов для вызова WriteConsoleA.
    mov r8, rcx                  ; Аргумент 3 (R8): длина строки.
    mov rcx, [std_output_handle] ; Аргумент 1 (RCX): дескриптор вывода.
     ; RDX уже содержит адрес строки (Аргумент 2).
    lea r9, [chars_written]      ; Аргумент 4 (R9): адрес переменной для кол-ва записанных байт.
    mov qword ptr [rsp+32], 0    ; Аргумент 5 (на стеке): зарезервировано (NULL).
    call WriteConsoleA
    ; Восстанавливаем стек и регистры.
    add rsp, 40
    pop rbx
    ret
PrintString ENDP

; ------------------------------------------------------------------------------
; Процедура: ReadString
; Назначение: Чтение строки с клавиатуры.
; Вход:       RDX = адрес буфера для сохранения строки.
; ------------------------------------------------------------------------------
ReadString PROC
    ; Сохраняем RBX, так как это нелетучий регистр, и мы его используем.
    push rbx
    ; Выделяем 40 байт на стеке для теневого пространства и выравнивания.
    sub rsp, 40
    ; Сохраняем адрес буфера (из RDX) в безопасный,
    ; нелетучий регистр RBX, потому что RDX будет уничтожен вызовом ReadConsoleA.
    mov rbx, rdx
    ; Подготовка аргументов для вызова ReadConsoleA.
    mov rcx, [std_input_handle] ; Аргумент 1 (RCX): дескриптор ввода.
    mov rdx, rbx                ; Аргумент 2 (RDX): адрес буфера.
    mov r8, BUFFER_SIZE - 1     ; Аргумент 3 (R8): максимальное кол-во символов для чтения.
    lea r9, [chars_read]        ; Аргумент 4 (R9): адрес переменной для кол-ва прочитанных байт.
    mov qword ptr [rsp+32], 0   ; Аргумент 5 (на стеке): зарезервировано (NULL).
    call ReadConsoleA
    
    ; Читаем 32-битный DWORD в EAX. RAX автоматически обнуляется в старших битах.
    mov eax, [chars_read]
    ; Обработка прочитанной строки: установка нуль-терминатора
    cmp rax, 0                      ; Если ничего не прочитано, выходим.
    je done_reading
    mov byte ptr [rbx + rax], 0     ; Ставим \0 в самый конец (за последний символ).
    ; Удаляем символы CR (\r) и LF (\n) из конца строки
    cmp rax, 2
    jl done_reading
    cmp byte ptr [rbx + rax - 2], 0Dh   
    jne done_reading
    cmp byte ptr [rbx + rax - 1], 0Ah 
    jne done_reading
    mov byte ptr [rbx + rax - 2], 0 ; Заменяем CR на \0, укорачивая строку.

done_reading:
    ; Восстанавливаем стек и регистр.
    add rsp, 40
    pop rbx
    ret
ReadString ENDP

; ------------------------------------------------------------------------------
; Процедура: Int64ToStr
; Назначение: Преобразование 64-битного знакового числа в строку.
; Вход:       RCX = число, RDX = буфер для строки, R8 = основание системы.
; ------------------------------------------------------------------------------
Int64ToStr PROC
    push rdi
    push rsi
    push rbx
    push rcx
    mov rdi, rdx    ; rdi = указатель на буфер.
    mov rbx, r8     ; rbx = основание.
    mov rax, rcx    ; rax = число.
    xor rsi, rsi    ; rsi = счетчик цифр.
    cmp rax, 0      ; Отдельно обрабатываем случай, если число - ноль.
    jne check_sign
    mov byte ptr [rdi], '0'
    inc rdi
    mov byte ptr [rdi], 0
    jmp end_conversion_final
check_sign:
    test rax, rax            ; Проверяем знак числа.
    jns conversion_loop      ; Если не отрицательное, переходим к циклу.
    mov byte ptr [rdi], '-'  ; Иначе, ставим минус в начало строки.
    inc rdi
    neg rax                  ; И инвертируем число.
conversion_loop:
    xor rdx, rdx             ; Обнуляем RDX перед делением.
    div rbx                  ; rax = rax / rbx, rdx = остаток.
    add dl, '0'              ; Преобразуем остаток (0-9) в символ ('0'-'9').
    push rdx                 ; Сохраняем символ цифры в стеке.
    inc rsi                  ; Увеличиваем счетчик цифр.
    cmp rax, 0               ; Повторяем, пока число не станет нулем.
    jne conversion_loop
pop_digits_loop:
    pop rax                  ; Извлекаем цифры из стека (они будут в обратном порядке).
    mov [rdi], al            ; Записываем символ в буфер.
    inc rdi
    dec rsi                  ; Уменьшаем счетчик.
    cmp rsi, 0
    jne pop_digits_loop
end_conversion_final:
    mov byte ptr [rdi], 0    ; Ставим нуль-терминатор в конце строки.
    pop rcx
    pop rbx
    pop rsi
    pop rdi
    ret
Int64ToStr ENDP

; ------------------------------------------------------------------------------
; Процедура: HexStrToInt64
; Назначение: Преобразование 16-ричной строки в 64-битное знаковое число.
; Вход:       RCX = адрес строки.
; Выход:      RAX = результат.
; ------------------------------------------------------------------------------
HexStrToInt64 PROC
    push rbx
    push rsi
    push rcx
    xor rax, rax                ; rax = аккумулятор результата.
    mov rsi, rcx                ; rsi = указатель на текущий символ.
    xor rbx, rbx                ; rbx = флаг отрицательного числа.
    cmp byte ptr [rsi], '-'     ; Проверяем наличие знака '-'.
    jne parse_loop
    mov rbx, 1                  ; Устанавливаем флаг.
    inc rsi                     ; Пропускаем символ знака.
parse_loop:
    movzx rcx, byte ptr [rsi]   ; Читаем байт-символ в RCX, обнуляя старшие биты.
    cmp cl, 0
    je parse_end
    ; Преобразуем ASCII-символ в числовое значение (0-15).
    cmp cl, '9'
    jle is_digit
    cmp cl, 'F'
    jle is_upper_hex
    cmp cl, 'f'
    jle is_lower_hex
    jmp parse_end               ; Если символ некорректный, завершаем.
is_digit:
    sub cl, '0'
    jmp accumulate
is_upper_hex:
    sub cl, 'A' - 10
    jmp accumulate
is_lower_hex:
    sub cl, 'a' - 10
accumulate:
    shl rax, 4       ; Умножаем аккумулятор на 16.
    add rax, rcx     ; Добавляем значение новой цифры.
    inc rsi          ; Переходим к следующему символу.
    jmp parse_loop
parse_end:
    cmp rbx, 1       ; Если был флаг отрицательного числа...
    jne done
    neg rax          ; ...инвертируем результат.
done:
    pop rcx
    pop rsi
    pop rbx
    ret
HexStrToInt64 ENDP

END