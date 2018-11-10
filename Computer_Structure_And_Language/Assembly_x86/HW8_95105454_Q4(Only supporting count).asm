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
    jmp scanstr    
            
convert:

    mov bl,al
    mov ax,cx
    mul dl
    mov cx,ax
    sub bl,48
    mov bh,0
    add cx,bx
    jmp scan
    
scanstr:  

    mov dx, offset msg1
    mov ah, 9
    int 21h
    jmp n1
    msg1 db 0Dh,0Ah, '$'
    
    n1:

    mov bp,0  
    
    lea si, mainstr
    
    strloop:
    
        mov ah,0h
        int 16h
    
        mov ah,0eh
        int 10h     
        
        mov [si],ax
        
        inc si
        
        inc bp
        cmp bp,cx
        je finishstr
        jne strloop
        

finishstr:  

    mov dx, offset msg2
    mov ah, 9
    int 21h
    jmp n2
    msg2 db 0Dh,0Ah, '$'
    
    n2:
    
    mov ah,0h
    int 16h
    
    mov ah,0eh
    int 10h   
    
    mov dx, offset msg3
    mov ah, 9
    int 21h
    jmp n3
    msg3 db 0Dh,0Ah, '$'
    
    n3:
    
    cmp al,99
    je count
    
    cmp al,114
    je replace
    
count:

    mov bp,cx
    
    mov dl,10
    mov cx,0

scan2ndnum:

    mov ah, 0h
    int 16h

    mov ah, 0eh
    int 10h

    cmp al, 13
    jne convert2nd
    jmp scan2ndstr    
            
convert2nd:

    mov bl,al
    mov ax,cx
    mul dl
    mov cx,ax
    sub bl,48
    mov bh,0
    add cx,bx
    jmp scan2ndnum
    
scan2ndstr:

    mov bx,bp ;size of first str
    
    mov dx, offset msg4
    mov ah, 9
    int 21h
    jmp n4
    msg4 db 0Dh,0Ah, '$'
    
    n4:
    
    lea si,countstr
    
    mov bp,0
      
    str2loop:
    
        mov ah,0h
        int 16h
    
        mov ah,0eh
        int 10h     
        
        mov [si],ax
        
        inc si
        
        inc bp
        cmp bp,cx
        je startcalc
        jne str2loop
        
startcalc:

    mov dx, offset msg5
    mov ah, 9
    int 21h
    jmp n5
    msg5 db 0Dh,0Ah, '$'
    
    n5:
    
        ;bx : size of first string
        ;cx : size of second string
        mov ax,0 ;counter first loop
        mov dx,0 ;counter second loop
        mov bp,0 ;count number of repetition
        
        lea si,mainstr
        lea di,countstr
        
        lp1:
        
            mov dx,0
            
            push si
            push di 
              
            lp2:
                
                push ax
                push dx 
                mov ax,0
                mov dx,0
                mov al,[si]
                mov dl,[di]
                cmp ax,dx
                pop dx
                pop ax
                jne outlp2
                inc di
                inc si
                inc dx
                cmp dx,cx
                je addup
                jmp lp2
                
                
                
            addup:
                
                add bp,1
            
            outlp2: 
            
            
            pop di
            pop si
            inc ax
            cmp ax,bx
            je printres
            add si,1
            jmp lp1
            
            
                 
printres:

mov dx, offset msg6
mov ah, 9
int 21h
jmp n6
msg6 db 0Dh,0Ah, '$'

n6:

mov ax,bp


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

jmp endprog

             
        
        
                       

    
    
replace:
    
    



endprog:

mainstr db "                                                                                                     "

countstr db "                                                                                                     "
    
ten dw 10    