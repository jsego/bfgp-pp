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
6
Atom holding(c)
Atom on(c, a)
Atom on(c, b)
Atom on(c, d)
Atom on(c, e)
Atom ontable(c)
end_variable
begin_variable
var1
-1
2
Atom clear(c)
NegatedAtom clear(c)
end_variable
begin_variable
var2
-1
2
Atom clear(a)
NegatedAtom clear(a)
end_variable
begin_variable
var3
-1
2
Atom clear(b)
NegatedAtom clear(b)
end_variable
begin_variable
var4
-1
2
Atom clear(d)
NegatedAtom clear(d)
end_variable
begin_variable
var5
-1
2
Atom clear(e)
NegatedAtom clear(e)
end_variable
begin_variable
var6
-1
2
Atom handempty()
NegatedAtom handempty()
end_variable
begin_variable
var7
-1
6
Atom holding(a)
Atom on(a, b)
Atom on(a, c)
Atom on(a, d)
Atom on(a, e)
Atom ontable(a)
end_variable
begin_variable
var8
-1
6
Atom holding(b)
Atom on(b, a)
Atom on(b, c)
Atom on(b, d)
Atom on(b, e)
Atom ontable(b)
end_variable
begin_variable
var9
-1
6
Atom holding(d)
Atom on(d, a)
Atom on(d, b)
Atom on(d, c)
Atom on(d, e)
Atom ontable(d)
end_variable
begin_variable
var10
-1
6
Atom holding(e)
Atom on(e, a)
Atom on(e, b)
Atom on(e, c)
Atom on(e, d)
Atom ontable(e)
end_variable
6
begin_mutex_group
6
2 0
7 0
8 1
0 1
9 1
10 1
end_mutex_group
begin_mutex_group
6
3 0
7 1
8 0
0 2
9 2
10 2
end_mutex_group
begin_mutex_group
6
1 0
7 2
8 2
0 0
9 3
10 3
end_mutex_group
begin_mutex_group
6
4 0
7 3
8 3
0 3
9 0
10 4
end_mutex_group
begin_mutex_group
6
5 0
7 4
8 4
0 4
9 4
10 0
end_mutex_group
begin_mutex_group
6
6 0
7 0
8 0
0 0
9 0
10 0
end_mutex_group
begin_state
4
0
1
1
0
1
0
5
1
5
2
end_state
begin_goal
4
7 4
8 3
9 3
10 2
end_goal
50
begin_operator
pick-up a
0
3
0 2 0 1
0 6 0 1
0 7 5 0
1
end_operator
begin_operator
pick-up b
0
3
0 3 0 1
0 6 0 1
0 8 5 0
1
end_operator
begin_operator
pick-up c
0
3
0 1 0 1
0 6 0 1
0 0 5 0
1
end_operator
begin_operator
pick-up d
0
3
0 4 0 1
0 6 0 1
0 9 5 0
1
end_operator
begin_operator
pick-up e
0
3
0 5 0 1
0 6 0 1
0 10 5 0
1
end_operator
begin_operator
put-down a
0
3
0 2 -1 0
0 6 -1 0
0 7 0 5
1
end_operator
begin_operator
put-down b
0
3
0 3 -1 0
0 6 -1 0
0 8 0 5
1
end_operator
begin_operator
put-down c
0
3
0 1 -1 0
0 6 -1 0
0 0 0 5
1
end_operator
begin_operator
put-down d
0
3
0 4 -1 0
0 6 -1 0
0 9 0 5
1
end_operator
begin_operator
put-down e
0
3
0 5 -1 0
0 6 -1 0
0 10 0 5
1
end_operator
begin_operator
stack a b
0
4
0 2 -1 0
0 3 0 1
0 6 -1 0
0 7 0 1
1
end_operator
begin_operator
stack a c
0
4
0 2 -1 0
0 1 0 1
0 6 -1 0
0 7 0 2
1
end_operator
begin_operator
stack a d
0
4
0 2 -1 0
0 4 0 1
0 6 -1 0
0 7 0 3
1
end_operator
begin_operator
stack a e
0
4
0 2 -1 0
0 5 0 1
0 6 -1 0
0 7 0 4
1
end_operator
begin_operator
stack b a
0
4
0 2 0 1
0 3 -1 0
0 6 -1 0
0 8 0 1
1
end_operator
begin_operator
stack b c
0
4
0 3 -1 0
0 1 0 1
0 6 -1 0
0 8 0 2
1
end_operator
begin_operator
stack b d
0
4
0 3 -1 0
0 4 0 1
0 6 -1 0
0 8 0 3
1
end_operator
begin_operator
stack b e
0
4
0 3 -1 0
0 5 0 1
0 6 -1 0
0 8 0 4
1
end_operator
begin_operator
stack c a
0
4
0 2 0 1
0 1 -1 0
0 6 -1 0
0 0 0 1
1
end_operator
begin_operator
stack c b
0
4
0 3 0 1
0 1 -1 0
0 6 -1 0
0 0 0 2
1
end_operator
begin_operator
stack c d
0
4
0 1 -1 0
0 4 0 1
0 6 -1 0
0 0 0 3
1
end_operator
begin_operator
stack c e
0
4
0 1 -1 0
0 5 0 1
0 6 -1 0
0 0 0 4
1
end_operator
begin_operator
stack d a
0
4
0 2 0 1
0 4 -1 0
0 6 -1 0
0 9 0 1
1
end_operator
begin_operator
stack d b
0
4
0 3 0 1
0 4 -1 0
0 6 -1 0
0 9 0 2
1
end_operator
begin_operator
stack d c
0
4
0 1 0 1
0 4 -1 0
0 6 -1 0
0 9 0 3
1
end_operator
begin_operator
stack d e
0
4
0 4 -1 0
0 5 0 1
0 6 -1 0
0 9 0 4
1
end_operator
begin_operator
stack e a
0
4
0 2 0 1
0 5 -1 0
0 6 -1 0
0 10 0 1
1
end_operator
begin_operator
stack e b
0
4
0 3 0 1
0 5 -1 0
0 6 -1 0
0 10 0 2
1
end_operator
begin_operator
stack e c
0
4
0 1 0 1
0 5 -1 0
0 6 -1 0
0 10 0 3
1
end_operator
begin_operator
stack e d
0
4
0 4 0 1
0 5 -1 0
0 6 -1 0
0 10 0 4
1
end_operator
begin_operator
unstack a b
0
4
0 2 0 1
0 3 -1 0
0 6 0 1
0 7 1 0
1
end_operator
begin_operator
unstack a c
0
4
0 2 0 1
0 1 -1 0
0 6 0 1
0 7 2 0
1
end_operator
begin_operator
unstack a d
0
4
0 2 0 1
0 4 -1 0
0 6 0 1
0 7 3 0
1
end_operator
begin_operator
unstack a e
0
4
0 2 0 1
0 5 -1 0
0 6 0 1
0 7 4 0
1
end_operator
begin_operator
unstack b a
0
4
0 2 -1 0
0 3 0 1
0 6 0 1
0 8 1 0
1
end_operator
begin_operator
unstack b c
0
4
0 3 0 1
0 1 -1 0
0 6 0 1
0 8 2 0
1
end_operator
begin_operator
unstack b d
0
4
0 3 0 1
0 4 -1 0
0 6 0 1
0 8 3 0
1
end_operator
begin_operator
unstack b e
0
4
0 3 0 1
0 5 -1 0
0 6 0 1
0 8 4 0
1
end_operator
begin_operator
unstack c a
0
4
0 2 -1 0
0 1 0 1
0 6 0 1
0 0 1 0
1
end_operator
begin_operator
unstack c b
0
4
0 3 -1 0
0 1 0 1
0 6 0 1
0 0 2 0
1
end_operator
begin_operator
unstack c d
0
4
0 1 0 1
0 4 -1 0
0 6 0 1
0 0 3 0
1
end_operator
begin_operator
unstack c e
0
4
0 1 0 1
0 5 -1 0
0 6 0 1
0 0 4 0
1
end_operator
begin_operator
unstack d a
0
4
0 2 -1 0
0 4 0 1
0 6 0 1
0 9 1 0
1
end_operator
begin_operator
unstack d b
0
4
0 3 -1 0
0 4 0 1
0 6 0 1
0 9 2 0
1
end_operator
begin_operator
unstack d c
0
4
0 1 -1 0
0 4 0 1
0 6 0 1
0 9 3 0
1
end_operator
begin_operator
unstack d e
0
4
0 4 0 1
0 5 -1 0
0 6 0 1
0 9 4 0
1
end_operator
begin_operator
unstack e a
0
4
0 2 -1 0
0 5 0 1
0 6 0 1
0 10 1 0
1
end_operator
begin_operator
unstack e b
0
4
0 3 -1 0
0 5 0 1
0 6 0 1
0 10 2 0
1
end_operator
begin_operator
unstack e c
0
4
0 1 -1 0
0 5 0 1
0 6 0 1
0 10 3 0
1
end_operator
begin_operator
unstack e d
0
4
0 4 -1 0
0 5 0 1
0 6 0 1
0 10 4 0
1
end_operator
0
