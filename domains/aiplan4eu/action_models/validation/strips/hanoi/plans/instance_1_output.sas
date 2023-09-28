begin_version
3
end_version
begin_metric
0
end_metric
15
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
Atom clear(d5)
NegatedAtom clear(d5)
end_variable
begin_variable
var5
-1
2
Atom clear(d6)
NegatedAtom clear(d6)
end_variable
begin_variable
var6
-1
2
Atom clear(peg1)
NegatedAtom clear(peg1)
end_variable
begin_variable
var7
-1
2
Atom clear(peg2)
NegatedAtom clear(peg2)
end_variable
begin_variable
var8
-1
2
Atom clear(peg3)
NegatedAtom clear(peg3)
end_variable
begin_variable
var9
-1
3
Atom on(d6, peg1)
Atom on(d6, peg2)
Atom on(d6, peg3)
end_variable
begin_variable
var10
-1
5
Atom on(d5, d5)
Atom on(d5, d6)
Atom on(d5, peg1)
Atom on(d5, peg2)
Atom on(d5, peg3)
end_variable
begin_variable
var11
-1
6
Atom on(d4, d4)
Atom on(d4, d5)
Atom on(d4, d6)
Atom on(d4, peg1)
Atom on(d4, peg2)
Atom on(d4, peg3)
end_variable
begin_variable
var12
-1
7
Atom on(d3, d3)
Atom on(d3, d4)
Atom on(d3, d5)
Atom on(d3, d6)
Atom on(d3, peg1)
Atom on(d3, peg2)
Atom on(d3, peg3)
end_variable
begin_variable
var13
-1
8
Atom on(d2, d2)
Atom on(d2, d3)
Atom on(d2, d4)
Atom on(d2, d5)
Atom on(d2, d6)
Atom on(d2, peg1)
Atom on(d2, peg2)
Atom on(d2, peg3)
end_variable
begin_variable
var14
-1
9
Atom on(d1, d1)
Atom on(d1, d2)
Atom on(d1, d3)
Atom on(d1, d4)
Atom on(d1, d5)
Atom on(d1, d6)
Atom on(d1, peg1)
Atom on(d1, peg2)
Atom on(d1, peg3)
end_variable
9
begin_mutex_group
2
0 0
14 0
end_mutex_group
begin_mutex_group
3
1 0
14 1
13 0
end_mutex_group
begin_mutex_group
4
2 0
14 2
13 1
12 0
end_mutex_group
begin_mutex_group
5
3 0
14 3
13 2
12 1
11 0
end_mutex_group
begin_mutex_group
6
4 0
14 4
13 3
12 2
11 1
10 0
end_mutex_group
begin_mutex_group
6
5 0
14 5
13 4
12 3
11 2
10 1
end_mutex_group
begin_mutex_group
7
6 0
14 6
13 5
12 4
11 3
10 2
9 0
end_mutex_group
begin_mutex_group
7
7 0
14 7
13 6
12 5
11 4
10 3
9 1
end_mutex_group
begin_mutex_group
7
8 0
14 8
13 7
12 6
11 5
10 4
9 2
end_mutex_group
begin_state
0
1
1
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
1
1
end_state
begin_goal
6
9 2
10 1
11 1
12 1
13 1
14 1
end_goal
196
begin_operator
move d1 d2 d1
0
3
0 0 0 1
0 1 -1 0
0 14 1 0
1
end_operator
begin_operator
move d1 d2 d3
1
0 0
3
0 1 -1 0
0 2 0 1
0 14 1 2
1
end_operator
begin_operator
move d1 d2 d4
1
0 0
3
0 1 -1 0
0 3 0 1
0 14 1 3
1
end_operator
begin_operator
move d1 d2 d5
1
0 0
3
0 1 -1 0
0 4 0 1
0 14 1 4
1
end_operator
begin_operator
move d1 d2 d6
1
0 0
3
0 1 -1 0
0 5 0 1
0 14 1 5
1
end_operator
begin_operator
move d1 d2 peg1
1
0 0
3
0 1 -1 0
0 6 0 1
0 14 1 6
1
end_operator
begin_operator
move d1 d2 peg2
1
0 0
3
0 1 -1 0
0 7 0 1
0 14 1 7
1
end_operator
begin_operator
move d1 d2 peg3
1
0 0
3
0 1 -1 0
0 8 0 1
0 14 1 8
1
end_operator
begin_operator
move d1 d3 d1
0
3
0 0 0 1
0 2 -1 0
0 14 2 0
1
end_operator
begin_operator
move d1 d3 d2
1
0 0
3
0 1 0 1
0 2 -1 0
0 14 2 1
1
end_operator
begin_operator
move d1 d3 d4
1
0 0
3
0 2 -1 0
0 3 0 1
0 14 2 3
1
end_operator
begin_operator
move d1 d3 d5
1
0 0
3
0 2 -1 0
0 4 0 1
0 14 2 4
1
end_operator
begin_operator
move d1 d3 d6
1
0 0
3
0 2 -1 0
0 5 0 1
0 14 2 5
1
end_operator
begin_operator
move d1 d3 peg1
1
0 0
3
0 2 -1 0
0 6 0 1
0 14 2 6
1
end_operator
begin_operator
move d1 d3 peg2
1
0 0
3
0 2 -1 0
0 7 0 1
0 14 2 7
1
end_operator
begin_operator
move d1 d3 peg3
1
0 0
3
0 2 -1 0
0 8 0 1
0 14 2 8
1
end_operator
begin_operator
move d1 d4 d1
0
3
0 0 0 1
0 3 -1 0
0 14 3 0
1
end_operator
begin_operator
move d1 d4 d2
1
0 0
3
0 1 0 1
0 3 -1 0
0 14 3 1
1
end_operator
begin_operator
move d1 d4 d3
1
0 0
3
0 2 0 1
0 3 -1 0
0 14 3 2
1
end_operator
begin_operator
move d1 d4 d5
1
0 0
3
0 3 -1 0
0 4 0 1
0 14 3 4
1
end_operator
begin_operator
move d1 d4 d6
1
0 0
3
0 3 -1 0
0 5 0 1
0 14 3 5
1
end_operator
begin_operator
move d1 d4 peg1
1
0 0
3
0 3 -1 0
0 6 0 1
0 14 3 6
1
end_operator
begin_operator
move d1 d4 peg2
1
0 0
3
0 3 -1 0
0 7 0 1
0 14 3 7
1
end_operator
begin_operator
move d1 d4 peg3
1
0 0
3
0 3 -1 0
0 8 0 1
0 14 3 8
1
end_operator
begin_operator
move d1 d5 d1
0
3
0 0 0 1
0 4 -1 0
0 14 4 0
1
end_operator
begin_operator
move d1 d5 d2
1
0 0
3
0 1 0 1
0 4 -1 0
0 14 4 1
1
end_operator
begin_operator
move d1 d5 d3
1
0 0
3
0 2 0 1
0 4 -1 0
0 14 4 2
1
end_operator
begin_operator
move d1 d5 d4
1
0 0
3
0 3 0 1
0 4 -1 0
0 14 4 3
1
end_operator
begin_operator
move d1 d5 d6
1
0 0
3
0 4 -1 0
0 5 0 1
0 14 4 5
1
end_operator
begin_operator
move d1 d5 peg1
1
0 0
3
0 4 -1 0
0 6 0 1
0 14 4 6
1
end_operator
begin_operator
move d1 d5 peg2
1
0 0
3
0 4 -1 0
0 7 0 1
0 14 4 7
1
end_operator
begin_operator
move d1 d5 peg3
1
0 0
3
0 4 -1 0
0 8 0 1
0 14 4 8
1
end_operator
begin_operator
move d1 d6 d1
0
3
0 0 0 1
0 5 -1 0
0 14 5 0
1
end_operator
begin_operator
move d1 d6 d2
1
0 0
3
0 1 0 1
0 5 -1 0
0 14 5 1
1
end_operator
begin_operator
move d1 d6 d3
1
0 0
3
0 2 0 1
0 5 -1 0
0 14 5 2
1
end_operator
begin_operator
move d1 d6 d4
1
0 0
3
0 3 0 1
0 5 -1 0
0 14 5 3
1
end_operator
begin_operator
move d1 d6 d5
1
0 0
3
0 4 0 1
0 5 -1 0
0 14 5 4
1
end_operator
begin_operator
move d1 d6 peg1
1
0 0
3
0 5 -1 0
0 6 0 1
0 14 5 6
1
end_operator
begin_operator
move d1 d6 peg2
1
0 0
3
0 5 -1 0
0 7 0 1
0 14 5 7
1
end_operator
begin_operator
move d1 d6 peg3
1
0 0
3
0 5 -1 0
0 8 0 1
0 14 5 8
1
end_operator
begin_operator
move d1 peg1 d1
0
3
0 0 0 1
0 6 -1 0
0 14 6 0
1
end_operator
begin_operator
move d1 peg1 d2
1
0 0
3
0 1 0 1
0 6 -1 0
0 14 6 1
1
end_operator
begin_operator
move d1 peg1 d3
1
0 0
3
0 2 0 1
0 6 -1 0
0 14 6 2
1
end_operator
begin_operator
move d1 peg1 d4
1
0 0
3
0 3 0 1
0 6 -1 0
0 14 6 3
1
end_operator
begin_operator
move d1 peg1 d5
1
0 0
3
0 4 0 1
0 6 -1 0
0 14 6 4
1
end_operator
begin_operator
move d1 peg1 d6
1
0 0
3
0 5 0 1
0 6 -1 0
0 14 6 5
1
end_operator
begin_operator
move d1 peg1 peg2
1
0 0
3
0 6 -1 0
0 7 0 1
0 14 6 7
1
end_operator
begin_operator
move d1 peg1 peg3
1
0 0
3
0 6 -1 0
0 8 0 1
0 14 6 8
1
end_operator
begin_operator
move d1 peg2 d1
0
3
0 0 0 1
0 7 -1 0
0 14 7 0
1
end_operator
begin_operator
move d1 peg2 d2
1
0 0
3
0 1 0 1
0 7 -1 0
0 14 7 1
1
end_operator
begin_operator
move d1 peg2 d3
1
0 0
3
0 2 0 1
0 7 -1 0
0 14 7 2
1
end_operator
begin_operator
move d1 peg2 d4
1
0 0
3
0 3 0 1
0 7 -1 0
0 14 7 3
1
end_operator
begin_operator
move d1 peg2 d5
1
0 0
3
0 4 0 1
0 7 -1 0
0 14 7 4
1
end_operator
begin_operator
move d1 peg2 d6
1
0 0
3
0 5 0 1
0 7 -1 0
0 14 7 5
1
end_operator
begin_operator
move d1 peg2 peg1
1
0 0
3
0 6 0 1
0 7 -1 0
0 14 7 6
1
end_operator
begin_operator
move d1 peg2 peg3
1
0 0
3
0 7 -1 0
0 8 0 1
0 14 7 8
1
end_operator
begin_operator
move d1 peg3 d1
0
3
0 0 0 1
0 8 -1 0
0 14 8 0
1
end_operator
begin_operator
move d1 peg3 d2
1
0 0
3
0 1 0 1
0 8 -1 0
0 14 8 1
1
end_operator
begin_operator
move d1 peg3 d3
1
0 0
3
0 2 0 1
0 8 -1 0
0 14 8 2
1
end_operator
begin_operator
move d1 peg3 d4
1
0 0
3
0 3 0 1
0 8 -1 0
0 14 8 3
1
end_operator
begin_operator
move d1 peg3 d5
1
0 0
3
0 4 0 1
0 8 -1 0
0 14 8 4
1
end_operator
begin_operator
move d1 peg3 d6
1
0 0
3
0 5 0 1
0 8 -1 0
0 14 8 5
1
end_operator
begin_operator
move d1 peg3 peg1
1
0 0
3
0 6 0 1
0 8 -1 0
0 14 8 6
1
end_operator
begin_operator
move d1 peg3 peg2
1
0 0
3
0 7 0 1
0 8 -1 0
0 14 8 7
1
end_operator
begin_operator
move d2 d3 d2
0
3
0 1 0 1
0 2 -1 0
0 13 1 0
1
end_operator
begin_operator
move d2 d3 d4
1
1 0
3
0 2 -1 0
0 3 0 1
0 13 1 2
1
end_operator
begin_operator
move d2 d3 d5
1
1 0
3
0 2 -1 0
0 4 0 1
0 13 1 3
1
end_operator
begin_operator
move d2 d3 d6
1
1 0
3
0 2 -1 0
0 5 0 1
0 13 1 4
1
end_operator
begin_operator
move d2 d3 peg1
1
1 0
3
0 2 -1 0
0 6 0 1
0 13 1 5
1
end_operator
begin_operator
move d2 d3 peg2
1
1 0
3
0 2 -1 0
0 7 0 1
0 13 1 6
1
end_operator
begin_operator
move d2 d3 peg3
1
1 0
3
0 2 -1 0
0 8 0 1
0 13 1 7
1
end_operator
begin_operator
move d2 d4 d2
0
3
0 1 0 1
0 3 -1 0
0 13 2 0
1
end_operator
begin_operator
move d2 d4 d3
1
1 0
3
0 2 0 1
0 3 -1 0
0 13 2 1
1
end_operator
begin_operator
move d2 d4 d5
1
1 0
3
0 3 -1 0
0 4 0 1
0 13 2 3
1
end_operator
begin_operator
move d2 d4 d6
1
1 0
3
0 3 -1 0
0 5 0 1
0 13 2 4
1
end_operator
begin_operator
move d2 d4 peg1
1
1 0
3
0 3 -1 0
0 6 0 1
0 13 2 5
1
end_operator
begin_operator
move d2 d4 peg2
1
1 0
3
0 3 -1 0
0 7 0 1
0 13 2 6
1
end_operator
begin_operator
move d2 d4 peg3
1
1 0
3
0 3 -1 0
0 8 0 1
0 13 2 7
1
end_operator
begin_operator
move d2 d5 d2
0
3
0 1 0 1
0 4 -1 0
0 13 3 0
1
end_operator
begin_operator
move d2 d5 d3
1
1 0
3
0 2 0 1
0 4 -1 0
0 13 3 1
1
end_operator
begin_operator
move d2 d5 d4
1
1 0
3
0 3 0 1
0 4 -1 0
0 13 3 2
1
end_operator
begin_operator
move d2 d5 d6
1
1 0
3
0 4 -1 0
0 5 0 1
0 13 3 4
1
end_operator
begin_operator
move d2 d5 peg1
1
1 0
3
0 4 -1 0
0 6 0 1
0 13 3 5
1
end_operator
begin_operator
move d2 d5 peg2
1
1 0
3
0 4 -1 0
0 7 0 1
0 13 3 6
1
end_operator
begin_operator
move d2 d5 peg3
1
1 0
3
0 4 -1 0
0 8 0 1
0 13 3 7
1
end_operator
begin_operator
move d2 d6 d2
0
3
0 1 0 1
0 5 -1 0
0 13 4 0
1
end_operator
begin_operator
move d2 d6 d3
1
1 0
3
0 2 0 1
0 5 -1 0
0 13 4 1
1
end_operator
begin_operator
move d2 d6 d4
1
1 0
3
0 3 0 1
0 5 -1 0
0 13 4 2
1
end_operator
begin_operator
move d2 d6 d5
1
1 0
3
0 4 0 1
0 5 -1 0
0 13 4 3
1
end_operator
begin_operator
move d2 d6 peg1
1
1 0
3
0 5 -1 0
0 6 0 1
0 13 4 5
1
end_operator
begin_operator
move d2 d6 peg2
1
1 0
3
0 5 -1 0
0 7 0 1
0 13 4 6
1
end_operator
begin_operator
move d2 d6 peg3
1
1 0
3
0 5 -1 0
0 8 0 1
0 13 4 7
1
end_operator
begin_operator
move d2 peg1 d2
0
3
0 1 0 1
0 6 -1 0
0 13 5 0
1
end_operator
begin_operator
move d2 peg1 d3
1
1 0
3
0 2 0 1
0 6 -1 0
0 13 5 1
1
end_operator
begin_operator
move d2 peg1 d4
1
1 0
3
0 3 0 1
0 6 -1 0
0 13 5 2
1
end_operator
begin_operator
move d2 peg1 d5
1
1 0
3
0 4 0 1
0 6 -1 0
0 13 5 3
1
end_operator
begin_operator
move d2 peg1 d6
1
1 0
3
0 5 0 1
0 6 -1 0
0 13 5 4
1
end_operator
begin_operator
move d2 peg1 peg2
1
1 0
3
0 6 -1 0
0 7 0 1
0 13 5 6
1
end_operator
begin_operator
move d2 peg1 peg3
1
1 0
3
0 6 -1 0
0 8 0 1
0 13 5 7
1
end_operator
begin_operator
move d2 peg2 d2
0
3
0 1 0 1
0 7 -1 0
0 13 6 0
1
end_operator
begin_operator
move d2 peg2 d3
1
1 0
3
0 2 0 1
0 7 -1 0
0 13 6 1
1
end_operator
begin_operator
move d2 peg2 d4
1
1 0
3
0 3 0 1
0 7 -1 0
0 13 6 2
1
end_operator
begin_operator
move d2 peg2 d5
1
1 0
3
0 4 0 1
0 7 -1 0
0 13 6 3
1
end_operator
begin_operator
move d2 peg2 d6
1
1 0
3
0 5 0 1
0 7 -1 0
0 13 6 4
1
end_operator
begin_operator
move d2 peg2 peg1
1
1 0
3
0 6 0 1
0 7 -1 0
0 13 6 5
1
end_operator
begin_operator
move d2 peg2 peg3
1
1 0
3
0 7 -1 0
0 8 0 1
0 13 6 7
1
end_operator
begin_operator
move d2 peg3 d2
0
3
0 1 0 1
0 8 -1 0
0 13 7 0
1
end_operator
begin_operator
move d2 peg3 d3
1
1 0
3
0 2 0 1
0 8 -1 0
0 13 7 1
1
end_operator
begin_operator
move d2 peg3 d4
1
1 0
3
0 3 0 1
0 8 -1 0
0 13 7 2
1
end_operator
begin_operator
move d2 peg3 d5
1
1 0
3
0 4 0 1
0 8 -1 0
0 13 7 3
1
end_operator
begin_operator
move d2 peg3 d6
1
1 0
3
0 5 0 1
0 8 -1 0
0 13 7 4
1
end_operator
begin_operator
move d2 peg3 peg1
1
1 0
3
0 6 0 1
0 8 -1 0
0 13 7 5
1
end_operator
begin_operator
move d2 peg3 peg2
1
1 0
3
0 7 0 1
0 8 -1 0
0 13 7 6
1
end_operator
begin_operator
move d3 d4 d3
0
3
0 2 0 1
0 3 -1 0
0 12 1 0
1
end_operator
begin_operator
move d3 d4 d5
1
2 0
3
0 3 -1 0
0 4 0 1
0 12 1 2
1
end_operator
begin_operator
move d3 d4 d6
1
2 0
3
0 3 -1 0
0 5 0 1
0 12 1 3
1
end_operator
begin_operator
move d3 d4 peg1
1
2 0
3
0 3 -1 0
0 6 0 1
0 12 1 4
1
end_operator
begin_operator
move d3 d4 peg2
1
2 0
3
0 3 -1 0
0 7 0 1
0 12 1 5
1
end_operator
begin_operator
move d3 d4 peg3
1
2 0
3
0 3 -1 0
0 8 0 1
0 12 1 6
1
end_operator
begin_operator
move d3 d5 d3
0
3
0 2 0 1
0 4 -1 0
0 12 2 0
1
end_operator
begin_operator
move d3 d5 d4
1
2 0
3
0 3 0 1
0 4 -1 0
0 12 2 1
1
end_operator
begin_operator
move d3 d5 d6
1
2 0
3
0 4 -1 0
0 5 0 1
0 12 2 3
1
end_operator
begin_operator
move d3 d5 peg1
1
2 0
3
0 4 -1 0
0 6 0 1
0 12 2 4
1
end_operator
begin_operator
move d3 d5 peg2
1
2 0
3
0 4 -1 0
0 7 0 1
0 12 2 5
1
end_operator
begin_operator
move d3 d5 peg3
1
2 0
3
0 4 -1 0
0 8 0 1
0 12 2 6
1
end_operator
begin_operator
move d3 d6 d3
0
3
0 2 0 1
0 5 -1 0
0 12 3 0
1
end_operator
begin_operator
move d3 d6 d4
1
2 0
3
0 3 0 1
0 5 -1 0
0 12 3 1
1
end_operator
begin_operator
move d3 d6 d5
1
2 0
3
0 4 0 1
0 5 -1 0
0 12 3 2
1
end_operator
begin_operator
move d3 d6 peg1
1
2 0
3
0 5 -1 0
0 6 0 1
0 12 3 4
1
end_operator
begin_operator
move d3 d6 peg2
1
2 0
3
0 5 -1 0
0 7 0 1
0 12 3 5
1
end_operator
begin_operator
move d3 d6 peg3
1
2 0
3
0 5 -1 0
0 8 0 1
0 12 3 6
1
end_operator
begin_operator
move d3 peg1 d3
0
3
0 2 0 1
0 6 -1 0
0 12 4 0
1
end_operator
begin_operator
move d3 peg1 d4
1
2 0
3
0 3 0 1
0 6 -1 0
0 12 4 1
1
end_operator
begin_operator
move d3 peg1 d5
1
2 0
3
0 4 0 1
0 6 -1 0
0 12 4 2
1
end_operator
begin_operator
move d3 peg1 d6
1
2 0
3
0 5 0 1
0 6 -1 0
0 12 4 3
1
end_operator
begin_operator
move d3 peg1 peg2
1
2 0
3
0 6 -1 0
0 7 0 1
0 12 4 5
1
end_operator
begin_operator
move d3 peg1 peg3
1
2 0
3
0 6 -1 0
0 8 0 1
0 12 4 6
1
end_operator
begin_operator
move d3 peg2 d3
0
3
0 2 0 1
0 7 -1 0
0 12 5 0
1
end_operator
begin_operator
move d3 peg2 d4
1
2 0
3
0 3 0 1
0 7 -1 0
0 12 5 1
1
end_operator
begin_operator
move d3 peg2 d5
1
2 0
3
0 4 0 1
0 7 -1 0
0 12 5 2
1
end_operator
begin_operator
move d3 peg2 d6
1
2 0
3
0 5 0 1
0 7 -1 0
0 12 5 3
1
end_operator
begin_operator
move d3 peg2 peg1
1
2 0
3
0 6 0 1
0 7 -1 0
0 12 5 4
1
end_operator
begin_operator
move d3 peg2 peg3
1
2 0
3
0 7 -1 0
0 8 0 1
0 12 5 6
1
end_operator
begin_operator
move d3 peg3 d3
0
3
0 2 0 1
0 8 -1 0
0 12 6 0
1
end_operator
begin_operator
move d3 peg3 d4
1
2 0
3
0 3 0 1
0 8 -1 0
0 12 6 1
1
end_operator
begin_operator
move d3 peg3 d5
1
2 0
3
0 4 0 1
0 8 -1 0
0 12 6 2
1
end_operator
begin_operator
move d3 peg3 d6
1
2 0
3
0 5 0 1
0 8 -1 0
0 12 6 3
1
end_operator
begin_operator
move d3 peg3 peg1
1
2 0
3
0 6 0 1
0 8 -1 0
0 12 6 4
1
end_operator
begin_operator
move d3 peg3 peg2
1
2 0
3
0 7 0 1
0 8 -1 0
0 12 6 5
1
end_operator
begin_operator
move d4 d5 d4
0
3
0 3 0 1
0 4 -1 0
0 11 1 0
1
end_operator
begin_operator
move d4 d5 d6
1
3 0
3
0 4 -1 0
0 5 0 1
0 11 1 2
1
end_operator
begin_operator
move d4 d5 peg1
1
3 0
3
0 4 -1 0
0 6 0 1
0 11 1 3
1
end_operator
begin_operator
move d4 d5 peg2
1
3 0
3
0 4 -1 0
0 7 0 1
0 11 1 4
1
end_operator
begin_operator
move d4 d5 peg3
1
3 0
3
0 4 -1 0
0 8 0 1
0 11 1 5
1
end_operator
begin_operator
move d4 d6 d4
0
3
0 3 0 1
0 5 -1 0
0 11 2 0
1
end_operator
begin_operator
move d4 d6 d5
1
3 0
3
0 4 0 1
0 5 -1 0
0 11 2 1
1
end_operator
begin_operator
move d4 d6 peg1
1
3 0
3
0 5 -1 0
0 6 0 1
0 11 2 3
1
end_operator
begin_operator
move d4 d6 peg2
1
3 0
3
0 5 -1 0
0 7 0 1
0 11 2 4
1
end_operator
begin_operator
move d4 d6 peg3
1
3 0
3
0 5 -1 0
0 8 0 1
0 11 2 5
1
end_operator
begin_operator
move d4 peg1 d4
0
3
0 3 0 1
0 6 -1 0
0 11 3 0
1
end_operator
begin_operator
move d4 peg1 d5
1
3 0
3
0 4 0 1
0 6 -1 0
0 11 3 1
1
end_operator
begin_operator
move d4 peg1 d6
1
3 0
3
0 5 0 1
0 6 -1 0
0 11 3 2
1
end_operator
begin_operator
move d4 peg1 peg2
1
3 0
3
0 6 -1 0
0 7 0 1
0 11 3 4
1
end_operator
begin_operator
move d4 peg1 peg3
1
3 0
3
0 6 -1 0
0 8 0 1
0 11 3 5
1
end_operator
begin_operator
move d4 peg2 d4
0
3
0 3 0 1
0 7 -1 0
0 11 4 0
1
end_operator
begin_operator
move d4 peg2 d5
1
3 0
3
0 4 0 1
0 7 -1 0
0 11 4 1
1
end_operator
begin_operator
move d4 peg2 d6
1
3 0
3
0 5 0 1
0 7 -1 0
0 11 4 2
1
end_operator
begin_operator
move d4 peg2 peg1
1
3 0
3
0 6 0 1
0 7 -1 0
0 11 4 3
1
end_operator
begin_operator
move d4 peg2 peg3
1
3 0
3
0 7 -1 0
0 8 0 1
0 11 4 5
1
end_operator
begin_operator
move d4 peg3 d4
0
3
0 3 0 1
0 8 -1 0
0 11 5 0
1
end_operator
begin_operator
move d4 peg3 d5
1
3 0
3
0 4 0 1
0 8 -1 0
0 11 5 1
1
end_operator
begin_operator
move d4 peg3 d6
1
3 0
3
0 5 0 1
0 8 -1 0
0 11 5 2
1
end_operator
begin_operator
move d4 peg3 peg1
1
3 0
3
0 6 0 1
0 8 -1 0
0 11 5 3
1
end_operator
begin_operator
move d4 peg3 peg2
1
3 0
3
0 7 0 1
0 8 -1 0
0 11 5 4
1
end_operator
begin_operator
move d5 d6 d5
0
3
0 4 0 1
0 5 -1 0
0 10 1 0
1
end_operator
begin_operator
move d5 d6 peg1
1
4 0
3
0 5 -1 0
0 6 0 1
0 10 1 2
1
end_operator
begin_operator
move d5 d6 peg2
1
4 0
3
0 5 -1 0
0 7 0 1
0 10 1 3
1
end_operator
begin_operator
move d5 d6 peg3
1
4 0
3
0 5 -1 0
0 8 0 1
0 10 1 4
1
end_operator
begin_operator
move d5 peg1 d5
0
3
0 4 0 1
0 6 -1 0
0 10 2 0
1
end_operator
begin_operator
move d5 peg1 d6
1
4 0
3
0 5 0 1
0 6 -1 0
0 10 2 1
1
end_operator
begin_operator
move d5 peg1 peg2
1
4 0
3
0 6 -1 0
0 7 0 1
0 10 2 3
1
end_operator
begin_operator
move d5 peg1 peg3
1
4 0
3
0 6 -1 0
0 8 0 1
0 10 2 4
1
end_operator
begin_operator
move d5 peg2 d5
0
3
0 4 0 1
0 7 -1 0
0 10 3 0
1
end_operator
begin_operator
move d5 peg2 d6
1
4 0
3
0 5 0 1
0 7 -1 0
0 10 3 1
1
end_operator
begin_operator
move d5 peg2 peg1
1
4 0
3
0 6 0 1
0 7 -1 0
0 10 3 2
1
end_operator
begin_operator
move d5 peg2 peg3
1
4 0
3
0 7 -1 0
0 8 0 1
0 10 3 4
1
end_operator
begin_operator
move d5 peg3 d5
0
3
0 4 0 1
0 8 -1 0
0 10 4 0
1
end_operator
begin_operator
move d5 peg3 d6
1
4 0
3
0 5 0 1
0 8 -1 0
0 10 4 1
1
end_operator
begin_operator
move d5 peg3 peg1
1
4 0
3
0 6 0 1
0 8 -1 0
0 10 4 2
1
end_operator
begin_operator
move d5 peg3 peg2
1
4 0
3
0 7 0 1
0 8 -1 0
0 10 4 3
1
end_operator
begin_operator
move d6 peg1 peg2
1
5 0
3
0 6 -1 0
0 7 0 1
0 9 0 1
1
end_operator
begin_operator
move d6 peg1 peg3
1
5 0
3
0 6 -1 0
0 8 0 1
0 9 0 2
1
end_operator
begin_operator
move d6 peg2 peg1
1
5 0
3
0 6 0 1
0 7 -1 0
0 9 1 0
1
end_operator
begin_operator
move d6 peg2 peg3
1
5 0
3
0 7 -1 0
0 8 0 1
0 9 1 2
1
end_operator
begin_operator
move d6 peg3 peg1
1
5 0
3
0 6 0 1
0 8 -1 0
0 9 2 0
1
end_operator
begin_operator
move d6 peg3 peg2
1
5 0
3
0 7 0 1
0 8 -1 0
0 9 2 1
1
end_operator
0
