begin_version
3
end_version
begin_metric
0
end_metric
4
begin_variable
var0
-1
2
Atom is-at(l0)
Atom is-at(l1)
end_variable
begin_variable
var1
-1
2
Atom at(o0, l0)
NegatedAtom at(o0, l0)
end_variable
begin_variable
var2
-1
2
Atom in(o0)
NegatedAtom in(o0)
end_variable
begin_variable
var3
-1
2
Atom at(o0, l1)
NegatedAtom at(o0, l1)
end_variable
0
begin_state
1
1
1
0
end_state
begin_goal
2
0 0
3 0
end_goal
5
begin_operator
move l0 l1
0
3
1 2 0 1 -1 1
1 2 0 3 -1 0
0 0 0 1
1
end_operator
begin_operator
move l1 l0
0
3
1 2 0 1 -1 0
1 2 0 3 -1 1
0 0 1 0
1
end_operator
begin_operator
put-in o0 l0
2
1 0
0 0
1
0 2 1 0
1
end_operator
begin_operator
put-in o0 l1
2
3 0
0 1
1
0 2 1 0
1
end_operator
begin_operator
take-out o0
0
1
0 2 0 1
1
end_operator
0
