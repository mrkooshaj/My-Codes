.code      

putc macro char
        
        push ax
        mov al, char
        mov ah, 0eh
        int 10h     
        pop ax
        
endm

mov dl,10
mov cx,0

scan:

    mov ah, 0h
    int 16h

    mov ah, 0eh
    int 10h

    cmp al, 13
    jne convert
    jmp rest    
            
convert:

    mov bl,al
    mov ax,cx
    mul dl
    mov cx,ax
    sub bl,48
    mov bh,0
    add cx,bx
    jmp scan
        
rest:

mov bp,cx 
mov cx,0

mov dx, offset msg1
mov ah, 9
int 21h
jmp scan2nd
msg1 db 0Dh,0Ah, '$'

 

scan2nd:

    mov ah, 0h
    int 16h

    mov ah, 0eh
    int 10h

    cmp al, 13
    jne convert2nd
    jmp startcalc    
            
convert2nd:

    mov bl,al
    mov ax,cx
    mul dl
    mov cx,ax
    sub bl,48
    mov bh,0
    add cx,bx
    jmp scan2nd      
        
startcalc:      

mov bx,cx

mov dx, offset msg2
mov ah, 9
int 21h
jmp prepare
msg2 db 0Dh,0Ah, '$'

prepare:

mov ax,bp

call calccomb

mov ax,cx 

printnum proc near
        
        push ax
        push bx
        push cx
        push dx

        mov cx,1

        mov bx,10000

        cmp ax,0
        
        jz printzero

begin_print:

        cmp bx,0
        jz end_print

        cmp cx,0
        jz calc
   
        cmp ax, bx
        jb skip
calc:
        mov cx, 0

        mov dx, 0
        div bx

        add al, 48
        putc al


        mov ax,dx

skip:
     
        push ax
        mov dx,0
        mov ax,bx
        div cs:ten
        mov bx,ax
        pop ax

        jmp begin_print
        
printzero:

        putc '0'
        
end_print:

        pop dx
        pop cx
        pop bx
        pop ax
        
        ret

printnum endp

proc calccomb
    
    cmp ax,bx
    je setone
    cmp bx,0
    je setone
    
    push dx
    push ax
    dec ax
    call calccomb
    
    mov dx,cx
    
    push bx
    dec bx
    call calccomb
    
    pop bx
    pop ax
    
    add cx,dx
    
    pop dx
    ret
    
    
    
    
    setone:
        
        mov cx,1
        ret              
        
calccomb endp

ten dw 10