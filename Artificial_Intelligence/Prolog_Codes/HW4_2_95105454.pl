gcd(X,0,X) :-!.
gcd(0,X,X) :-!.
gcd(X,X,X) :-!.
gcd(A,B,X) :- A > B , Y is mod(A,B) , gcd(Y,B,X).
gcd(A,B,X) :- A < B , gcd(B,A,X).

lcm(A,B,X) :- gcd(A,B,Z) , Y is A / Z , X is Y * B.

lcm_list([],1).
lcm_list([H|T],X) :- lcm_list(T,Y) , lcm(H,Y,X).

list_append([], L, L).
list_append([H|T], L, [H|Rest]) :- list_append(T, L, Rest).

list_len([],0).
list_len([_|T],X) :- list_len(T,Y) , X is Y+1.

minus_all_list([],_,[]).
minus_all_list([H|T],C,L) :- X is H - C , minus_all_list(T,C,Y) , list_append(Y,[X],L).

max_long_list([],_,[]).
max_long_list([H|T],Max,L2) :- H > Max , max_long_list(T,H,L3) , list_append([H],L3,L2).
max_long_list([H|T],Max,L2) :- H =< Max , max_long_list(T,Max,L3) , list_append([Max],L3,L2).

max_list(L1,L2) :- max_long_list(L1,0,L2).

equal_list([],_,[]).
equal_list([H1|T1],Cnt,L2) :- H1 \= Cnt ,Cntp is Cnt + 1 , equal_list(T1,Cntp,L2).
equal_list([H1|T1],Cnt,L2) :- H1 == Cnt ,Cntp is Cnt + 1 , equal_list(T1,Cntp,L3) , list_append(L3,[Cnt],L2).

eq_list(L1,L2) :- equal_list(L1,1,L2).

perm_list(L1,L2) :- max_list(L1,L3) , eq_list(L3,L2).

list_head([],[]).
list_head([H|_],H).

list_minus([],[]).
list_minus([X],[X]).
list_minus([H|T],L2) :- list_head(T,X) , Y is H - X , list_minus(T,L3) , list_append([Y],L3,L2).

perm_list_minus(L1,L2) :- perm_list(L1,L3), list_minus(L3,L2).

permutationLength(Perm,L) :- perm_list_minus(Perm,L3) , lcm_list(L3,L).