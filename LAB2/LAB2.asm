%include "io64.asm"

   section .data              
ExitMsg db "Press Enter to Exit",10  
lenExit equ $-ExitMsg
InputMsg db "Input 5 numbers with Enter",10  
lenInput equ $-InputMsg
EMsg db "Inter E",10  
lenE equ $-EMsg
BMsg db "Inter B",10  
lenB equ $-BMsg
DMsg db "Inter D (non 0)",10  
lenD equ $-DMsg
QMsg db "Inter Q",10  
lenQ equ $-QMsg
MMsg db "Inter M",10  
lenM equ $-MMsg

   section .bss               
InBuf   resb    10            
lenIn   equ     $-InBuf 
Q resw 1
E resw 1
B resw 1
D resw 1
M resw 1
X resw 1


        section .text         
        global  _start
_start:

      mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      mov rsi, InputMsg ; адрес выводимой строки
      mov rdx, lenInput ; длина строки
      syscall       ; вызов системной функции

      mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      mov rsi, EMsg ; адрес выводимой строки
      mov rdx, lenE ; длина строки
      syscall       ; вызов системной функции
      
      mov rax, 0      ; системная функция 0 (read)
      mov rdi, 0      ; дескриптор файла stdin=0
      mov rsi, InBuf  ; адрес вводимой строки
      mov rdx, lenIn  ; длина строки
      syscall         ; вызов системной функции
      call StrToInt64
      
      mov [E], rax 

      mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      mov rsi, BMsg ; адрес выводимой строки
      mov rdx, lenB ; длина строки
      syscall       ; вызов системной функции

      mov rax, 0      ; системная функция 0 (read)
      mov rdi, 0      ; дескриптор файла stdin=0
      mov rsi, InBuf  ; адрес вводимой строки
      mov rdx, lenIn  ; длина строки
      syscall         ; вызов системной функции
      call StrToInt64
      
      mov [B], rax 


input: mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      mov rsi, DMsg ; адрес выводимой строки
      mov rdx, lenD ; длина строки
      syscall       ; вызов системной функции


      mov eax, 0      ; системная функция 0 (read)
      mov edi, 0      ; дескриптор файла stdin=0
      mov esi, InBuf  ; адрес вводимой строки
      mov edx, lenIn  ; длина строки
      syscall         ; вызов системной функции
      call StrToInt64
      
      mov [D], ax

      mov ax, [D]
      mov bx, 0
      cmp ax, bx
      je input


      mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      mov rsi, QMsg ; адрес выводимой строки
      mov rdx, lenQ ; длина строки
      syscall       ; вызов системной функции


      mov eax, 0      ; системная функция 0 (read)
      mov edi, 0      ; дескриптор файла stdin=0
      mov esi, InBuf  ; адрес вводимой строки
      mov edx, lenIn  ; длина строки
      syscall         ; вызов системной функции
      call StrToInt64
      
      mov [Q], ax 

      mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      mov rsi, MMsg ; адрес выводимой строки
      mov rdx, lenM ; длина строки
      syscall       ; вызов системной функции


      mov eax, 0      ; системная функция 0 (read)
      mov edi, 0      ; дескриптор файла stdin=0
      mov esi, InBuf  ; адрес вводимой строки
      mov edx, lenIn  ; длина строки
      syscall         ; вызов системной функции
      call StrToInt64
      
      mov [M], eax

        mov ax, [Q]
        imul ax    ;q*q
        mov bx, [M]
        imul bx
        mov bx, ax
        mov ax, [E]
        sub ax, [B]  ;E-B
        mov cx, [D]
        cwd
        idiv cx  ;(E-B)/D
        sub ax,bx
        sub ax, 2
        

        cwde
        mov rsi, InBuf
        call IntToStr64

    ; write
      mov rdx, rax
      mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      syscall

      mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      mov rsi, ExitMsg ; адрес выводимой строки
      mov rdx, lenExit ; длина строки
      syscall       ; вызов системной функции

    ; read
      mov rax, 0      ; системная функция 0 (read)
      mov rdi, 0      ; дескриптор файла stdin=0
      mov rsi, InBuf  ; адрес вводимой строки
      mov rdx, lenIn  ; длина строки
      syscall         ; вызов системной функции
      
    ; exit
      mov rax, 60     ; системная функция 60 (exit)
      xor rdi, rdi    ; return code 0
      syscall         ; вызов системной функции