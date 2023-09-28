begin_version
3
end_version
begin_metric
0
end_metric
11
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
Atom clear(d3)
NegatedAtom clear(d3)
end_variable
begin_variable
var3
-1
2
Atom clear(d4)
NegatedAtom clear(d4)
end_variable
begin_variable
var4
-1
2
Atom clear(peg1)
NegatedAtom clear(peg1)
end_variable
begin_variable
var5
-1
2
Atom clear(peg2)
NegatedAtom clear(peg2)
end_variable
begin_variable
var6
-1
2
Atom clear(peg3)
NegatedAtom clear(peg3)
end_variable
begin_variable
var7
-1
3
Atom on(d4, peg1)
Atom on(d4, peg2)
Atom on(d4, peg3)
end_variable
begin_variable
var8
-1
5
Atom on(d3, d3)
Atom on(d3, d4)
Atom on(d3, peg1)
Atom on(d3, peg2)
Atom on(d3, peg3)
end_variable
begin_variable
var9
-1
6
Atom on(d2, d2)
Atom on(d2, d3)
Atom on(d2, d4)
Atom on(d2, peg1)
Atom on(d2, peg2)
Atom on(d2, peg3)
end_variable
begin_variable
var10
-1
7
Atom on(d1, d1)
Atom on(d1, d2)
Atom on(d1, d3)
Atom on(d1, d4)
Atom on(d1, peg1)
Atom on(d1, peg2)
Atom on(d1, peg3)
end_variable
7
begin_mutex_group
2
0 0
10 0
end_mutex_group
begin_mutex_group
3
1 0
10 1
9 0
end_mutex_group
begin_mutex_group
4
2 0
10 2
9 1
8 0
end_mutex_group
begin_mutex_group
4
3 0
10 3
9 2
8 1
end_mutex_group
begin_mutex_group
5
4 0
10 4
9 3
8 2
7 0
end_mutex_group
begin_mutex_group
5
5 0
10 5
9 4
8 3
7 1
end_mutex_group
begin_mutex_group
5
6 0
10 6
9 5
8 4
7 2
end_mutex_group
begin_state
0
1
1
1
1
0
0
0
1
1
1
end_state
begin_goal
4
7 2
8 1
9 1
10 1
end_goal
83
begin_operator
move d1 d2 d1
0
3
0 0 0 1
0 1 -1 0
0 10 1 0
1
end_operator
begin_operator
move d1 d2 d3
1
0 0
3
0 1 -1 0
0 2 0 1
0 10 1 2
1
end_operator
begin_operator
move d1 d2 d4
1
0 0
3
0 1 -1 0
0 3 0 1
0 10 1 3
1
end_operator
begin_operator
move d1 d2 peg1
1
0 0
3
0 1 -1 0
0 4 0 1
0 10 1 4
1
end_operator
begin_operator
move d1 d2 peg2
1
0 0
3
0 1 -1 0
0 5 0 1
0 10 1 5
1
end_operator
begin_operator
move d1 d2 peg3
1
0 0
3
0 1 -1 0
0 6 0 1
0 10 1 6
1
end_operator
begin_operator
move d1 d3 d1
0
3
0 0 0 1
0 2 -1 0
0 10 2 0
1
end_operator
begin_operator
move d1 d3 d2
1
0 0
3
0 1 0 1
0 2 -1 0
0 10 2 1
1
end_operator
begin_operator
move d1 d3 d4
1
0 0
3
0 2 -1 0
0 3 0 1
0 10 2 3
1
end_operator
begin_operator
move d1 d3 peg1
1
0 0
3
0 2 -1 0
0 4 0 1
0 10 2 4
1
end_operator
begin_operator
move d1 d3 peg2
1
0 0
3
0 2 -1 0
0 5 0 1
0 10 2 5
1
end_operator
begin_operator
move d1 d3 peg3
1
0 0
3
0 2 -1 0
0 6 0 1
0 10 2 6
1
end_operator
begin_operator
move d1 d4 d1
0
3
0 0 0 1
0 3 -1 0
0 10 3 0
1
end_operator
begin_operator
move d1 d4 d2
1
0 0
3
0 1 0 1
0 3 -1 0
0 10 3 1
1
end_operator
begin_operator
move d1 d4 d3
1
0 0
3
0 2 0 1
0 3 -1 0
0 10 3 2
1
end_operator
begin_operator
move d1 d4 peg1
1
0 0
3
0 3 -1 0
0 4 0 1
0 10 3 4
1
end_operator
begin_operator
move d1 d4 peg2
1
0 0
3
0 3 -1 0
0 5 0 1
0 10 3 5
1
end_operator
begin_operator
move d1 d4 peg3
1
0 0
3
0 3 -1 0
0 6 0 1
0 10 3 6
1
end_operator
begin_operator
move d1 peg1 d1
0
3
0 0 0 1
0 4 -1 0
0 10 4 0
1
end_operator
begin_operator
move d1 peg1 d2
1
0 0
3
0 1 0 1
0 4 -1 0
0 10 4 1
1
end_operator
begin_operator
move d1 peg1 d3
1
0 0
3
0 2 0 1
0 4 -1 0
0 10 4 2
1
end_operator
begin_operator
move d1 peg1 d4
1
0 0
3
0 3 0 1
0 4 -1 0
0 10 4 3
1
end_operator
begin_operator
move d1 peg1 peg2
1
0 0
3
0 4 -1 0
0 5 0 1
0 10 4 5
1
end_operator
begin_operator
move d1 peg1 peg3
1
0 0
3
0 4 -1 0
0 6 0 1
0 10 4 6
1
end_operator
begin_operator
move d1 peg2 d1
0
3
0 0 0 1
0 5 -1 0
0 10 5 0
1
end_operator
begin_operator
move d1 peg2 d2
1
0 0
3
0 1 0 1
0 5 -1 0
0 10 5 1
1
end_operator
begin_operator
move d1 peg2 d3
1
0 0
3
0 2 0 1
0 5 -1 0
0 10 5 2
1
end_operator
begin_operator
move d1 peg2 d4
1
0 0
3
0 3 0 1
0 5 -1 0
0 10 5 3
1
end_operator
begin_operator
move d1 peg2 peg1
1
0 0
3
0 4 0 1
0 5 -1 0
0 10 5 4
1
end_operator
begin_operator
move d1 peg2 peg3
1
0 0
3
0 5 -1 0
0 6 0 1
0 10 5 6
1
end_operator
begin_operator
move d1 peg3 d1
0
3
0 0 0 1
0 6 -1 0
0 10 6 0
1
end_operator
begin_operator
move d1 peg3 d2
1
0 0
3
0 1 0 1
0 6 -1 0
0 10 6 1
1
end_operator
begin_operator
move d1 peg3 d3
1
0 0
3
0 2 0 1
0 6 -1 0
0 10 6 2
1
end_operator
begin_operator
move d1 peg3 d4
1
0 0
3
0 3 0 1
0 6 -1 0
0 10 6 3
1
end_operator
begin_operator
move d1 peg3 peg1
1
0 0
3
0 4 0 1
0 6 -1 0
0 10 6 4
1
end_operator
begin_operator
move d1 peg3 peg2
1
0 0
3
0 5 0 1
0 6 -1 0
0 10 6 5
1
end_operator
begin_operator
move d2 d3 d2
0
3
0 1 0 1
0 2 -1 0
0 9 1 0
1
end_operator
begin_operator
move d2 d3 d4
1
1 0
3
0 2 -1 0
0 3 0 1
0 9 1 2
1
end_operator
begin_operator
move d2 d3 peg1
1
1 0
3
0 2 -1 0
0 4 0 1
0 9 1 3
1
end_operator
begin_operator
move d2 d3 peg2
1
1 0
3
0 2 -1 0
0 5 0 1
0 9 1 4
1
end_operator
begin_operator
move d2 d3 peg3
1
1 0
3
0 2 -1 0
0 6 0 1
0 9 1 5
1
end_operator
begin_operator
move d2 d4 d2
0
3
0 1 0 1
0 3 -1 0
0 9 2 0
1
end_operator
begin_operator
move d2 d4 d3
1
1 0
3
0 2 0 1
0 3 -1 0
0 9 2 1
1
end_operator
begin_operator
move d2 d4 peg1
1
1 0
3
0 3 -1 0
0 4 0 1
0 9 2 3
1
end_operator
begin_operator
move d2 d4 peg2
1
1 0
3
0 3 -1 0
0 5 0 1
0 9 2 4
1
end_operator
begin_operator
move d2 d4 peg3
1
1 0
3
0 3 -1 0
0 6 0 1
0 9 2 5
1
end_operator
begin_operator
move d2 peg1 d2
0
3
0 1 0 1
0 4 -1 0
0 9 3 0
1
end_operator
begin_operator
move d2 peg1 d3
1
1 0
3
0 2 0 1
0 4 -1 0
0 9 3 1
1
end_operator
begin_operator
move d2 peg1 d4
1
1 0
3
0 3 0 1
0 4 -1 0
0 9 3 2
1
end_operator
begin_operator
move d2 peg1 peg2
1
1 0
3
0 4 -1 0
0 5 0 1
0 9 3 4
1
end_operator
begin_operator
move d2 peg1 peg3
1
1 0
3
0 4 -1 0
0 6 0 1
0 9 3 5
1
end_operator
begin_operator
move d2 peg2 d2
0
3
0 1 0 1
0 5 -1 0
0 9 4 0
1
end_operator
begin_operator
move d2 peg2 d3
1
1 0
3
0 2 0 1
0 5 -1 0
0 9 4 1
1
end_operator
begin_operator
move d2 peg2 d4
1
1 0
3
0 3 0 1
0 5 -1 0
0 9 4 2
1
end_operator
begin_operator
move d2 peg2 peg1
1
1 0
3
0 4 0 1
0 5 -1 0
0 9 4 3
1
end_operator
begin_operator
move d2 peg2 peg3
1
1 0
3
0 5 -1 0
0 6 0 1
0 9 4 5
1
end_operator
begin_operator
move d2 peg3 d2
0
3
0 1 0 1
0 6 -1 0
0 9 5 0
1
end_operator
begin_operator
move d2 peg3 d3
1
1 0
3
0 2 0 1
0 6 -1 0
0 9 5 1
1
end_operator
begin_operator
move d2 peg3 d4
1
1 0
3
0 3 0 1
0 6 -1 0
0 9 5 2
1
end_operator
begin_operator
move d2 peg3 peg1
1
1 0
3
0 4 0 1
0 6 -1 0
0 9 5 3
1
end_operator
begin_operator
move d2 peg3 peg2
1
1 0
3
0 5 0 1
0 6 -1 0
0 9 5 4
1
end_operator
begin_operator
move d3 d4 d3
0
3
0 2 0 1
0 3 -1 0
0 8 1 0
1
end_operator
begin_operator
move d3 d4 peg1
1
2 0
3
0 3 -1 0
0 4 0 1
0 8 1 2
1
end_operator
begin_operator
move d3 d4 peg2
1
2 0
3
0 3 -1 0
0 5 0 1
0 8 1 3
1
end_operator
begin_operator
move d3 d4 peg3
1
2 0
3
0 3 -1 0
0 6 0 1
0 8 1 4
1
end_operator
begin_operator
move d3 peg1 d3
0
3
0 2 0 1
0 4 -1 0
0 8 2 0
1
end_operator
begin_operator
move d3 peg1 d4
1
2 0
3
0 3 0 1
0 4 -1 0
0 8 2 1
1
end_operator
begin_operator
move d3 peg1 peg2
1
2 0
3
0 4 -1 0
0 5 0 1
0 8 2 3
1
end_operator
begin_operator
move d3 peg1 peg3
1
2 0
3
0 4 -1 0
0 6 0 1
0 8 2 4
1
end_operator
begin_operator
move d3 peg2 d3
0
3
0 2 0 1
0 5 -1 0
0 8 3 0
1
end_operator
begin_operator
move d3 peg2 d4
1
2 0
3
0 3 0 1
0 5 -1 0
0 8 3 1
1
end_operator
begin_operator
move d3 peg2 peg1
1
2 0
3
0 4 0 1
0 5 -1 0
0 8 3 2
1
end_operator
begin_operator
move d3 peg2 peg3
1
2 0
3
0 5 -1 0
0 6 0 1
0 8 3 4
1
end_operator
begin_operator
move d3 peg3 d3
0
3
0 2 0 1
0 6 -1 0
0 8 4 0
1
end_operator
begin_operator
move d3 peg3 d4
1
2 0
3
0 3 0 1
0 6 -1 0
0 8 4 1
1
end_operator
begin_operator
move d3 peg3 peg1
1
2 0
3
0 4 0 1
0 6 -1 0
0 8 4 2
1
end_operator
begin_operator
move d3 peg3 peg2
1
2 0
3
0 5 0 1
0 6 -1 0
0 8 4 3
1
end_operator
begin_operator
move d4 peg1 peg2
1
3 0
3
0 4 -1 0
0 5 0 1
0 7 0 1
1
end_operator
begin_operator
move d4 peg1 peg3
1
3 0
3
0 4 -1 0
0 6 0 1
0 7 0 2
1
end_operator
begin_operator
move d4 peg2 peg1
1
3 0
3
0 4 0 1
0 5 -1 0
0 7 1 0
1
end_operator
begin_operator
move d4 peg2 peg3
1
3 0
3
0 5 -1 0
0 6 0 1
0 7 1 2
1
end_operator
begin_operator
move d4 peg3 peg1
1
3 0
3
0 4 0 1
0 6 -1 0
0 7 2 0
1
end_operator
begin_operator
move d4 peg3 peg2
1
3 0
3
0 5 0 1
0 6 -1 0
0 7 2 1
1
end_operator
0
