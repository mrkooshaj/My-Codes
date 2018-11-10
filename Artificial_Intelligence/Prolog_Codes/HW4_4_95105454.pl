list_head([H|_],H).

list_pop([X|Z], Y) :- list_pop_prev(Z, Y, X).        

list_pop_prev([], [], _).
list_pop_prev([X|Z], [Xp|Y], Xp) :- list_pop_prev(Z, Y, X).

list_second([_|T],X) :- list_head(T,X).

list_len([],0).
list_len([_|T],X) :- list_len(T,Y) , X is Y+1.

list_end([H|T],H) :- list_len(T,0).
list_end([_|T],X) :- list_end(T,X).

list_append([], L, L).
list_append([H|T], L, [H|Rest]) :- list_append(T, L, Rest).

list_add_first_last([H|T],L2) :- list_append([H|T],[H],L2).

queue_csp_true([],[]).
queue_csp_true([_|T],[t]) :- list_len(T,0).

queue_csp_true([H|T],M) :- list_second(H,L) , (L == 't' ; L == 'x') , list_second([H|T],L1) , list_head(L1,L2) , (L2 == t ; L2 == x) , queue_csp_true(T,L3) , list_append([t],L3,M).
queue_csp_true([H|T],M) :- list_second(H,L) , (L == 'f' ; L == 'x') , list_second([H|T],L1) , list_head(L1,L2) , (L2 == f ; L2 == x) , queue_csp_false(T,L3), list_append([t],L3,M).

queue_csp_false([],[]).
queue_csp_false([_|T],[f]) :- list_len(T,0).

queue_csp_false([H|T],M) :- list_second(H,L) , (L == 't' ; L == 'x') , list_second([H|T],L1) , list_head(L1,L2) , (L2 == t ; L2 == x) , queue_csp_false(T,L3) , list_append([f],L3,M).
queue_csp_false([H|T],M) :- list_second(H,L) , (L == 'f' ; L == 'x') , list_second([H|T],L1) , list_head(L1,L2) , (L2 == f ; L2 == x) , queue_csp_true(T,L3) , list_append([f],L3,M).

queue_csp([],[]).
queue_csp([H|T],M) :- queue_csp_true([H|T],M) ; queue_csp_false([H|T],M).

csp(L1,K) :- list_add_first_last(L1,L2) , queue_csp(L2,T) , list_head(T,Q) , list_end(T,Qp) , Q == Qp , list_pop(T,K).

 

