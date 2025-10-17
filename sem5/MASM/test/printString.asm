.model small
.stack 100h

.data
    msg db "Hello Assembly$"
    
.code
main PROC
    mov ax, @data
    mov ds, ax
                 
    mov ah, 09h
    mov dx, offset msg
    int 21h
                 
    
    mov ah, 4ch
    int 21h
main endp
end