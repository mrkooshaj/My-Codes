.code

putc macro char
        
        push ax
        mov al, char
        mov ah, 0eh
        int 10h     
        pop ax
        
endm

mov dx,0  

lea si,input

mov bl,[si]

cmp bl,97
jge lw

cmp bl,65
jge up
jne scan

lw:
    cmp bl,122
    jle prep
    jg scan
up:
    cmp bl,90
    jle prep
    jg scan
    
prep:
    
    mov dx,1



scan:
          
    mov bl,al      
          
    inc si
    
    mov al, [si]

    cmp al, 0
    
    jne check
    jmp startcalc    
            
check:
   
   cmp al,97
   jge lowercase
   cmp al,65
   jge uppercase
   jl scan 
   
   
uppercase:
   
   cmp al,90
   jle goodcheck
   jg scan
   
lowercase:

   cmp al,122                                     
   jle goodcheck
   jg scan
   
goodcheck:

   cmp bl,32
   je add1
   cmp bl,13
   je add1
   jne scan
   
add1:
    
    add dx,1
    jne scan
        
startcalc: 

mov cx,dx

mov dx, offset msg1
mov ah, 9
int 21h
jmp n1
msg1 db 0Dh,0Ah, '$'

n1:        

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



ten dw 10  

input db "    koosha ? is     the best . in the world!"
