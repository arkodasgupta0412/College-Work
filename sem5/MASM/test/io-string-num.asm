.model small
.stack 100h

.data
    num db 3
    num1 db ?
    input db "Enter num: $"
    output db "You entered: $"
    
.code
main proc
    mov ax, @data
    mov ds, ax
    
    
    ; display contents of memory location num
    mov ah, 2  
    mov dl, num
    add dl, 30h
    int 21h   
    
    
    ; new line + carriage return
    mov ah, 2
    mov dl, 0Ah
    int 21h
    mov dl, 0Dh
    int 21h
    
    mov ah, 9
    mov dl, offset input
    int 21h           
    
    
    ; take user input, store it in variable (say num1), display
    mov ah, 1
    int 21h
    ; user input data now in al register         
    
    mov num1, al  
    
    
    ; new line + carriage return
    mov ah, 2
    mov dl, 0Ah
    int 21h      
    mov dl, 0Dh
    int 21h
    
    mov ah, 9
    mov dl, offset output
    int 21h
    
    ; display user input value
    mov ah, 2
    mov dl, num1
    int 21h
    
    
    mov ah, 4Ch
    int 21h
main endp
end