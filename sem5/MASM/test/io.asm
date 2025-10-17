.model small
.stack 100h

.data
    prompt db "Enter a number: $"
    
.code
main proc
    
    mov ah, 1   ; // function for taking user input
    int 21h     ; // call function
    mov bl, al  ; by default, whatever value is retrieved for user input, stored in al
    
    
    mov ah, 2   ; function for displaying
    mov dl, bl  ; move value to dl register only for display
    int 21h
    
    
    mov ah, 4ch
    int 21h
    
main endp
end