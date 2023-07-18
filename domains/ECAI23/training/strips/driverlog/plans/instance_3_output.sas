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
8
Atom at(driver1, p0-1)
Atom at(driver1, p2-0)
Atom at(driver1, p2-1)
Atom at(driver1, s0)
Atom at(driver1, s1)
Atom at(driver1, s2)
Atom driving(driver1, truck1)
Atom driving(driver1, truck2)
end_variable
begin_variable
var1
-1
2
Atom empty(truck1)
NegatedAtom empty(truck1)
end_variable
begin_variable
var2
-1
2
Atom empty(truck2)
NegatedAtom empty(truck2)
end_variable
begin_variable
var3
-1
3
Atom at(truck1, s0)
Atom at(truck1, s1)
Atom at(truck1, s2)
end_variable
begin_variable
var4
-1
3
Atom at(truck2, s0)
Atom at(truck2, s1)
Atom at(truck2, s2)
end_variable
begin_variable
var5
-1
8
Atom at(driver2, p0-1)
Atom at(driver2, p2-0)
Atom at(driver2, p2-1)
Atom at(driver2, s0)
Atom at(driver2, s1)
Atom at(driver2, s2)
Atom driving(driver2, truck1)
Atom driving(driver2, truck2)
end_variable
begin_variable
var6
-1
5
Atom at(package3, s0)
Atom at(package3, s1)
Atom at(package3, s2)
Atom in(package3, truck1)
Atom in(package3, truck2)
end_variable
begin_variable
var7
-1
5
Atom at(package2, s0)
Atom at(package2, s1)
Atom at(package2, s2)
Atom in(package2, truck1)
Atom in(package2, truck2)
end_variable
begin_variable
var8
-1
5
Atom at(package1, s0)
Atom at(package1, s1)
Atom at(package1, s2)
Atom in(package1, truck1)
Atom in(package1, truck2)
end_variable
2
begin_mutex_group
3
0 6
5 6
1 0
end_mutex_group
begin_mutex_group
3
0 7
5 7
2 0
end_mutex_group
begin_state
4
0
0
1
2
3
1
0
0
end_state
begin_goal
6
3 1
4 2
5 5
6 2
7 1
8 1
end_goal
108
begin_operator
board-truck driver1 truck1 s0
1
3 0
2
0 0 3 6
0 1 0 1
1
end_operator
begin_operator
board-truck driver1 truck1 s1
1
3 1
2
0 0 4 6
0 1 0 1
1
end_operator
begin_operator
board-truck driver1 truck1 s2
1
3 2
2
0 0 5 6
0 1 0 1
1
end_operator
begin_operator
board-truck driver1 truck2 s0
1
4 0
2
0 0 3 7
0 2 0 1
1
end_operator
begin_operator
board-truck driver1 truck2 s1
1
4 1
2
0 0 4 7
0 2 0 1
1
end_operator
begin_operator
board-truck driver1 truck2 s2
1
4 2
2
0 0 5 7
0 2 0 1
1
end_operator
begin_operator
board-truck driver2 truck1 s0
1
3 0
2
0 5 3 6
0 1 0 1
1
end_operator
begin_operator
board-truck driver2 truck1 s1
1
3 1
2
0 5 4 6
0 1 0 1
1
end_operator
begin_operator
board-truck driver2 truck1 s2
1
3 2
2
0 5 5 6
0 1 0 1
1
end_operator
begin_operator
board-truck driver2 truck2 s0
1
4 0
2
0 5 3 7
0 2 0 1
1
end_operator
begin_operator
board-truck driver2 truck2 s1
1
4 1
2
0 5 4 7
0 2 0 1
1
end_operator
begin_operator
board-truck driver2 truck2 s2
1
4 2
2
0 5 5 7
0 2 0 1
1
end_operator
begin_operator
disembark-truck driver1 truck1 s0
1
3 0
2
0 0 6 3
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck1 s1
1
3 1
2
0 0 6 4
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck1 s2
1
3 2
2
0 0 6 5
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck2 s0
1
4 0
2
0 0 7 3
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck2 s1
1
4 1
2
0 0 7 4
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck2 s2
1
4 2
2
0 0 7 5
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck1 s0
1
3 0
2
0 5 6 3
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck1 s1
1
3 1
2
0 5 6 4
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck1 s2
1
3 2
2
0 5 6 5
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck2 s0
1
4 0
2
0 5 7 3
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck2 s1
1
4 1
2
0 5 7 4
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck2 s2
1
4 2
2
0 5 7 5
0 2 -1 0
1
end_operator
begin_operator
drive-truck truck1 s0 s1 driver1
1
0 6
1
0 3 0 1
1
end_operator
begin_operator
drive-truck truck1 s0 s1 driver2
1
5 6
1
0 3 0 1
1
end_operator
begin_operator
drive-truck truck1 s0 s2 driver1
1
0 6
1
0 3 0 2
1
end_operator
begin_operator
drive-truck truck1 s0 s2 driver2
1
5 6
1
0 3 0 2
1
end_operator
begin_operator
drive-truck truck1 s1 s0 driver1
1
0 6
1
0 3 1 0
1
end_operator
begin_operator
drive-truck truck1 s1 s0 driver2
1
5 6
1
0 3 1 0
1
end_operator
begin_operator
drive-truck truck1 s1 s2 driver1
1
0 6
1
0 3 1 2
1
end_operator
begin_operator
drive-truck truck1 s1 s2 driver2
1
5 6
1
0 3 1 2
1
end_operator
begin_operator
drive-truck truck1 s2 s0 driver1
1
0 6
1
0 3 2 0
1
end_operator
begin_operator
drive-truck truck1 s2 s0 driver2
1
5 6
1
0 3 2 0
1
end_operator
begin_operator
drive-truck truck1 s2 s1 driver1
1
0 6
1
0 3 2 1
1
end_operator
begin_operator
drive-truck truck1 s2 s1 driver2
1
5 6
1
0 3 2 1
1
end_operator
begin_operator
drive-truck truck2 s0 s1 driver1
1
0 7
1
0 4 0 1
1
end_operator
begin_operator
drive-truck truck2 s0 s1 driver2
1
5 7
1
0 4 0 1
1
end_operator
begin_operator
drive-truck truck2 s0 s2 driver1
1
0 7
1
0 4 0 2
1
end_operator
begin_operator
drive-truck truck2 s0 s2 driver2
1
5 7
1
0 4 0 2
1
end_operator
begin_operator
drive-truck truck2 s1 s0 driver1
1
0 7
1
0 4 1 0
1
end_operator
begin_operator
drive-truck truck2 s1 s0 driver2
1
5 7
1
0 4 1 0
1
end_operator
begin_operator
drive-truck truck2 s1 s2 driver1
1
0 7
1
0 4 1 2
1
end_operator
begin_operator
drive-truck truck2 s1 s2 driver2
1
5 7
1
0 4 1 2
1
end_operator
begin_operator
drive-truck truck2 s2 s0 driver1
1
0 7
1
0 4 2 0
1
end_operator
begin_operator
drive-truck truck2 s2 s0 driver2
1
5 7
1
0 4 2 0
1
end_operator
begin_operator
drive-truck truck2 s2 s1 driver1
1
0 7
1
0 4 2 1
1
end_operator
begin_operator
drive-truck truck2 s2 s1 driver2
1
5 7
1
0 4 2 1
1
end_operator
begin_operator
load-truck package1 truck1 s0
1
3 0
1
0 8 0 3
1
end_operator
begin_operator
load-truck package1 truck1 s1
1
3 1
1
0 8 1 3
1
end_operator
begin_operator
load-truck package1 truck1 s2
1
3 2
1
0 8 2 3
1
end_operator
begin_operator
load-truck package1 truck2 s0
1
4 0
1
0 8 0 4
1
end_operator
begin_operator
load-truck package1 truck2 s1
1
4 1
1
0 8 1 4
1
end_operator
begin_operator
load-truck package1 truck2 s2
1
4 2
1
0 8 2 4
1
end_operator
begin_operator
load-truck package2 truck1 s0
1
3 0
1
0 7 0 3
1
end_operator
begin_operator
load-truck package2 truck1 s1
1
3 1
1
0 7 1 3
1
end_operator
begin_operator
load-truck package2 truck1 s2
1
3 2
1
0 7 2 3
1
end_operator
begin_operator
load-truck package2 truck2 s0
1
4 0
1
0 7 0 4
1
end_operator
begin_operator
load-truck package2 truck2 s1
1
4 1
1
0 7 1 4
1
end_operator
begin_operator
load-truck package2 truck2 s2
1
4 2
1
0 7 2 4
1
end_operator
begin_operator
load-truck package3 truck1 s0
1
3 0
1
0 6 0 3
1
end_operator
begin_operator
load-truck package3 truck1 s1
1
3 1
1
0 6 1 3
1
end_operator
begin_operator
load-truck package3 truck1 s2
1
3 2
1
0 6 2 3
1
end_operator
begin_operator
load-truck package3 truck2 s0
1
4 0
1
0 6 0 4
1
end_operator
begin_operator
load-truck package3 truck2 s1
1
4 1
1
0 6 1 4
1
end_operator
begin_operator
load-truck package3 truck2 s2
1
4 2
1
0 6 2 4
1
end_operator
begin_operator
unload-truck package1 truck1 s0
1
3 0
1
0 8 3 0
1
end_operator
begin_operator
unload-truck package1 truck1 s1
1
3 1
1
0 8 3 1
1
end_operator
begin_operator
unload-truck package1 truck1 s2
1
3 2
1
0 8 3 2
1
end_operator
begin_operator
unload-truck package1 truck2 s0
1
4 0
1
0 8 4 0
1
end_operator
begin_operator
unload-truck package1 truck2 s1
1
4 1
1
0 8 4 1
1
end_operator
begin_operator
unload-truck package1 truck2 s2
1
4 2
1
0 8 4 2
1
end_operator
begin_operator
unload-truck package2 truck1 s0
1
3 0
1
0 7 3 0
1
end_operator
begin_operator
unload-truck package2 truck1 s1
1
3 1
1
0 7 3 1
1
end_operator
begin_operator
unload-truck package2 truck1 s2
1
3 2
1
0 7 3 2
1
end_operator
begin_operator
unload-truck package2 truck2 s0
1
4 0
1
0 7 4 0
1
end_operator
begin_operator
unload-truck package2 truck2 s1
1
4 1
1
0 7 4 1
1
end_operator
begin_operator
unload-truck package2 truck2 s2
1
4 2
1
0 7 4 2
1
end_operator
begin_operator
unload-truck package3 truck1 s0
1
3 0
1
0 6 3 0
1
end_operator
begin_operator
unload-truck package3 truck1 s1
1
3 1
1
0 6 3 1
1
end_operator
begin_operator
unload-truck package3 truck1 s2
1
3 2
1
0 6 3 2
1
end_operator
begin_operator
unload-truck package3 truck2 s0
1
4 0
1
0 6 4 0
1
end_operator
begin_operator
unload-truck package3 truck2 s1
1
4 1
1
0 6 4 1
1
end_operator
begin_operator
unload-truck package3 truck2 s2
1
4 2
1
0 6 4 2
1
end_operator
begin_operator
walk driver1 p0-1 s0
0
1
0 0 0 3
1
end_operator
begin_operator
walk driver1 p0-1 s1
0
1
0 0 0 4
1
end_operator
begin_operator
walk driver1 p2-0 s0
0
1
0 0 1 3
1
end_operator
begin_operator
walk driver1 p2-0 s2
0
1
0 0 1 5
1
end_operator
begin_operator
walk driver1 p2-1 s1
0
1
0 0 2 4
1
end_operator
begin_operator
walk driver1 p2-1 s2
0
1
0 0 2 5
1
end_operator
begin_operator
walk driver1 s0 p0-1
0
1
0 0 3 0
1
end_operator
begin_operator
walk driver1 s0 p2-0
0
1
0 0 3 1
1
end_operator
begin_operator
walk driver1 s1 p0-1
0
1
0 0 4 0
1
end_operator
begin_operator
walk driver1 s1 p2-1
0
1
0 0 4 2
1
end_operator
begin_operator
walk driver1 s2 p2-0
0
1
0 0 5 1
1
end_operator
begin_operator
walk driver1 s2 p2-1
0
1
0 0 5 2
1
end_operator
begin_operator
walk driver2 p0-1 s0
0
1
0 5 0 3
1
end_operator
begin_operator
walk driver2 p0-1 s1
0
1
0 5 0 4
1
end_operator
begin_operator
walk driver2 p2-0 s0
0
1
0 5 1 3
1
end_operator
begin_operator
walk driver2 p2-0 s2
0
1
0 5 1 5
1
end_operator
begin_operator
walk driver2 p2-1 s1
0
1
0 5 2 4
1
end_operator
begin_operator
walk driver2 p2-1 s2
0
1
0 5 2 5
1
end_operator
begin_operator
walk driver2 s0 p0-1
0
1
0 5 3 0
1
end_operator
begin_operator
walk driver2 s0 p2-0
0
1
0 5 3 1
1
end_operator
begin_operator
walk driver2 s1 p0-1
0
1
0 5 4 0
1
end_operator
begin_operator
walk driver2 s1 p2-1
0
1
0 5 4 2
1
end_operator
begin_operator
walk driver2 s2 p2-0
0
1
0 5 5 1
1
end_operator
begin_operator
walk driver2 s2 p2-1
0
1
0 5 5 2
1
end_operator
0
