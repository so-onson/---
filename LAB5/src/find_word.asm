%define STDOUT 1
%define WRITE 1
%define EXIT 60

%define MAX_LEN 255

section .data
    err_msg db "Invalid word position",10
    err_len equ $-err_msg
    my_msg db "swapmeonly",10
    

section .bss
    OutBuf resb 10
    input_len resq 1
    input_start resq 1

    max resd 1
    count resd 1
    addr resq 1

section .text
global find_word
; extern print_cut
extern count_char

find_word:
    push rbp
    mov rbp, rsp
    lea rsp, [rsp-0]

    mov [input_start], rdi
    mov [input_len], rsi

    mov dword[max],0
    ;тут надо сделать что проходим по строке до пробела сохраняем сторку отправляем в log вернули сравнили полученное число  
    mov rax, [input_start]
    mov rbx, [input_len]
    add rax, rbx

start:   
    cmp rdi, rax 
    je exit
    push rdi 
    push rax
    push rdx
    mov rsi, count
    call count_char
    pop rdx
    pop rax
    pop rdi
    mov rbx,[count]
    cmp ebx,[max]
    jle less
    mov [max],rbx
    mov [addr],rdi
    less:
    inc rdi
    cmp byte[rdi-1], " "
    je start
    jmp less

exit:

    mov rsi, [addr]
    mov rdi, rdx
write_word:
    movsb
    cmp byte[rsi], " "
    je end_write_word
    jmp write_word
end_write_word:

    mov rsp, rbp
    pop rbp
    ret
