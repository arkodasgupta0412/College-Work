.model small
.stack 100h
.data
  
.code
main proc  
    
    mov ax, 123
    mov bx, 456
    mov cx, 0
    
    add ax, bx
    
extractDigit:
    mov dx, 0
    mov bx, 10
    
    div bx
    push dx 
    inc cx
    cmp ax, 0
    jne extractDigit
    
print:
    cmp cx, 0
    je exit
    
    dec cx
    pop dx
    add dx, 48
    mov ah, 02h
    int 21h
    jmp print
    
      
exit:      
    mov ah, 4Ch
    int 21h
    
main endp
end


