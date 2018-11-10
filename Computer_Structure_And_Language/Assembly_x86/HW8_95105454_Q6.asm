.code



;------------------------------------------------
;Part one :                                     


mov dx,bx ;----> keeping the first bx

mov ax,[bx] ;---> ax = A.pointer
mov bx,ax ; -----> bx = A.pointer
mov ax,[bx] ;---> ax = *(A.pointer)

mov bx,dx ;----->restoring bx

mov [bx+6],ax ;----> A.array[2] = *(A.pointer)


;------------------------------------------------



              

;------------------------------------------------
;Part two :    

mov dx,bx ;-----> keeping the first bx

mov ax,[bx+14] ;----> ax = A.f

mov bx,ax ; -----> bx = A.f

mov ax,[bx+4] ; ------> ax = A.f->array[1]

mov bx,dx ;-----> restoring bx 

mov dx,bx ; -----> keeping the first bx

mov cx,[bx] ; --------> cx = A.pointer

mov bx,cx ; --------> bx = A.pointer

mov [bx],ax ;--------> *(A.pointer) = A.f->array[1]

mov bx,dx ; ---------> restoring bx

;------------------------------------------------





;------------------------------------------------
;Part three :


mov dx,bx ; -----> keeping the first bx

mov cx,[bx+14] ; ----> cx = A.f

mov bx,cx ; ---------> bx = A.f

mov ax,[bx+6] ; ------> ax = A.f->array[2]

mov bx,dx ; --------> restoring bx

mov cx,[bx+10] ; ------> cx = A.array[4]

mov ax,cx ; -----> A.f->array[2] = A.array[4]



;------------------------------------------------