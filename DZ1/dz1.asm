%include "io64.asm"

section .data              
InpMsg db "Input 3 words: ",10  
lenInp equ $-InpMsg

Stroka db "abcdef qwerty abcdef",10
lenStroka equ $-Stroka
Stroka2 db "rrrrrr rrrrrr rrrrrr",10
lenStroka2 equ $-Stroka2
Dlina dw 3

section .bss             
InBuf   resb    10            
lenIn   equ     $-InBuf


StrokaInp resw 20
lenStr   equ     $-StrokaInp


section .text         
        global  _start
_start:
      mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      mov rsi, InpMsg ; адрес выводимой строки
      mov rdx, lenInp ; длина строки
      syscall       ; вызов системной функции


    ; read
      mov rax, 0      ; системная функция 0 (read)
      mov rdi, 0      ; дескриптор файла stdin=0
      mov rsi, StrokaInp  ; адрес вводимой строки
      mov rdx, lenStr  ; длина строки
      syscall         ; вызов системной функции



lea rdi,[StrokaInp] ; загружаем адрес строки в edi
mov dx,0 ; обнуляем счетчик длины слова


;алгоритм замены во втором слове ecx=2
mov ecx,3

cycl:  push rcx
    mov eax,7
    imul ecx
    mov edx,eax
    sub edx,7 


    mov ebx,6
    sub ebx,ecx ;4 = ebx

    lea esi, [StrokaInp+edx]
    lea edi, [Stroka2+edx+ebx]


    repe movsb

;     pop rcx

;     push rcx


    lea esi, [StrokaInp+edx+6]
    sub esi,ebx
    lea edi, [Stroka2+edx] 
    mov ecx, ebx; ecx=4
    repe movsb
pop rcx
    loop cycl




      mov rax, 1    ; системная функция 1 (write)
      mov rdi, 1    ; дескриптор файла stdout=1
      mov rsi, Stroka2 ; адрес выводимой строки
      mov rdx, lenStroka2 ; длина строки
      syscall       ; вызов системной функции


exit:
    xor rdi, rdi
    mov rax, 60
    syscall