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
8
Atom holding(e)
Atom on(e, a)
Atom on(e, b)
Atom on(e, c)
Atom on(e, d)
Atom on(e, f)
Atom on(e, g)
Atom ontable(e)
end_variable
begin_variable
var1
-1
2
Atom clear(e)
NegatedAtom clear(e)
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
Atom clear(c)
NegatedAtom clear(c)
end_variable
begin_variable
var5
-1
2
Atom clear(d)
NegatedAtom clear(d)
end_variable
begin_variable
var6
-1
2
Atom clear(f)
NegatedAtom clear(f)
end_variable
begin_variable
var7
-1
2
Atom clear(g)
NegatedAtom clear(g)
end_variable
begin_variable
var8
-1
2
Atom handempty()
NegatedAtom handempty()
end_variable
begin_variable
var9
-1
8
Atom holding(a)
Atom on(a, b)
Atom on(a, c)
Atom on(a, d)
Atom on(a, e)
Atom on(a, f)
Atom on(a, g)
Atom ontable(a)
end_variable
begin_variable
var10
-1
8
Atom holding(b)
Atom on(b, a)
Atom on(b, c)
Atom on(b, d)
Atom on(b, e)
Atom on(b, f)
Atom on(b, g)
Atom ontable(b)
end_variable
begin_variable
var11
-1
8
Atom holding(c)
Atom on(c, a)
Atom on(c, b)
Atom on(c, d)
Atom on(c, e)
Atom on(c, f)
Atom on(c, g)
Atom ontable(c)
end_variable
begin_variable
var12
-1
8
Atom holding(d)
Atom on(d, a)
Atom on(d, b)
Atom on(d, c)
Atom on(d, e)
Atom on(d, f)
Atom on(d, g)
Atom ontable(d)
end_variable
begin_variable
var13
-1
8
Atom holding(f)
Atom on(f, a)
Atom on(f, b)
Atom on(f, c)
Atom on(f, d)
Atom on(f, e)
Atom on(f, g)
Atom ontable(f)
end_variable
begin_variable
var14
-1
8
Atom holding(g)
Atom on(g, a)
Atom on(g, b)
Atom on(g, c)
Atom on(g, d)
Atom on(g, e)
Atom on(g, f)
Atom ontable(g)
end_variable
8
begin_mutex_group
8
2 0
9 0
10 1
11 1
12 1
0 1
13 1
14 1
end_mutex_group
begin_mutex_group
8
3 0
9 1
10 0
11 2
12 2
0 2
13 2
14 2
end_mutex_group
begin_mutex_group
8
4 0
9 2
10 2
11 0
12 3
0 3
13 3
14 3
end_mutex_group
begin_mutex_group
8
5 0
9 3
10 3
11 3
12 0
0 4
13 4
14 4
end_mutex_group
begin_mutex_group
8
1 0
9 4
10 4
11 4
12 4
0 0
13 5
14 5
end_mutex_group
begin_mutex_group
8
6 0
9 5
10 5
11 5
12 5
0 5
13 0
14 6
end_mutex_group
begin_mutex_group
8
7 0
9 6
10 6
11 6
12 6
0 6
13 6
14 0
end_mutex_group
begin_mutex_group
8
8 0
9 0
10 0
11 0
12 0
0 0
13 0
14 0
end_mutex_group
begin_state
6
0
1
1
1
1
1
1
0
5
1
3
7
3
2
end_state
begin_goal
6
9 6
10 2
11 5
12 2
13 5
14 4
end_goal
98
begin_operator
pick-up a
0
3
0 2 0 1
0 8 0 1
0 9 7 0
1
end_operator
begin_operator
pick-up b
0
3
0 3 0 1
0 8 0 1
0 10 7 0
1
end_operator
begin_operator
pick-up c
0
3
0 4 0 1
0 8 0 1
0 11 7 0
1
end_operator
begin_operator
pick-up d
0
3
0 5 0 1
0 8 0 1
0 12 7 0
1
end_operator
begin_operator
pick-up e
0
3
0 1 0 1
0 8 0 1
0 0 7 0
1
end_operator
begin_operator
pick-up f
0
3
0 6 0 1
0 8 0 1
0 13 7 0
1
end_operator
begin_operator
pick-up g
0
3
0 7 0 1
0 8 0 1
0 14 7 0
1
end_operator
begin_operator
put-down a
0
3
0 2 -1 0
0 8 -1 0
0 9 0 7
1
end_operator
begin_operator
put-down b
0
3
0 3 -1 0
0 8 -1 0
0 10 0 7
1
end_operator
begin_operator
put-down c
0
3
0 4 -1 0
0 8 -1 0
0 11 0 7
1
end_operator
begin_operator
put-down d
0
3
0 5 -1 0
0 8 -1 0
0 12 0 7
1
end_operator
begin_operator
put-down e
0
3
0 1 -1 0
0 8 -1 0
0 0 0 7
1
end_operator
begin_operator
put-down f
0
3
0 6 -1 0
0 8 -1 0
0 13 0 7
1
end_operator
begin_operator
put-down g
0
3
0 7 -1 0
0 8 -1 0
0 14 0 7
1
end_operator
begin_operator
stack a b
0
4
0 2 -1 0
0 3 0 1
0 8 -1 0
0 9 0 1
1
end_operator
begin_operator
stack a c
0
4
0 2 -1 0
0 4 0 1
0 8 -1 0
0 9 0 2
1
end_operator
begin_operator
stack a d
0
4
0 2 -1 0
0 5 0 1
0 8 -1 0
0 9 0 3
1
end_operator
begin_operator
stack a e
0
4
0 2 -1 0
0 1 0 1
0 8 -1 0
0 9 0 4
1
end_operator
begin_operator
stack a f
0
4
0 2 -1 0
0 6 0 1
0 8 -1 0
0 9 0 5
1
end_operator
begin_operator
stack a g
0
4
0 2 -1 0
0 7 0 1
0 8 -1 0
0 9 0 6
1
end_operator
begin_operator
stack b a
0
4
0 2 0 1
0 3 -1 0
0 8 -1 0
0 10 0 1
1
end_operator
begin_operator
stack b c
0
4
0 3 -1 0
0 4 0 1
0 8 -1 0
0 10 0 2
1
end_operator
begin_operator
stack b d
0
4
0 3 -1 0
0 5 0 1
0 8 -1 0
0 10 0 3
1
end_operator
begin_operator
stack b e
0
4
0 3 -1 0
0 1 0 1
0 8 -1 0
0 10 0 4
1
end_operator
begin_operator
stack b f
0
4
0 3 -1 0
0 6 0 1
0 8 -1 0
0 10 0 5
1
end_operator
begin_operator
stack b g
0
4
0 3 -1 0
0 7 0 1
0 8 -1 0
0 10 0 6
1
end_operator
begin_operator
stack c a
0
4
0 2 0 1
0 4 -1 0
0 8 -1 0
0 11 0 1
1
end_operator
begin_operator
stack c b
0
4
0 3 0 1
0 4 -1 0
0 8 -1 0
0 11 0 2
1
end_operator
begin_operator
stack c d
0
4
0 4 -1 0
0 5 0 1
0 8 -1 0
0 11 0 3
1
end_operator
begin_operator
stack c e
0
4
0 4 -1 0
0 1 0 1
0 8 -1 0
0 11 0 4
1
end_operator
begin_operator
stack c f
0
4
0 4 -1 0
0 6 0 1
0 8 -1 0
0 11 0 5
1
end_operator
begin_operator
stack c g
0
4
0 4 -1 0
0 7 0 1
0 8 -1 0
0 11 0 6
1
end_operator
begin_operator
stack d a
0
4
0 2 0 1
0 5 -1 0
0 8 -1 0
0 12 0 1
1
end_operator
begin_operator
stack d b
0
4
0 3 0 1
0 5 -1 0
0 8 -1 0
0 12 0 2
1
end_operator
begin_operator
stack d c
0
4
0 4 0 1
0 5 -1 0
0 8 -1 0
0 12 0 3
1
end_operator
begin_operator
stack d e
0
4
0 5 -1 0
0 1 0 1
0 8 -1 0
0 12 0 4
1
end_operator
begin_operator
stack d f
0
4
0 5 -1 0
0 6 0 1
0 8 -1 0
0 12 0 5
1
end_operator
begin_operator
stack d g
0
4
0 5 -1 0
0 7 0 1
0 8 -1 0
0 12 0 6
1
end_operator
begin_operator
stack e a
0
4
0 2 0 1
0 1 -1 0
0 8 -1 0
0 0 0 1
1
end_operator
begin_operator
stack e b
0
4
0 3 0 1
0 1 -1 0
0 8 -1 0
0 0 0 2
1
end_operator
begin_operator
stack e c
0
4
0 4 0 1
0 1 -1 0
0 8 -1 0
0 0 0 3
1
end_operator
begin_operator
stack e d
0
4
0 5 0 1
0 1 -1 0
0 8 -1 0
0 0 0 4
1
end_operator
begin_operator
stack e f
0
4
0 1 -1 0
0 6 0 1
0 8 -1 0
0 0 0 5
1
end_operator
begin_operator
stack e g
0
4
0 1 -1 0
0 7 0 1
0 8 -1 0
0 0 0 6
1
end_operator
begin_operator
stack f a
0
4
0 2 0 1
0 6 -1 0
0 8 -1 0
0 13 0 1
1
end_operator
begin_operator
stack f b
0
4
0 3 0 1
0 6 -1 0
0 8 -1 0
0 13 0 2
1
end_operator
begin_operator
stack f c
0
4
0 4 0 1
0 6 -1 0
0 8 -1 0
0 13 0 3
1
end_operator
begin_operator
stack f d
0
4
0 5 0 1
0 6 -1 0
0 8 -1 0
0 13 0 4
1
end_operator
begin_operator
stack f e
0
4
0 1 0 1
0 6 -1 0
0 8 -1 0
0 13 0 5
1
end_operator
begin_operator
stack f g
0
4
0 6 -1 0
0 7 0 1
0 8 -1 0
0 13 0 6
1
end_operator
begin_operator
stack g a
0
4
0 2 0 1
0 7 -1 0
0 8 -1 0
0 14 0 1
1
end_operator
begin_operator
stack g b
0
4
0 3 0 1
0 7 -1 0
0 8 -1 0
0 14 0 2
1
end_operator
begin_operator
stack g c
0
4
0 4 0 1
0 7 -1 0
0 8 -1 0
0 14 0 3
1
end_operator
begin_operator
stack g d
0
4
0 5 0 1
0 7 -1 0
0 8 -1 0
0 14 0 4
1
end_operator
begin_operator
stack g e
0
4
0 1 0 1
0 7 -1 0
0 8 -1 0
0 14 0 5
1
end_operator
begin_operator
stack g f
0
4
0 6 0 1
0 7 -1 0
0 8 -1 0
0 14 0 6
1
end_operator
begin_operator
unstack a b
0
4
0 2 0 1
0 3 -1 0
0 8 0 1
0 9 1 0
1
end_operator
begin_operator
unstack a c
0
4
0 2 0 1
0 4 -1 0
0 8 0 1
0 9 2 0
1
end_operator
begin_operator
unstack a d
0
4
0 2 0 1
0 5 -1 0
0 8 0 1
0 9 3 0
1
end_operator
begin_operator
unstack a e
0
4
0 2 0 1
0 1 -1 0
0 8 0 1
0 9 4 0
1
end_operator
begin_operator
unstack a f
0
4
0 2 0 1
0 6 -1 0
0 8 0 1
0 9 5 0
1
end_operator
begin_operator
unstack a g
0
4
0 2 0 1
0 7 -1 0
0 8 0 1
0 9 6 0
1
end_operator
begin_operator
unstack b a
0
4
0 2 -1 0
0 3 0 1
0 8 0 1
0 10 1 0
1
end_operator
begin_operator
unstack b c
0
4
0 3 0 1
0 4 -1 0
0 8 0 1
0 10 2 0
1
end_operator
begin_operator
unstack b d
0
4
0 3 0 1
0 5 -1 0
0 8 0 1
0 10 3 0
1
end_operator
begin_operator
unstack b e
0
4
0 3 0 1
0 1 -1 0
0 8 0 1
0 10 4 0
1
end_operator
begin_operator
unstack b f
0
4
0 3 0 1
0 6 -1 0
0 8 0 1
0 10 5 0
1
end_operator
begin_operator
unstack b g
0
4
0 3 0 1
0 7 -1 0
0 8 0 1
0 10 6 0
1
end_operator
begin_operator
unstack c a
0
4
0 2 -1 0
0 4 0 1
0 8 0 1
0 11 1 0
1
end_operator
begin_operator
unstack c b
0
4
0 3 -1 0
0 4 0 1
0 8 0 1
0 11 2 0
1
end_operator
begin_operator
unstack c d
0
4
0 4 0 1
0 5 -1 0
0 8 0 1
0 11 3 0
1
end_operator
begin_operator
unstack c e
0
4
0 4 0 1
0 1 -1 0
0 8 0 1
0 11 4 0
1
end_operator
begin_operator
unstack c f
0
4
0 4 0 1
0 6 -1 0
0 8 0 1
0 11 5 0
1
end_operator
begin_operator
unstack c g
0
4
0 4 0 1
0 7 -1 0
0 8 0 1
0 11 6 0
1
end_operator
begin_operator
unstack d a
0
4
0 2 -1 0
0 5 0 1
0 8 0 1
0 12 1 0
1
end_operator
begin_operator
unstack d b
0
4
0 3 -1 0
0 5 0 1
0 8 0 1
0 12 2 0
1
end_operator
begin_operator
unstack d c
0
4
0 4 -1 0
0 5 0 1
0 8 0 1
0 12 3 0
1
end_operator
begin_operator
unstack d e
0
4
0 5 0 1
0 1 -1 0
0 8 0 1
0 12 4 0
1
end_operator
begin_operator
unstack d f
0
4
0 5 0 1
0 6 -1 0
0 8 0 1
0 12 5 0
1
end_operator
begin_operator
unstack d g
0
4
0 5 0 1
0 7 -1 0
0 8 0 1
0 12 6 0
1
end_operator
begin_operator
unstack e a
0
4
0 2 -1 0
0 1 0 1
0 8 0 1
0 0 1 0
1
end_operator
begin_operator
unstack e b
0
4
0 3 -1 0
0 1 0 1
0 8 0 1
0 0 2 0
1
end_operator
begin_operator
unstack e c
0
4
0 4 -1 0
0 1 0 1
0 8 0 1
0 0 3 0
1
end_operator
begin_operator
unstack e d
0
4
0 5 -1 0
0 1 0 1
0 8 0 1
0 0 4 0
1
end_operator
begin_operator
unstack e f
0
4
0 1 0 1
0 6 -1 0
0 8 0 1
0 0 5 0
1
end_operator
begin_operator
unstack e g
0
4
0 1 0 1
0 7 -1 0
0 8 0 1
0 0 6 0
1
end_operator
begin_operator
unstack f a
0
4
0 2 -1 0
0 6 0 1
0 8 0 1
0 13 1 0
1
end_operator
begin_operator
unstack f b
0
4
0 3 -1 0
0 6 0 1
0 8 0 1
0 13 2 0
1
end_operator
begin_operator
unstack f c
0
4
0 4 -1 0
0 6 0 1
0 8 0 1
0 13 3 0
1
end_operator
begin_operator
unstack f d
0
4
0 5 -1 0
0 6 0 1
0 8 0 1
0 13 4 0
1
end_operator
begin_operator
unstack f e
0
4
0 1 -1 0
0 6 0 1
0 8 0 1
0 13 5 0
1
end_operator
begin_operator
unstack f g
0
4
0 6 0 1
0 7 -1 0
0 8 0 1
0 13 6 0
1
end_operator
begin_operator
unstack g a
0
4
0 2 -1 0
0 7 0 1
0 8 0 1
0 14 1 0
1
end_operator
begin_operator
unstack g b
0
4
0 3 -1 0
0 7 0 1
0 8 0 1
0 14 2 0
1
end_operator
begin_operator
unstack g c
0
4
0 4 -1 0
0 7 0 1
0 8 0 1
0 14 3 0
1
end_operator
begin_operator
unstack g d
0
4
0 5 -1 0
0 7 0 1
0 8 0 1
0 14 4 0
1
end_operator
begin_operator
unstack g e
0
4
0 1 -1 0
0 7 0 1
0 8 0 1
0 14 5 0
1
end_operator
begin_operator
unstack g f
0
4
0 6 -1 0
0 7 0 1
0 8 0 1
0 14 6 0
1
end_operator
0
