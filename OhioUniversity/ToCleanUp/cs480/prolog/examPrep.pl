fun(prolog).
likes(jane,X):-fun(X).
fun(X):-entertaining(X);says_is_fun(prof_marling,X).
gooddog(X):-trained(X),collie(X).
trained(fred).
collie(fred).

i_o:-write('Enter a value for Y:'),read(Y),nl,
	write('You entered '),write(Y),nl.
fileio:-see('exam.txt'),tell('exam.txt'),seen,told.

double:-
   write('Enter a number to double or q to quit:'),
   read(X), process(X).

process(q):-!.
process(N):-
   D is N*2, write('The double of '), write(N), write(' is '), 
   write(D), nl, double.


exchange(X,Y):- Y is X*0.66.

minimum(X,Y,Z):- X>=Y, Z is Y.
minimum(X,Y,Z):- X<Y, Z is X.
