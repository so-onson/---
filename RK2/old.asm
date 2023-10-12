%include "io64.asm"
section .data
    InputMsg dq "Input string: ",10  
    lenInput equ $-InputMsg
    ; Max dw 0
section .bss
    StrInp resb 30
    lenStr equ $-StrInp
    StrNew times 10 db ''
section .text
global  _start
_start:

    mov rax, 1
    mov rdi, 1
    mov rsi, InputMsg
    mov rdx, lenInput
    syscall

    ; read
    mov rax, 0  
    mov rdi, 0      
    mov rsi, StrInp  
    mov rdx, lenStr  
    syscall        


;основная часть


;подсчет длины введенной строки до кода Enter
lea rdi,[StrInp] 
mov rcx,lenStr
mov al,0Ah
repne scasb; ищем код Enter
mov rax,30
sub rax,rcx
mov rcx,rax
mov byte[rcx+StrInp-1],' ' ;добавление пробела в конец строки

; mov [lenStr],rcx

    mov edx,0
    mov ebx,0
    ; mov ecx, lenStr

cycl:
    lea esi, [StrInp + edx]
    mov al,' '
    cmp [StrInp + edx], al
    je probel
    jmp next

probel: 
    inc ebx
    jmp next
next: 
    inc edx
    loop cycl


    mov eax, ebx

    call IntToStr64

    mov rdx,rax
    mov rax,1
    mov rdi,1
    syscall
 
;стараемся посчитать произведение
    
    mov ecx, ebx
    mov ebx, lenStr
cycl1:
    mov al, ' '
    lea esi,[StrInp+edx]
    cmp [StrInp+edx], al

    je probel1
    inc edx
    lea edi, [StrNew + edx]
    repe movsb
    jmp cycl1

probel1:
    inc edx ;?
    mov esi, [StrNew]
    call StrToInt64  ;в eax число 
    jmp cycl2

cycl2:
    mov eax, ' '
    lea edi, [StrInp]
    add edi, ebx
    cmp edi, eax
    je probel2

    dec ebx
    ;jmp cycl2
    lea edi, [StrNew+ebx]
    repe movsb
    jmp cycl2

probel2:
    dec ebx
    mov r8,rax
    mov esi, [StrNew]
    call StrToInt64  ;в eax число 
    imul r8
    call IntToStr64
    push rdx
    mov rdx,rax
    mov rax,1
    mov rdi,1
    syscall
    pop rdx

loop cycl1


exit:
    xor rdi, rdi
    mov rax, 60
    syscall