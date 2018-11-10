gcdCoef(A,B,M,N) :- A =:= B , N is 1 , M is 0.
gcdCoef(A,B,M,N) :- A > B , gcdCoef(A-B,B,X,Y) , M is X , N is Y-X.
gcdCoef(A,B,M,N) :- A < B , gcdCoef(B-A,A,X,Y) , N is X , M is Y-X.