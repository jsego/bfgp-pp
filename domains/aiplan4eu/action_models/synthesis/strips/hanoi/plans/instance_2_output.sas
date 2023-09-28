begin_version
3
end_version
begin_metric
0
end_metric
7
begin_variable
var0
-1
2
Atom clear(d1)
NegatedAtom clear(d1)
end_variable
begin_variable
var1
-1
2
Atom clear(d2)
NegatedAtom clear(d2)
end_variable
begin_variable
var2
-1
2
Atom clear(peg1)
NegatedAtom clear(peg1)
end_variable
begin_variable
var3
-1
2
Atom clear(peg2)
NegatedAtom clear(peg2)
end_variable
begin_variable
var4
-1
2
Atom clear(peg3)
NegatedAtom clear(peg3)
end_variable
begin_variable
var5
-1
3
Atom on(d2, peg1)
Atom on(d2, peg2)
Atom on(d2, peg3)
end_variable
begin_variable
var6
-1
5
Atom on(d1, d1)
Atom on(d1, d2)
Atom on(d1, peg1)
Atom on(d1, peg2)
Atom on(d1, peg3)
end_variable
5
begin_mutex_group
2
0 0
6 0
end_mutex_group
begin_mutex_group
2
1 0
6 1
end_mutex_group
begin_mutex_group
3
2 0
6 2
5 0
end_mutex_group
begin_mutex_group
3
3 0
6 3
5 1
end_mutex_group
begin_mutex_group
3
4 0
6 4
5 2
end_mutex_group
begin_state
0
1
1
0
0
0
1
end_state
begin_goal
2
5 2
6 1
end_goal
22
begin_operator
move d1 d2 d1
0
3
0 0 0 1
0 1 -1 0
0 6 1 0
1
end_operator
begin_operator
move d1 d2 peg1
1
0 0
3
0 1 -1 0
0 2 0 1
0 6 1 2
1
end_operator
begin_operator
move d1 d2 peg2
1
0 0
3
0 1 -1 0
0 3 0 1
0 6 1 3
1
end_operator
begin_operator
move d1 d2 peg3
1
0 0
3
0 1 -1 0
0 4 0 1
0 6 1 4
1
end_operator
begin_operator
move d1 peg1 d1
0
3
0 0 0 1
0 2 -1 0
0 6 2 0
1
end_operator
begin_operator
move d1 peg1 d2
1
0 0
3
0 1 0 1
0 2 -1 0
0 6 2 1
1
end_operator
begin_operator
move d1 peg1 peg2
1
0 0
3
0 2 -1 0
0 3 0 1
0 6 2 3
1
end_operator
begin_operator
move d1 peg1 peg3
1
0 0
3
0 2 -1 0
0 4 0 1
0 6 2 4
1
end_operator
begin_operator
move d1 peg2 d1
0
3
0 0 0 1
0 3 -1 0
0 6 3 0
1
end_operator
begin_operator
move d1 peg2 d2
1
0 0
3
0 1 0 1
0 3 -1 0
0 6 3 1
1
end_operator
begin_operator
move d1 peg2 peg1
1
0 0
3
0 2 0 1
0 3 -1 0
0 6 3 2
1
end_operator
begin_operator
move d1 peg2 peg3
1
0 0
3
0 3 -1 0
0 4 0 1
0 6 3 4
1
end_operator
begin_operator
move d1 peg3 d1
0
3
0 0 0 1
0 4 -1 0
0 6 4 0
1
end_operator
begin_operator
move d1 peg3 d2
1
0 0
3
0 1 0 1
0 4 -1 0
0 6 4 1
1
end_operator
begin_operator
move d1 peg3 peg1
1
0 0
3
0 2 0 1
0 4 -1 0
0 6 4 2
1
end_operator
begin_operator
move d1 peg3 peg2
1
0 0
3
0 3 0 1
0 4 -1 0
0 6 4 3
1
end_operator
begin_operator
move d2 peg1 peg2
1
1 0
3
0 2 -1 0
0 3 0 1
0 5 0 1
1
end_operator
begin_operator
move d2 peg1 peg3
1
1 0
3
0 2 -1 0
0 4 0 1
0 5 0 2
1
end_operator
begin_operator
move d2 peg2 peg1
1
1 0
3
0 2 0 1
0 3 -1 0
0 5 1 0
1
end_operator
begin_operator
move d2 peg2 peg3
1
1 0
3
0 3 -1 0
0 4 0 1
0 5 1 2
1
end_operator
begin_operator
move d2 peg3 peg1
1
1 0
3
0 2 0 1
0 4 -1 0
0 5 2 0
1
end_operator
begin_operator
move d2 peg3 peg2
1
1 0
3
0 3 0 1
0 4 -1 0
0 5 2 1
1
end_operator
0
