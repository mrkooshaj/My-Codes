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
    jmp startcalc    
            
convert:

    mov bl,al
    mov ax,cx
    mul dl
    mov cx,ax
    sub bl,48
    mov bh,0
    add cx,bx
    jmp scan
        
startcalc: 

    mov bx,1  
    mov bp,0
    
calcloop:

    mov ax,cx
    
    minusloop:
    
        sub ax,bx
        cmp ax,0
        jg minusloop
        je addup
        jl rest
    
addup:
    
    add bp,bx

rest:

    inc bx
    cmp bx,cx
    je printres
    jne calcloop
    
printres:



mov dx, offset msg1
mov ah, 9
int 21h
jmp n1
msg1 db 0Dh,0Ah, '$'

n1:

mov ax,bp
add ax,cx


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



ten dw 10
         



             
             
                                       