move(1,6). move(1,8). move(2,7). move(2,9).
move(3,4). move(3,8). move(4,3). move(4,9). move(6,7). move(6,1).
move(7,6). move(7,2). move(8,3). move(8,1). move(9,4). move(9,2).

path(Z,Z,L). 
path(X,Y,Z):-move(X,Z), not(member(Z,L)), path(Z,Y,[Z|L]).
