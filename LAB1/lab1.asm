%include "io64.asm"

  section .data              
      ExitMsg db "Press Enter to Exit",10 
      lenExit equ $-ExitMsg

      ; A dw -30
      ; B dw 21

      A dw 5
      B dw -5

      ; val1 db 255
      ; chart dw 256
      ; lue3 dw -128
      ; v5 db 10h
      ;    db 100101B
      ; beta db 23,23h,0ch
      ; sdk db "Hello",10
      ; min dw -32767
      ; ar dd 12345678h
      ; valar times 5 db

      ; strok db "Sofia", 10
      ; st db "Софья", 10

      ; num dw 25
      ; num2 dd -35

      ; num3 dw 37
      ; num4 dw 9472

      ; F1 dw 65535
      ; F2 dd 65535

  section .bss               
      InBuf   resb    10
      lenIn   equ     $-InBuf

      X resd 1

      alu resw 10
      f1 resb 5

  section .text ; сегмент кода
    global _start
    _start:

      mov eax,[A] ; загрузить число A в регистр EAX
      ; add eax,5   ; сложить EAX и 5, результат в EAX
      ; sub eax,[B] ; вычесть число B, результат в EAX
      ; mov [X],eax ; сохранить результат в памяти
      mov eax, [B]

      ; mov dword[F1], 1
      ; add word[F1], 1


      mov esi,InBuf
      ; mov ax, [X]
      cwde
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