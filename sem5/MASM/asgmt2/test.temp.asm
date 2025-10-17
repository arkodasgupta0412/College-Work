.stack 100h

dgroup group data
data segment
    message db "Hello World!", 0Dh, 0Ah, "$"
data ends

code segment
main proc
    mov ax, data
    mov ds, ax

    mov ah, 09h
    lea dx, message
    int 21h

    mov ah, 4Ch
    int 21h
main endp
code ends
end main
