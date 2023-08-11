begin_version
3
end_version
begin_metric
0
end_metric
9
begin_variable
var0
-1
3
Atom is-at(l0)
Atom is-at(l1)
Atom is-at(l2)
end_variable
begin_variable
var1
-1
2
Atom in(o1)
NegatedAtom in(o1)
end_variable
begin_variable
var2
-1
2
Atom at(o1, l0)
NegatedAtom at(o1, l0)
end_variable
begin_variable
var3
-1
2
Atom at(o1, l1)
NegatedAtom at(o1, l1)
end_variable
begin_variable
var4
-1
2
Atom at(o1, l2)
NegatedAtom at(o1, l2)
end_variable
begin_variable
var5
-1
2
Atom in(o0)
NegatedAtom in(o0)
end_variable
begin_variable
var6
-1
2
Atom at(o0, l1)
NegatedAtom at(o0, l1)
end_variable
begin_variable
var7
-1
2
Atom at(o0, l2)
NegatedAtom at(o0, l2)
end_variable
begin_variable
var8
-1
2
Atom at(o0, l0)
NegatedAtom at(o0, l0)
end_variable
0
begin_state
2
1
1
1
0
1
1
0
1
end_state
begin_goal
3
0 0
4 0
8 0
end_goal
14
begin_operator
move l0 l1
0
5
1 5 0 8 -1 1
1 5 0 6 -1 0
1 1 0 2 -1 1
1 1 0 3 -1 0
0 0 0 1
1
end_operator
begin_operator
move l0 l2
0
5
1 5 0 8 -1 1
1 5 0 7 -1 0
1 1 0 2 -1 1
1 1 0 4 -1 0
0 0 0 2
1
end_operator
begin_operator
move l1 l0
0
5
1 5 0 8 -1 0
1 5 0 6 -1 1
1 1 0 2 -1 0
1 1 0 3 -1 1
0 0 1 0
1
end_operator
begin_operator
move l1 l2
0
5
1 5 0 6 -1 1
1 5 0 7 -1 0
1 1 0 3 -1 1
1 1 0 4 -1 0
0 0 1 2
1
end_operator
begin_operator
move l2 l0
0
5
1 5 0 8 -1 0
1 5 0 7 -1 1
1 1 0 2 -1 0
1 1 0 4 -1 1
0 0 2 0
1
end_operator
begin_operator
move l2 l1
0
5
1 5 0 6 -1 0
1 5 0 7 -1 1
1 1 0 3 -1 0
1 1 0 4 -1 1
0 0 2 1
1
end_operator
begin_operator
put-in o0 l0
2
8 0
0 0
1
0 5 1 0
1
end_operator
begin_operator
put-in o0 l1
2
6 0
0 1
1
0 5 1 0
1
end_operator
begin_operator
put-in o0 l2
2
7 0
0 2
1
0 5 1 0
1
end_operator
begin_operator
put-in o1 l0
2
2 0
0 0
1
0 1 1 0
1
end_operator
begin_operator
put-in o1 l1
2
3 0
0 1
1
0 1 1 0
1
end_operator
begin_operator
put-in o1 l2
2
4 0
0 2
1
0 1 1 0
1
end_operator
begin_operator
take-out o0
0
1
0 5 0 1
1
end_operator
begin_operator
take-out o1
0
1
0 1 0 1
1
end_operator
0
