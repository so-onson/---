%include "io64.asm"

section .data
    InputMsg dq "Input 7*3 matrix: ",10
    lenInput equ $-InputMsg
    OutMsg dq "Your matrix: ",10
    lenOut equ $-OutMsg
    DevMsg dq "",10  
    lenDev equ $-DevMsg

    err_line dq "Each line should have exactly 3 numbers divided by spaces", 10
    err_line_len equ $-err_line

    err_num dq "Only numbers and spaces can be entered", 10
    err_num_len equ $-err_num

    input times 32  db 0
    input_len equ $-input

    matrix times 21 dq 0

    A	dq	2,3,1
		dq	6,-8,5
		dq	6,3,1
        dq	8,4,7
        dq	3,-1,8
        dq	3,1,6
        dq	8,6,7


section .bss               
    InBuf   resb    10            
    lenIn   equ     $-InBuf
    X resd 1
    res resq 1

section .text         
    global  _start
_start:

    mov rax, 1
    mov rdi, 1
    mov rsi, InputMsg
    mov rdx, lenInput
    syscall




    mov rcx,7
    xor rdi, rdi
read_line:
    push rcx
    push rdi

    mov rax, 0 ; системная функция 0 (read)
    mov rdi, 0 ; дескриптор файла stdin=0
    mov rsi, input ; адрес вводимой строки
    mov rdx, input_len ; длина строки
    syscall ; вызов системной функции
    
    pop rdi

    mov rcx, rax
    xor rdx, rdx
    xor r10, r10
process_line:
    cmp byte[input + rdx], 10
    je process_number

    cmp byte[input + rdx], ' '
    jne next

    mov byte[input + rdx], 10
    cmp r10, rdx
    jne process_number
    jmp next

process_number:
    push rdx
    call StrToInt64
    cmp rbx, 0   ;проверка на букву
    jne error_num 
    cmp rdi, 21
    jge error_line ;;проверка на лишнее число

    mov [matrix + 8*rdi], rax
    inc rdi

    pop rdx
    mov r10, rdx
    inc r10
    lea rsi, [input + r10]

next:
    inc rdx
    loop process_line

    pop rcx

    mov rax, 3
    sub rax, rcx
    inc rax
    push rdx
    mov rdx, 3
    mul rdx
    pop rdx

    dec rcx
    cmp rcx, 0
    jne read_line



;основная программа
    mov rbx, 0
    mov rcx,11
    xor rdi, rdi


read:
    mov qword[rbx*8+matrix], 0
    add rbx, 2
    loop read


    mov rax, 1
    mov rdi, 1
    mov rsi, OutMsg
    mov rdx, lenOut
    syscall

;вывод матрицы
    mov rcx,7
    mov rbx,0
    xor rdi, rdi
out_line:
    push rcx
    mov rcx,3

out_num: 
        mov rax,[rbx*8+matrix]

        mov rsi, InBuf
        call IntToStr64

        push rcx
        

    ; write
      mov rdx, rax
      mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      syscall
        
        pop rcx
        mov rdi, 0   

        cmp rcx,1


        inc rbx
        loop out_num

        push rcx
        mov rax,1
        mov rdi,1
        mov rsi, DevMsg ; адрес выводимой строки
        mov rdx, lenDev ; длина строки
        syscall
        pop rcx


        pop rcx
        loop out_line

 


exit:
    xor rdi, rdi
    mov rax, 60
    syscall

error_line:
    mov rax, 1
    mov rdi, 1   
    mov rsi, err_line
    mov rdx, err_line_len
    syscall
    jmp exit

error_num:
    mov rax, 1
    mov rdi, 1   
    mov rsi, err_num
    mov rdx, err_num_len
    syscall
    jmp exit
