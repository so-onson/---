%include "io64.asm"

section .data              
ExitMsg db "Press Enter to Exit",10  
lenExit equ $-ExitMsg
InputMsg db "Input X",10  
lenInput equ $-InputMsg
AMsg db "Inter A",10  
lenA equ $-AMsg
YMsg db "Inter Y",10  
lenY equ $-YMsg
NMsg db "Inter N",10  
lenN equ $-NMsg


; A dd 90
; Y dd 3
N dd 0
; X dd -8

section .bss               
InBuf   resb    10            
lenIn   equ     $-InBuf
X resd 1
A resw 1
Y resw 1



section .text         
        global  _start
_start:
      mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      mov rsi, InputMsg ; адрес выводимой строки
      mov rdx, lenInput ; длина строки
      syscall       ; вызов системной функции

      mov rax, 0      ; системная функция 0 (read)
      mov rdi, 0      ; дескриптор файла stdin=0
      mov rsi, InBuf  ; адрес вводимой строки
      mov rdx, lenIn  ; длина строки
      syscall         ; вызов системной функции
      call StrToInt64
      
      mov [X], rax

      mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      mov rsi, AMsg ; адрес выводимой строки
      mov rdx, lenA ; длина строки
      syscall       ; вызов системной функции

      mov rax, 0      ; системная функция 0 (read)
      mov rdi, 0      ; дескриптор файла stdin=0
      mov rsi, InBuf  ; адрес вводимой строки
      mov rdx, lenIn  ; длина строки
      syscall         ; вызов системной функции
      call StrToInt64
      
      mov [A], rax
     
        mov   eax, [X]

        cmp   eax, [N]  ; сравнение A и B
        jle    LESS    ; если первое меньше или равно
        mov eax, [X]
        imul eax    ;q*q
        mov ebx, [A]
        imul ebx
        jmp   short CONTINUE  ; безусловный переход 
LESS:   
  input: mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      mov rsi, YMsg ; адрес выводимой строки
      mov rdx, lenY ; длина строки
      syscall       ; вызов системной функции

      mov rax, 0      ; системная функция 0 (read)
      mov rdi, 0      ; дескриптор файла stdin=0
      mov rsi, InBuf  ; адрес вводимой строки
      mov rdx, lenIn  ; длина строки
      syscall         ; вызов системной функции
      call StrToInt64
      
      mov [Y], rax

      mov ax, [Y]
      mov bx, [X]
      sub ax, bx
      mov bx, 0
      cmp ax, bx
      je input


        mov ebx, [Y]
        sub ebx, [X]
        mov eax, [A]
        cwd
        idiv ebx

CONTINUE:    


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