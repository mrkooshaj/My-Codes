list_pop([X|Z], Y) :- list_pop_prev(Z, Y, X).        

list_pop_prev([], [], _).
list_pop_prev([X|Z], [Xp|Y], Xp) :- list_pop_prev(Z, Y, X).

list_len([],0).
list_len([_|T],X) :- list_len(T,Y) , X is Y+1.

list_append([], L, L).
list_append([H|T], L, [H|Rest]) :- list_append(T, L, Rest).

list_mulbylen([],0,[]) :-!.
list_mulbylen([H|T],Len,L2) :- list_append([H1|_],L3,L2) , H1 is H*Len ,Y is Len-1 , list_mulbylen(T,Y,L3).

list_derivative([],[]).
list_derivative(L1,L2) :- list_pop(L1,L3) , list_len(L3,T), list_mulbylen(L3,T,L2).

add_poly_eqlen([],[],[]).
add_poly_eqlen([H1|T1],[H2|T2],L3) :- list_append([H5|_],L2,L3) , add_poly_eqlen(T1,T2,L2) , H5 is H1 + H2.

poly_extend_to_len(L1,Len,L2) :- list_len(L1,Len) , list_append(L1,[],L2).
poly_extend_to_len(L1,Len,L2) :- list_append([0],L1,L3), poly_extend_to_len(L3,Len,L2) .

poly_extend_to_len_rev(L1,Len,L2) :- list_len(L1,Len) , list_append(L1,[],L2).
poly_extend_to_len_rev(L1,Len,L2) :- list_append(L1,[0],L3), poly_extend_to_len_rev(L3,Len,L2) .

add_poly(L1,L2,L3) :- list_len(L1,Y) , list_len(L2,Z) , Y =< Z , poly_extend_to_len(L1,Z,L4), add_poly_eqlen(L4,L2,L3) . 
add_poly(L1,L2,L3) :- list_len(L1,Y) , list_len(L2,Z) , Y > Z , poly_extend_to_len(L2,Y,L4), add_poly_eqlen(L1,L4,L3).

%has_multiple_root(L) :- poly_gcd(L,L1,L2) , list_derivative(L,L1) , list_len(L2,Y) , Y > 1.

mul_cnst([],_,[]).
mul_cnst([H1|T1],Z,L2) :- Y is H1*Z , list_append([Y|_],L3,L2) , mul_cnst(T1,Z,L3).

list_pop2([_|T], T).

list_mul([],_,[]).
list_mul(_,[],[]).
list_mul([X],[Y],[Z]) :- Z is X * Y.
list_mul([H1|T1],L2,L3) :- mul_cnst(L2,H1,L4) , list_len(T1,X) , list_len(L2,Y) , Z is X + Y , poly_extend_to_len_rev(L4,Z,L5) , list_mul(T1,L2,L6) , add_poly(L5,L6,L3).

quotient_first(L1,L2,L3) :- list_len(L1,X) , list_len(L2,Y) , X < Y , list_append([],[],L3).
quotient_first([H1|T1],[H2|T2],L3) :- P is H1/H2 , list_append([],[P],L6) , list_len(T1,Y) , list_len(T2,X), Z is Y - X + 1, poly_extend_to_len_rev(L6,Z,L3). 

remove_zero([],[]).
remove_zero([H1|T1],L) :- H1 == 0 , remove_zero(T1,L).
remove_zero([H1|T1],L) :- H1 == 0.0 , remove_zero(T1,L).
remove_zero([H1|T1],L) :- H1 \= 0 , list_append([H1],T1,L).

quotient_all(L1,L2,L3) :- list_len(L1,X) , list_len(L2,Y) , X < Y , list_append([],[],L3).
quotient_all(L1,L2,L3) :- list_len(L1,X) , list_len(L2,Y) , X == Y , quotient_first(L1,L2,L3).
quotient_all([H1|T1],[H2|T2],L3) :- quotient_first([H1|T1],[H2|T2],L4) , list_mul([H2|T2],L4,L5) , mul_cnst(L5,-1,L6) , add_poly([H1|T1],L6,L7) , remove_zero(L7,L8) , quotient_all(L8,[H2|T2],L9) , add_poly(L4,L9,L3).

div_list(L1,L2,Q,R) :- quotient_all(L1,L2,Q) , list_mul(Q,L2,L4) , mul_cnst(L4,-1,L5) , add_poly(L5,L1,L6) , remove_zero(L6,R).

gcd_list([],L2,L2) :-!.
gcd_list(L1,[],L1) :-!.
gcd_list(L1,L1,L1) :-!.
gcd_list(L1,L2,L3) :- list_len(L1,Z) , list_len(L2,Y) , Z < Y , gcd_list(L2,L1,L3).
gcd_list(L1,L2,L3) :- list_len(L1,Z) , list_len(L2,Y) , Z >= Y , div_list(L1,L2,_,R) , gcd_list(L2,R,L3).

gcd_poly_deg(L1,L2,X) :- gcd_list(L1,L2,L3) , list_len(L3,Y) , X is Y - 1.

nequals(X,Y) :- X \= Y.

gcd_with_der_deg(L1,X) :- list_derivative(L1,L2) , gcd_poly_deg(L1,L2,X).

has_multiple_root(L1) :- gcd_with_der_deg(L1,X) ,!, X \= 0.