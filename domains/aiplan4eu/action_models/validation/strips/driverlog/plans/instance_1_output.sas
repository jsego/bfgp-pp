begin_version
3
end_version
begin_metric
0
end_metric
14
begin_variable
var0
-1
2
Atom empty(truck2)
NegatedAtom empty(truck2)
end_variable
begin_variable
var1
-1
2
Atom empty(truck3)
NegatedAtom empty(truck3)
end_variable
begin_variable
var2
-1
2
Atom empty(truck1)
NegatedAtom empty(truck1)
end_variable
begin_variable
var3
-1
6
Atom at(truck1, s0)
Atom at(truck1, s1)
Atom at(truck1, s2)
Atom at(truck1, s3)
Atom at(truck1, s4)
Atom at(truck1, s5)
end_variable
begin_variable
var4
-1
6
Atom at(truck2, s0)
Atom at(truck2, s1)
Atom at(truck2, s2)
Atom at(truck2, s3)
Atom at(truck2, s4)
Atom at(truck2, s5)
end_variable
begin_variable
var5
-1
6
Atom at(truck3, s0)
Atom at(truck3, s1)
Atom at(truck3, s2)
Atom at(truck3, s3)
Atom at(truck3, s4)
Atom at(truck3, s5)
end_variable
begin_variable
var6
-1
18
Atom at(driver1, p1-0)
Atom at(driver1, p1-4)
Atom at(driver1, p1-5)
Atom at(driver1, p2-1)
Atom at(driver1, p2-3)
Atom at(driver1, p3-0)
Atom at(driver1, p3-1)
Atom at(driver1, p3-5)
Atom at(driver1, p4-5)
Atom at(driver1, s0)
Atom at(driver1, s1)
Atom at(driver1, s2)
Atom at(driver1, s3)
Atom at(driver1, s4)
Atom at(driver1, s5)
Atom driving(driver1, truck1)
Atom driving(driver1, truck2)
Atom driving(driver1, truck3)
end_variable
begin_variable
var7
-1
18
Atom at(driver2, p1-0)
Atom at(driver2, p1-4)
Atom at(driver2, p1-5)
Atom at(driver2, p2-1)
Atom at(driver2, p2-3)
Atom at(driver2, p3-0)
Atom at(driver2, p3-1)
Atom at(driver2, p3-5)
Atom at(driver2, p4-5)
Atom at(driver2, s0)
Atom at(driver2, s1)
Atom at(driver2, s2)
Atom at(driver2, s3)
Atom at(driver2, s4)
Atom at(driver2, s5)
Atom driving(driver2, truck1)
Atom driving(driver2, truck2)
Atom driving(driver2, truck3)
end_variable
begin_variable
var8
-1
9
Atom at(package6, s0)
Atom at(package6, s1)
Atom at(package6, s2)
Atom at(package6, s3)
Atom at(package6, s4)
Atom at(package6, s5)
Atom in(package6, truck1)
Atom in(package6, truck2)
Atom in(package6, truck3)
end_variable
begin_variable
var9
-1
9
Atom at(package5, s0)
Atom at(package5, s1)
Atom at(package5, s2)
Atom at(package5, s3)
Atom at(package5, s4)
Atom at(package5, s5)
Atom in(package5, truck1)
Atom in(package5, truck2)
Atom in(package5, truck3)
end_variable
begin_variable
var10
-1
9
Atom at(package4, s0)
Atom at(package4, s1)
Atom at(package4, s2)
Atom at(package4, s3)
Atom at(package4, s4)
Atom at(package4, s5)
Atom in(package4, truck1)
Atom in(package4, truck2)
Atom in(package4, truck3)
end_variable
begin_variable
var11
-1
9
Atom at(package3, s0)
Atom at(package3, s1)
Atom at(package3, s2)
Atom at(package3, s3)
Atom at(package3, s4)
Atom at(package3, s5)
Atom in(package3, truck1)
Atom in(package3, truck2)
Atom in(package3, truck3)
end_variable
begin_variable
var12
-1
9
Atom at(package2, s0)
Atom at(package2, s1)
Atom at(package2, s2)
Atom at(package2, s3)
Atom at(package2, s4)
Atom at(package2, s5)
Atom in(package2, truck1)
Atom in(package2, truck2)
Atom in(package2, truck3)
end_variable
begin_variable
var13
-1
9
Atom at(package1, s0)
Atom at(package1, s1)
Atom at(package1, s2)
Atom at(package1, s3)
Atom at(package1, s4)
Atom at(package1, s5)
Atom in(package1, truck1)
Atom in(package1, truck2)
Atom in(package1, truck3)
end_variable
3
begin_mutex_group
3
6 15
7 15
2 0
end_mutex_group
begin_mutex_group
3
6 16
7 16
0 0
end_mutex_group
begin_mutex_group
3
6 17
7 17
1 0
end_mutex_group
begin_state
0
0
0
0
4
5
13
9
2
4
4
4
0
1
end_state
begin_goal
8
6 10
7 9
8 2
9 3
10 1
11 5
12 1
13 5
end_goal
516
begin_operator
board-truck driver1 truck1 s0
1
3 0
2
0 6 9 15
0 2 0 1
1
end_operator
begin_operator
board-truck driver1 truck1 s1
1
3 1
2
0 6 10 15
0 2 0 1
1
end_operator
begin_operator
board-truck driver1 truck1 s2
1
3 2
2
0 6 11 15
0 2 0 1
1
end_operator
begin_operator
board-truck driver1 truck1 s3
1
3 3
2
0 6 12 15
0 2 0 1
1
end_operator
begin_operator
board-truck driver1 truck1 s4
1
3 4
2
0 6 13 15
0 2 0 1
1
end_operator
begin_operator
board-truck driver1 truck1 s5
1
3 5
2
0 6 14 15
0 2 0 1
1
end_operator
begin_operator
board-truck driver1 truck2 s0
1
4 0
2
0 6 9 16
0 0 0 1
1
end_operator
begin_operator
board-truck driver1 truck2 s1
1
4 1
2
0 6 10 16
0 0 0 1
1
end_operator
begin_operator
board-truck driver1 truck2 s2
1
4 2
2
0 6 11 16
0 0 0 1
1
end_operator
begin_operator
board-truck driver1 truck2 s3
1
4 3
2
0 6 12 16
0 0 0 1
1
end_operator
begin_operator
board-truck driver1 truck2 s4
1
4 4
2
0 6 13 16
0 0 0 1
1
end_operator
begin_operator
board-truck driver1 truck2 s5
1
4 5
2
0 6 14 16
0 0 0 1
1
end_operator
begin_operator
board-truck driver1 truck3 s0
1
5 0
2
0 6 9 17
0 1 0 1
1
end_operator
begin_operator
board-truck driver1 truck3 s1
1
5 1
2
0 6 10 17
0 1 0 1
1
end_operator
begin_operator
board-truck driver1 truck3 s2
1
5 2
2
0 6 11 17
0 1 0 1
1
end_operator
begin_operator
board-truck driver1 truck3 s3
1
5 3
2
0 6 12 17
0 1 0 1
1
end_operator
begin_operator
board-truck driver1 truck3 s4
1
5 4
2
0 6 13 17
0 1 0 1
1
end_operator
begin_operator
board-truck driver1 truck3 s5
1
5 5
2
0 6 14 17
0 1 0 1
1
end_operator
begin_operator
board-truck driver2 truck1 s0
1
3 0
2
0 7 9 15
0 2 0 1
1
end_operator
begin_operator
board-truck driver2 truck1 s1
1
3 1
2
0 7 10 15
0 2 0 1
1
end_operator
begin_operator
board-truck driver2 truck1 s2
1
3 2
2
0 7 11 15
0 2 0 1
1
end_operator
begin_operator
board-truck driver2 truck1 s3
1
3 3
2
0 7 12 15
0 2 0 1
1
end_operator
begin_operator
board-truck driver2 truck1 s4
1
3 4
2
0 7 13 15
0 2 0 1
1
end_operator
begin_operator
board-truck driver2 truck1 s5
1
3 5
2
0 7 14 15
0 2 0 1
1
end_operator
begin_operator
board-truck driver2 truck2 s0
1
4 0
2
0 7 9 16
0 0 0 1
1
end_operator
begin_operator
board-truck driver2 truck2 s1
1
4 1
2
0 7 10 16
0 0 0 1
1
end_operator
begin_operator
board-truck driver2 truck2 s2
1
4 2
2
0 7 11 16
0 0 0 1
1
end_operator
begin_operator
board-truck driver2 truck2 s3
1
4 3
2
0 7 12 16
0 0 0 1
1
end_operator
begin_operator
board-truck driver2 truck2 s4
1
4 4
2
0 7 13 16
0 0 0 1
1
end_operator
begin_operator
board-truck driver2 truck2 s5
1
4 5
2
0 7 14 16
0 0 0 1
1
end_operator
begin_operator
board-truck driver2 truck3 s0
1
5 0
2
0 7 9 17
0 1 0 1
1
end_operator
begin_operator
board-truck driver2 truck3 s1
1
5 1
2
0 7 10 17
0 1 0 1
1
end_operator
begin_operator
board-truck driver2 truck3 s2
1
5 2
2
0 7 11 17
0 1 0 1
1
end_operator
begin_operator
board-truck driver2 truck3 s3
1
5 3
2
0 7 12 17
0 1 0 1
1
end_operator
begin_operator
board-truck driver2 truck3 s4
1
5 4
2
0 7 13 17
0 1 0 1
1
end_operator
begin_operator
board-truck driver2 truck3 s5
1
5 5
2
0 7 14 17
0 1 0 1
1
end_operator
begin_operator
disembark-truck driver1 truck1 s0
1
3 0
2
0 6 15 9
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck1 s1
1
3 1
2
0 6 15 10
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck1 s2
1
3 2
2
0 6 15 11
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck1 s3
1
3 3
2
0 6 15 12
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck1 s4
1
3 4
2
0 6 15 13
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck1 s5
1
3 5
2
0 6 15 14
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck2 s0
1
4 0
2
0 6 16 9
0 0 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck2 s1
1
4 1
2
0 6 16 10
0 0 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck2 s2
1
4 2
2
0 6 16 11
0 0 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck2 s3
1
4 3
2
0 6 16 12
0 0 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck2 s4
1
4 4
2
0 6 16 13
0 0 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck2 s5
1
4 5
2
0 6 16 14
0 0 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck3 s0
1
5 0
2
0 6 17 9
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck3 s1
1
5 1
2
0 6 17 10
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck3 s2
1
5 2
2
0 6 17 11
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck3 s3
1
5 3
2
0 6 17 12
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck3 s4
1
5 4
2
0 6 17 13
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver1 truck3 s5
1
5 5
2
0 6 17 14
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck1 s0
1
3 0
2
0 7 15 9
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck1 s1
1
3 1
2
0 7 15 10
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck1 s2
1
3 2
2
0 7 15 11
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck1 s3
1
3 3
2
0 7 15 12
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck1 s4
1
3 4
2
0 7 15 13
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck1 s5
1
3 5
2
0 7 15 14
0 2 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck2 s0
1
4 0
2
0 7 16 9
0 0 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck2 s1
1
4 1
2
0 7 16 10
0 0 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck2 s2
1
4 2
2
0 7 16 11
0 0 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck2 s3
1
4 3
2
0 7 16 12
0 0 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck2 s4
1
4 4
2
0 7 16 13
0 0 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck2 s5
1
4 5
2
0 7 16 14
0 0 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck3 s0
1
5 0
2
0 7 17 9
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck3 s1
1
5 1
2
0 7 17 10
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck3 s2
1
5 2
2
0 7 17 11
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck3 s3
1
5 3
2
0 7 17 12
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck3 s4
1
5 4
2
0 7 17 13
0 1 -1 0
1
end_operator
begin_operator
disembark-truck driver2 truck3 s5
1
5 5
2
0 7 17 14
0 1 -1 0
1
end_operator
begin_operator
drive-truck truck1 s0 s1 driver1
1
6 15
1
0 3 0 1
1
end_operator
begin_operator
drive-truck truck1 s0 s1 driver2
1
7 15
1
0 3 0 1
1
end_operator
begin_operator
drive-truck truck1 s0 s2 driver1
1
6 15
1
0 3 0 2
1
end_operator
begin_operator
drive-truck truck1 s0 s2 driver2
1
7 15
1
0 3 0 2
1
end_operator
begin_operator
drive-truck truck1 s0 s3 driver1
1
6 15
1
0 3 0 3
1
end_operator
begin_operator
drive-truck truck1 s0 s3 driver2
1
7 15
1
0 3 0 3
1
end_operator
begin_operator
drive-truck truck1 s0 s4 driver1
1
6 15
1
0 3 0 4
1
end_operator
begin_operator
drive-truck truck1 s0 s4 driver2
1
7 15
1
0 3 0 4
1
end_operator
begin_operator
drive-truck truck1 s0 s5 driver1
1
6 15
1
0 3 0 5
1
end_operator
begin_operator
drive-truck truck1 s0 s5 driver2
1
7 15
1
0 3 0 5
1
end_operator
begin_operator
drive-truck truck1 s1 s0 driver1
1
6 15
1
0 3 1 0
1
end_operator
begin_operator
drive-truck truck1 s1 s0 driver2
1
7 15
1
0 3 1 0
1
end_operator
begin_operator
drive-truck truck1 s1 s2 driver1
1
6 15
1
0 3 1 2
1
end_operator
begin_operator
drive-truck truck1 s1 s2 driver2
1
7 15
1
0 3 1 2
1
end_operator
begin_operator
drive-truck truck1 s1 s3 driver1
1
6 15
1
0 3 1 3
1
end_operator
begin_operator
drive-truck truck1 s1 s3 driver2
1
7 15
1
0 3 1 3
1
end_operator
begin_operator
drive-truck truck1 s1 s4 driver1
1
6 15
1
0 3 1 4
1
end_operator
begin_operator
drive-truck truck1 s1 s4 driver2
1
7 15
1
0 3 1 4
1
end_operator
begin_operator
drive-truck truck1 s1 s5 driver1
1
6 15
1
0 3 1 5
1
end_operator
begin_operator
drive-truck truck1 s1 s5 driver2
1
7 15
1
0 3 1 5
1
end_operator
begin_operator
drive-truck truck1 s2 s0 driver1
1
6 15
1
0 3 2 0
1
end_operator
begin_operator
drive-truck truck1 s2 s0 driver2
1
7 15
1
0 3 2 0
1
end_operator
begin_operator
drive-truck truck1 s2 s1 driver1
1
6 15
1
0 3 2 1
1
end_operator
begin_operator
drive-truck truck1 s2 s1 driver2
1
7 15
1
0 3 2 1
1
end_operator
begin_operator
drive-truck truck1 s2 s3 driver1
1
6 15
1
0 3 2 3
1
end_operator
begin_operator
drive-truck truck1 s2 s3 driver2
1
7 15
1
0 3 2 3
1
end_operator
begin_operator
drive-truck truck1 s3 s0 driver1
1
6 15
1
0 3 3 0
1
end_operator
begin_operator
drive-truck truck1 s3 s0 driver2
1
7 15
1
0 3 3 0
1
end_operator
begin_operator
drive-truck truck1 s3 s1 driver1
1
6 15
1
0 3 3 1
1
end_operator
begin_operator
drive-truck truck1 s3 s1 driver2
1
7 15
1
0 3 3 1
1
end_operator
begin_operator
drive-truck truck1 s3 s2 driver1
1
6 15
1
0 3 3 2
1
end_operator
begin_operator
drive-truck truck1 s3 s2 driver2
1
7 15
1
0 3 3 2
1
end_operator
begin_operator
drive-truck truck1 s3 s4 driver1
1
6 15
1
0 3 3 4
1
end_operator
begin_operator
drive-truck truck1 s3 s4 driver2
1
7 15
1
0 3 3 4
1
end_operator
begin_operator
drive-truck truck1 s3 s5 driver1
1
6 15
1
0 3 3 5
1
end_operator
begin_operator
drive-truck truck1 s3 s5 driver2
1
7 15
1
0 3 3 5
1
end_operator
begin_operator
drive-truck truck1 s4 s0 driver1
1
6 15
1
0 3 4 0
1
end_operator
begin_operator
drive-truck truck1 s4 s0 driver2
1
7 15
1
0 3 4 0
1
end_operator
begin_operator
drive-truck truck1 s4 s1 driver1
1
6 15
1
0 3 4 1
1
end_operator
begin_operator
drive-truck truck1 s4 s1 driver2
1
7 15
1
0 3 4 1
1
end_operator
begin_operator
drive-truck truck1 s4 s3 driver1
1
6 15
1
0 3 4 3
1
end_operator
begin_operator
drive-truck truck1 s4 s3 driver2
1
7 15
1
0 3 4 3
1
end_operator
begin_operator
drive-truck truck1 s4 s5 driver1
1
6 15
1
0 3 4 5
1
end_operator
begin_operator
drive-truck truck1 s4 s5 driver2
1
7 15
1
0 3 4 5
1
end_operator
begin_operator
drive-truck truck1 s5 s0 driver1
1
6 15
1
0 3 5 0
1
end_operator
begin_operator
drive-truck truck1 s5 s0 driver2
1
7 15
1
0 3 5 0
1
end_operator
begin_operator
drive-truck truck1 s5 s1 driver1
1
6 15
1
0 3 5 1
1
end_operator
begin_operator
drive-truck truck1 s5 s1 driver2
1
7 15
1
0 3 5 1
1
end_operator
begin_operator
drive-truck truck1 s5 s3 driver1
1
6 15
1
0 3 5 3
1
end_operator
begin_operator
drive-truck truck1 s5 s3 driver2
1
7 15
1
0 3 5 3
1
end_operator
begin_operator
drive-truck truck1 s5 s4 driver1
1
6 15
1
0 3 5 4
1
end_operator
begin_operator
drive-truck truck1 s5 s4 driver2
1
7 15
1
0 3 5 4
1
end_operator
begin_operator
drive-truck truck2 s0 s1 driver1
1
6 16
1
0 4 0 1
1
end_operator
begin_operator
drive-truck truck2 s0 s1 driver2
1
7 16
1
0 4 0 1
1
end_operator
begin_operator
drive-truck truck2 s0 s2 driver1
1
6 16
1
0 4 0 2
1
end_operator
begin_operator
drive-truck truck2 s0 s2 driver2
1
7 16
1
0 4 0 2
1
end_operator
begin_operator
drive-truck truck2 s0 s3 driver1
1
6 16
1
0 4 0 3
1
end_operator
begin_operator
drive-truck truck2 s0 s3 driver2
1
7 16
1
0 4 0 3
1
end_operator
begin_operator
drive-truck truck2 s0 s4 driver1
1
6 16
1
0 4 0 4
1
end_operator
begin_operator
drive-truck truck2 s0 s4 driver2
1
7 16
1
0 4 0 4
1
end_operator
begin_operator
drive-truck truck2 s0 s5 driver1
1
6 16
1
0 4 0 5
1
end_operator
begin_operator
drive-truck truck2 s0 s5 driver2
1
7 16
1
0 4 0 5
1
end_operator
begin_operator
drive-truck truck2 s1 s0 driver1
1
6 16
1
0 4 1 0
1
end_operator
begin_operator
drive-truck truck2 s1 s0 driver2
1
7 16
1
0 4 1 0
1
end_operator
begin_operator
drive-truck truck2 s1 s2 driver1
1
6 16
1
0 4 1 2
1
end_operator
begin_operator
drive-truck truck2 s1 s2 driver2
1
7 16
1
0 4 1 2
1
end_operator
begin_operator
drive-truck truck2 s1 s3 driver1
1
6 16
1
0 4 1 3
1
end_operator
begin_operator
drive-truck truck2 s1 s3 driver2
1
7 16
1
0 4 1 3
1
end_operator
begin_operator
drive-truck truck2 s1 s4 driver1
1
6 16
1
0 4 1 4
1
end_operator
begin_operator
drive-truck truck2 s1 s4 driver2
1
7 16
1
0 4 1 4
1
end_operator
begin_operator
drive-truck truck2 s1 s5 driver1
1
6 16
1
0 4 1 5
1
end_operator
begin_operator
drive-truck truck2 s1 s5 driver2
1
7 16
1
0 4 1 5
1
end_operator
begin_operator
drive-truck truck2 s2 s0 driver1
1
6 16
1
0 4 2 0
1
end_operator
begin_operator
drive-truck truck2 s2 s0 driver2
1
7 16
1
0 4 2 0
1
end_operator
begin_operator
drive-truck truck2 s2 s1 driver1
1
6 16
1
0 4 2 1
1
end_operator
begin_operator
drive-truck truck2 s2 s1 driver2
1
7 16
1
0 4 2 1
1
end_operator
begin_operator
drive-truck truck2 s2 s3 driver1
1
6 16
1
0 4 2 3
1
end_operator
begin_operator
drive-truck truck2 s2 s3 driver2
1
7 16
1
0 4 2 3
1
end_operator
begin_operator
drive-truck truck2 s3 s0 driver1
1
6 16
1
0 4 3 0
1
end_operator
begin_operator
drive-truck truck2 s3 s0 driver2
1
7 16
1
0 4 3 0
1
end_operator
begin_operator
drive-truck truck2 s3 s1 driver1
1
6 16
1
0 4 3 1
1
end_operator
begin_operator
drive-truck truck2 s3 s1 driver2
1
7 16
1
0 4 3 1
1
end_operator
begin_operator
drive-truck truck2 s3 s2 driver1
1
6 16
1
0 4 3 2
1
end_operator
begin_operator
drive-truck truck2 s3 s2 driver2
1
7 16
1
0 4 3 2
1
end_operator
begin_operator
drive-truck truck2 s3 s4 driver1
1
6 16
1
0 4 3 4
1
end_operator
begin_operator
drive-truck truck2 s3 s4 driver2
1
7 16
1
0 4 3 4
1
end_operator
begin_operator
drive-truck truck2 s3 s5 driver1
1
6 16
1
0 4 3 5
1
end_operator
begin_operator
drive-truck truck2 s3 s5 driver2
1
7 16
1
0 4 3 5
1
end_operator
begin_operator
drive-truck truck2 s4 s0 driver1
1
6 16
1
0 4 4 0
1
end_operator
begin_operator
drive-truck truck2 s4 s0 driver2
1
7 16
1
0 4 4 0
1
end_operator
begin_operator
drive-truck truck2 s4 s1 driver1
1
6 16
1
0 4 4 1
1
end_operator
begin_operator
drive-truck truck2 s4 s1 driver2
1
7 16
1
0 4 4 1
1
end_operator
begin_operator
drive-truck truck2 s4 s3 driver1
1
6 16
1
0 4 4 3
1
end_operator
begin_operator
drive-truck truck2 s4 s3 driver2
1
7 16
1
0 4 4 3
1
end_operator
begin_operator
drive-truck truck2 s4 s5 driver1
1
6 16
1
0 4 4 5
1
end_operator
begin_operator
drive-truck truck2 s4 s5 driver2
1
7 16
1
0 4 4 5
1
end_operator
begin_operator
drive-truck truck2 s5 s0 driver1
1
6 16
1
0 4 5 0
1
end_operator
begin_operator
drive-truck truck2 s5 s0 driver2
1
7 16
1
0 4 5 0
1
end_operator
begin_operator
drive-truck truck2 s5 s1 driver1
1
6 16
1
0 4 5 1
1
end_operator
begin_operator
drive-truck truck2 s5 s1 driver2
1
7 16
1
0 4 5 1
1
end_operator
begin_operator
drive-truck truck2 s5 s3 driver1
1
6 16
1
0 4 5 3
1
end_operator
begin_operator
drive-truck truck2 s5 s3 driver2
1
7 16
1
0 4 5 3
1
end_operator
begin_operator
drive-truck truck2 s5 s4 driver1
1
6 16
1
0 4 5 4
1
end_operator
begin_operator
drive-truck truck2 s5 s4 driver2
1
7 16
1
0 4 5 4
1
end_operator
begin_operator
drive-truck truck3 s0 s1 driver1
1
6 17
1
0 5 0 1
1
end_operator
begin_operator
drive-truck truck3 s0 s1 driver2
1
7 17
1
0 5 0 1
1
end_operator
begin_operator
drive-truck truck3 s0 s2 driver1
1
6 17
1
0 5 0 2
1
end_operator
begin_operator
drive-truck truck3 s0 s2 driver2
1
7 17
1
0 5 0 2
1
end_operator
begin_operator
drive-truck truck3 s0 s3 driver1
1
6 17
1
0 5 0 3
1
end_operator
begin_operator
drive-truck truck3 s0 s3 driver2
1
7 17
1
0 5 0 3
1
end_operator
begin_operator
drive-truck truck3 s0 s4 driver1
1
6 17
1
0 5 0 4
1
end_operator
begin_operator
drive-truck truck3 s0 s4 driver2
1
7 17
1
0 5 0 4
1
end_operator
begin_operator
drive-truck truck3 s0 s5 driver1
1
6 17
1
0 5 0 5
1
end_operator
begin_operator
drive-truck truck3 s0 s5 driver2
1
7 17
1
0 5 0 5
1
end_operator
begin_operator
drive-truck truck3 s1 s0 driver1
1
6 17
1
0 5 1 0
1
end_operator
begin_operator
drive-truck truck3 s1 s0 driver2
1
7 17
1
0 5 1 0
1
end_operator
begin_operator
drive-truck truck3 s1 s2 driver1
1
6 17
1
0 5 1 2
1
end_operator
begin_operator
drive-truck truck3 s1 s2 driver2
1
7 17
1
0 5 1 2
1
end_operator
begin_operator
drive-truck truck3 s1 s3 driver1
1
6 17
1
0 5 1 3
1
end_operator
begin_operator
drive-truck truck3 s1 s3 driver2
1
7 17
1
0 5 1 3
1
end_operator
begin_operator
drive-truck truck3 s1 s4 driver1
1
6 17
1
0 5 1 4
1
end_operator
begin_operator
drive-truck truck3 s1 s4 driver2
1
7 17
1
0 5 1 4
1
end_operator
begin_operator
drive-truck truck3 s1 s5 driver1
1
6 17
1
0 5 1 5
1
end_operator
begin_operator
drive-truck truck3 s1 s5 driver2
1
7 17
1
0 5 1 5
1
end_operator
begin_operator
drive-truck truck3 s2 s0 driver1
1
6 17
1
0 5 2 0
1
end_operator
begin_operator
drive-truck truck3 s2 s0 driver2
1
7 17
1
0 5 2 0
1
end_operator
begin_operator
drive-truck truck3 s2 s1 driver1
1
6 17
1
0 5 2 1
1
end_operator
begin_operator
drive-truck truck3 s2 s1 driver2
1
7 17
1
0 5 2 1
1
end_operator
begin_operator
drive-truck truck3 s2 s3 driver1
1
6 17
1
0 5 2 3
1
end_operator
begin_operator
drive-truck truck3 s2 s3 driver2
1
7 17
1
0 5 2 3
1
end_operator
begin_operator
drive-truck truck3 s3 s0 driver1
1
6 17
1
0 5 3 0
1
end_operator
begin_operator
drive-truck truck3 s3 s0 driver2
1
7 17
1
0 5 3 0
1
end_operator
begin_operator
drive-truck truck3 s3 s1 driver1
1
6 17
1
0 5 3 1
1
end_operator
begin_operator
drive-truck truck3 s3 s1 driver2
1
7 17
1
0 5 3 1
1
end_operator
begin_operator
drive-truck truck3 s3 s2 driver1
1
6 17
1
0 5 3 2
1
end_operator
begin_operator
drive-truck truck3 s3 s2 driver2
1
7 17
1
0 5 3 2
1
end_operator
begin_operator
drive-truck truck3 s3 s4 driver1
1
6 17
1
0 5 3 4
1
end_operator
begin_operator
drive-truck truck3 s3 s4 driver2
1
7 17
1
0 5 3 4
1
end_operator
begin_operator
drive-truck truck3 s3 s5 driver1
1
6 17
1
0 5 3 5
1
end_operator
begin_operator
drive-truck truck3 s3 s5 driver2
1
7 17
1
0 5 3 5
1
end_operator
begin_operator
drive-truck truck3 s4 s0 driver1
1
6 17
1
0 5 4 0
1
end_operator
begin_operator
drive-truck truck3 s4 s0 driver2
1
7 17
1
0 5 4 0
1
end_operator
begin_operator
drive-truck truck3 s4 s1 driver1
1
6 17
1
0 5 4 1
1
end_operator
begin_operator
drive-truck truck3 s4 s1 driver2
1
7 17
1
0 5 4 1
1
end_operator
begin_operator
drive-truck truck3 s4 s3 driver1
1
6 17
1
0 5 4 3
1
end_operator
begin_operator
drive-truck truck3 s4 s3 driver2
1
7 17
1
0 5 4 3
1
end_operator
begin_operator
drive-truck truck3 s4 s5 driver1
1
6 17
1
0 5 4 5
1
end_operator
begin_operator
drive-truck truck3 s4 s5 driver2
1
7 17
1
0 5 4 5
1
end_operator
begin_operator
drive-truck truck3 s5 s0 driver1
1
6 17
1
0 5 5 0
1
end_operator
begin_operator
drive-truck truck3 s5 s0 driver2
1
7 17
1
0 5 5 0
1
end_operator
begin_operator
drive-truck truck3 s5 s1 driver1
1
6 17
1
0 5 5 1
1
end_operator
begin_operator
drive-truck truck3 s5 s1 driver2
1
7 17
1
0 5 5 1
1
end_operator
begin_operator
drive-truck truck3 s5 s3 driver1
1
6 17
1
0 5 5 3
1
end_operator
begin_operator
drive-truck truck3 s5 s3 driver2
1
7 17
1
0 5 5 3
1
end_operator
begin_operator
drive-truck truck3 s5 s4 driver1
1
6 17
1
0 5 5 4
1
end_operator
begin_operator
drive-truck truck3 s5 s4 driver2
1
7 17
1
0 5 5 4
1
end_operator
begin_operator
load-truck package1 truck1 s0
1
3 0
1
0 13 0 6
1
end_operator
begin_operator
load-truck package1 truck1 s1
1
3 1
1
0 13 1 6
1
end_operator
begin_operator
load-truck package1 truck1 s2
1
3 2
1
0 13 2 6
1
end_operator
begin_operator
load-truck package1 truck1 s3
1
3 3
1
0 13 3 6
1
end_operator
begin_operator
load-truck package1 truck1 s4
1
3 4
1
0 13 4 6
1
end_operator
begin_operator
load-truck package1 truck1 s5
1
3 5
1
0 13 5 6
1
end_operator
begin_operator
load-truck package1 truck2 s0
1
4 0
1
0 13 0 7
1
end_operator
begin_operator
load-truck package1 truck2 s1
1
4 1
1
0 13 1 7
1
end_operator
begin_operator
load-truck package1 truck2 s2
1
4 2
1
0 13 2 7
1
end_operator
begin_operator
load-truck package1 truck2 s3
1
4 3
1
0 13 3 7
1
end_operator
begin_operator
load-truck package1 truck2 s4
1
4 4
1
0 13 4 7
1
end_operator
begin_operator
load-truck package1 truck2 s5
1
4 5
1
0 13 5 7
1
end_operator
begin_operator
load-truck package1 truck3 s0
1
5 0
1
0 13 0 8
1
end_operator
begin_operator
load-truck package1 truck3 s1
1
5 1
1
0 13 1 8
1
end_operator
begin_operator
load-truck package1 truck3 s2
1
5 2
1
0 13 2 8
1
end_operator
begin_operator
load-truck package1 truck3 s3
1
5 3
1
0 13 3 8
1
end_operator
begin_operator
load-truck package1 truck3 s4
1
5 4
1
0 13 4 8
1
end_operator
begin_operator
load-truck package1 truck3 s5
1
5 5
1
0 13 5 8
1
end_operator
begin_operator
load-truck package2 truck1 s0
1
3 0
1
0 12 0 6
1
end_operator
begin_operator
load-truck package2 truck1 s1
1
3 1
1
0 12 1 6
1
end_operator
begin_operator
load-truck package2 truck1 s2
1
3 2
1
0 12 2 6
1
end_operator
begin_operator
load-truck package2 truck1 s3
1
3 3
1
0 12 3 6
1
end_operator
begin_operator
load-truck package2 truck1 s4
1
3 4
1
0 12 4 6
1
end_operator
begin_operator
load-truck package2 truck1 s5
1
3 5
1
0 12 5 6
1
end_operator
begin_operator
load-truck package2 truck2 s0
1
4 0
1
0 12 0 7
1
end_operator
begin_operator
load-truck package2 truck2 s1
1
4 1
1
0 12 1 7
1
end_operator
begin_operator
load-truck package2 truck2 s2
1
4 2
1
0 12 2 7
1
end_operator
begin_operator
load-truck package2 truck2 s3
1
4 3
1
0 12 3 7
1
end_operator
begin_operator
load-truck package2 truck2 s4
1
4 4
1
0 12 4 7
1
end_operator
begin_operator
load-truck package2 truck2 s5
1
4 5
1
0 12 5 7
1
end_operator
begin_operator
load-truck package2 truck3 s0
1
5 0
1
0 12 0 8
1
end_operator
begin_operator
load-truck package2 truck3 s1
1
5 1
1
0 12 1 8
1
end_operator
begin_operator
load-truck package2 truck3 s2
1
5 2
1
0 12 2 8
1
end_operator
begin_operator
load-truck package2 truck3 s3
1
5 3
1
0 12 3 8
1
end_operator
begin_operator
load-truck package2 truck3 s4
1
5 4
1
0 12 4 8
1
end_operator
begin_operator
load-truck package2 truck3 s5
1
5 5
1
0 12 5 8
1
end_operator
begin_operator
load-truck package3 truck1 s0
1
3 0
1
0 11 0 6
1
end_operator
begin_operator
load-truck package3 truck1 s1
1
3 1
1
0 11 1 6
1
end_operator
begin_operator
load-truck package3 truck1 s2
1
3 2
1
0 11 2 6
1
end_operator
begin_operator
load-truck package3 truck1 s3
1
3 3
1
0 11 3 6
1
end_operator
begin_operator
load-truck package3 truck1 s4
1
3 4
1
0 11 4 6
1
end_operator
begin_operator
load-truck package3 truck1 s5
1
3 5
1
0 11 5 6
1
end_operator
begin_operator
load-truck package3 truck2 s0
1
4 0
1
0 11 0 7
1
end_operator
begin_operator
load-truck package3 truck2 s1
1
4 1
1
0 11 1 7
1
end_operator
begin_operator
load-truck package3 truck2 s2
1
4 2
1
0 11 2 7
1
end_operator
begin_operator
load-truck package3 truck2 s3
1
4 3
1
0 11 3 7
1
end_operator
begin_operator
load-truck package3 truck2 s4
1
4 4
1
0 11 4 7
1
end_operator
begin_operator
load-truck package3 truck2 s5
1
4 5
1
0 11 5 7
1
end_operator
begin_operator
load-truck package3 truck3 s0
1
5 0
1
0 11 0 8
1
end_operator
begin_operator
load-truck package3 truck3 s1
1
5 1
1
0 11 1 8
1
end_operator
begin_operator
load-truck package3 truck3 s2
1
5 2
1
0 11 2 8
1
end_operator
begin_operator
load-truck package3 truck3 s3
1
5 3
1
0 11 3 8
1
end_operator
begin_operator
load-truck package3 truck3 s4
1
5 4
1
0 11 4 8
1
end_operator
begin_operator
load-truck package3 truck3 s5
1
5 5
1
0 11 5 8
1
end_operator
begin_operator
load-truck package4 truck1 s0
1
3 0
1
0 10 0 6
1
end_operator
begin_operator
load-truck package4 truck1 s1
1
3 1
1
0 10 1 6
1
end_operator
begin_operator
load-truck package4 truck1 s2
1
3 2
1
0 10 2 6
1
end_operator
begin_operator
load-truck package4 truck1 s3
1
3 3
1
0 10 3 6
1
end_operator
begin_operator
load-truck package4 truck1 s4
1
3 4
1
0 10 4 6
1
end_operator
begin_operator
load-truck package4 truck1 s5
1
3 5
1
0 10 5 6
1
end_operator
begin_operator
load-truck package4 truck2 s0
1
4 0
1
0 10 0 7
1
end_operator
begin_operator
load-truck package4 truck2 s1
1
4 1
1
0 10 1 7
1
end_operator
begin_operator
load-truck package4 truck2 s2
1
4 2
1
0 10 2 7
1
end_operator
begin_operator
load-truck package4 truck2 s3
1
4 3
1
0 10 3 7
1
end_operator
begin_operator
load-truck package4 truck2 s4
1
4 4
1
0 10 4 7
1
end_operator
begin_operator
load-truck package4 truck2 s5
1
4 5
1
0 10 5 7
1
end_operator
begin_operator
load-truck package4 truck3 s0
1
5 0
1
0 10 0 8
1
end_operator
begin_operator
load-truck package4 truck3 s1
1
5 1
1
0 10 1 8
1
end_operator
begin_operator
load-truck package4 truck3 s2
1
5 2
1
0 10 2 8
1
end_operator
begin_operator
load-truck package4 truck3 s3
1
5 3
1
0 10 3 8
1
end_operator
begin_operator
load-truck package4 truck3 s4
1
5 4
1
0 10 4 8
1
end_operator
begin_operator
load-truck package4 truck3 s5
1
5 5
1
0 10 5 8
1
end_operator
begin_operator
load-truck package5 truck1 s0
1
3 0
1
0 9 0 6
1
end_operator
begin_operator
load-truck package5 truck1 s1
1
3 1
1
0 9 1 6
1
end_operator
begin_operator
load-truck package5 truck1 s2
1
3 2
1
0 9 2 6
1
end_operator
begin_operator
load-truck package5 truck1 s3
1
3 3
1
0 9 3 6
1
end_operator
begin_operator
load-truck package5 truck1 s4
1
3 4
1
0 9 4 6
1
end_operator
begin_operator
load-truck package5 truck1 s5
1
3 5
1
0 9 5 6
1
end_operator
begin_operator
load-truck package5 truck2 s0
1
4 0
1
0 9 0 7
1
end_operator
begin_operator
load-truck package5 truck2 s1
1
4 1
1
0 9 1 7
1
end_operator
begin_operator
load-truck package5 truck2 s2
1
4 2
1
0 9 2 7
1
end_operator
begin_operator
load-truck package5 truck2 s3
1
4 3
1
0 9 3 7
1
end_operator
begin_operator
load-truck package5 truck2 s4
1
4 4
1
0 9 4 7
1
end_operator
begin_operator
load-truck package5 truck2 s5
1
4 5
1
0 9 5 7
1
end_operator
begin_operator
load-truck package5 truck3 s0
1
5 0
1
0 9 0 8
1
end_operator
begin_operator
load-truck package5 truck3 s1
1
5 1
1
0 9 1 8
1
end_operator
begin_operator
load-truck package5 truck3 s2
1
5 2
1
0 9 2 8
1
end_operator
begin_operator
load-truck package5 truck3 s3
1
5 3
1
0 9 3 8
1
end_operator
begin_operator
load-truck package5 truck3 s4
1
5 4
1
0 9 4 8
1
end_operator
begin_operator
load-truck package5 truck3 s5
1
5 5
1
0 9 5 8
1
end_operator
begin_operator
load-truck package6 truck1 s0
1
3 0
1
0 8 0 6
1
end_operator
begin_operator
load-truck package6 truck1 s1
1
3 1
1
0 8 1 6
1
end_operator
begin_operator
load-truck package6 truck1 s2
1
3 2
1
0 8 2 6
1
end_operator
begin_operator
load-truck package6 truck1 s3
1
3 3
1
0 8 3 6
1
end_operator
begin_operator
load-truck package6 truck1 s4
1
3 4
1
0 8 4 6
1
end_operator
begin_operator
load-truck package6 truck1 s5
1
3 5
1
0 8 5 6
1
end_operator
begin_operator
load-truck package6 truck2 s0
1
4 0
1
0 8 0 7
1
end_operator
begin_operator
load-truck package6 truck2 s1
1
4 1
1
0 8 1 7
1
end_operator
begin_operator
load-truck package6 truck2 s2
1
4 2
1
0 8 2 7
1
end_operator
begin_operator
load-truck package6 truck2 s3
1
4 3
1
0 8 3 7
1
end_operator
begin_operator
load-truck package6 truck2 s4
1
4 4
1
0 8 4 7
1
end_operator
begin_operator
load-truck package6 truck2 s5
1
4 5
1
0 8 5 7
1
end_operator
begin_operator
load-truck package6 truck3 s0
1
5 0
1
0 8 0 8
1
end_operator
begin_operator
load-truck package6 truck3 s1
1
5 1
1
0 8 1 8
1
end_operator
begin_operator
load-truck package6 truck3 s2
1
5 2
1
0 8 2 8
1
end_operator
begin_operator
load-truck package6 truck3 s3
1
5 3
1
0 8 3 8
1
end_operator
begin_operator
load-truck package6 truck3 s4
1
5 4
1
0 8 4 8
1
end_operator
begin_operator
load-truck package6 truck3 s5
1
5 5
1
0 8 5 8
1
end_operator
begin_operator
unload-truck package1 truck1 s0
1
3 0
1
0 13 6 0
1
end_operator
begin_operator
unload-truck package1 truck1 s1
1
3 1
1
0 13 6 1
1
end_operator
begin_operator
unload-truck package1 truck1 s2
1
3 2
1
0 13 6 2
1
end_operator
begin_operator
unload-truck package1 truck1 s3
1
3 3
1
0 13 6 3
1
end_operator
begin_operator
unload-truck package1 truck1 s4
1
3 4
1
0 13 6 4
1
end_operator
begin_operator
unload-truck package1 truck1 s5
1
3 5
1
0 13 6 5
1
end_operator
begin_operator
unload-truck package1 truck2 s0
1
4 0
1
0 13 7 0
1
end_operator
begin_operator
unload-truck package1 truck2 s1
1
4 1
1
0 13 7 1
1
end_operator
begin_operator
unload-truck package1 truck2 s2
1
4 2
1
0 13 7 2
1
end_operator
begin_operator
unload-truck package1 truck2 s3
1
4 3
1
0 13 7 3
1
end_operator
begin_operator
unload-truck package1 truck2 s4
1
4 4
1
0 13 7 4
1
end_operator
begin_operator
unload-truck package1 truck2 s5
1
4 5
1
0 13 7 5
1
end_operator
begin_operator
unload-truck package1 truck3 s0
1
5 0
1
0 13 8 0
1
end_operator
begin_operator
unload-truck package1 truck3 s1
1
5 1
1
0 13 8 1
1
end_operator
begin_operator
unload-truck package1 truck3 s2
1
5 2
1
0 13 8 2
1
end_operator
begin_operator
unload-truck package1 truck3 s3
1
5 3
1
0 13 8 3
1
end_operator
begin_operator
unload-truck package1 truck3 s4
1
5 4
1
0 13 8 4
1
end_operator
begin_operator
unload-truck package1 truck3 s5
1
5 5
1
0 13 8 5
1
end_operator
begin_operator
unload-truck package2 truck1 s0
1
3 0
1
0 12 6 0
1
end_operator
begin_operator
unload-truck package2 truck1 s1
1
3 1
1
0 12 6 1
1
end_operator
begin_operator
unload-truck package2 truck1 s2
1
3 2
1
0 12 6 2
1
end_operator
begin_operator
unload-truck package2 truck1 s3
1
3 3
1
0 12 6 3
1
end_operator
begin_operator
unload-truck package2 truck1 s4
1
3 4
1
0 12 6 4
1
end_operator
begin_operator
unload-truck package2 truck1 s5
1
3 5
1
0 12 6 5
1
end_operator
begin_operator
unload-truck package2 truck2 s0
1
4 0
1
0 12 7 0
1
end_operator
begin_operator
unload-truck package2 truck2 s1
1
4 1
1
0 12 7 1
1
end_operator
begin_operator
unload-truck package2 truck2 s2
1
4 2
1
0 12 7 2
1
end_operator
begin_operator
unload-truck package2 truck2 s3
1
4 3
1
0 12 7 3
1
end_operator
begin_operator
unload-truck package2 truck2 s4
1
4 4
1
0 12 7 4
1
end_operator
begin_operator
unload-truck package2 truck2 s5
1
4 5
1
0 12 7 5
1
end_operator
begin_operator
unload-truck package2 truck3 s0
1
5 0
1
0 12 8 0
1
end_operator
begin_operator
unload-truck package2 truck3 s1
1
5 1
1
0 12 8 1
1
end_operator
begin_operator
unload-truck package2 truck3 s2
1
5 2
1
0 12 8 2
1
end_operator
begin_operator
unload-truck package2 truck3 s3
1
5 3
1
0 12 8 3
1
end_operator
begin_operator
unload-truck package2 truck3 s4
1
5 4
1
0 12 8 4
1
end_operator
begin_operator
unload-truck package2 truck3 s5
1
5 5
1
0 12 8 5
1
end_operator
begin_operator
unload-truck package3 truck1 s0
1
3 0
1
0 11 6 0
1
end_operator
begin_operator
unload-truck package3 truck1 s1
1
3 1
1
0 11 6 1
1
end_operator
begin_operator
unload-truck package3 truck1 s2
1
3 2
1
0 11 6 2
1
end_operator
begin_operator
unload-truck package3 truck1 s3
1
3 3
1
0 11 6 3
1
end_operator
begin_operator
unload-truck package3 truck1 s4
1
3 4
1
0 11 6 4
1
end_operator
begin_operator
unload-truck package3 truck1 s5
1
3 5
1
0 11 6 5
1
end_operator
begin_operator
unload-truck package3 truck2 s0
1
4 0
1
0 11 7 0
1
end_operator
begin_operator
unload-truck package3 truck2 s1
1
4 1
1
0 11 7 1
1
end_operator
begin_operator
unload-truck package3 truck2 s2
1
4 2
1
0 11 7 2
1
end_operator
begin_operator
unload-truck package3 truck2 s3
1
4 3
1
0 11 7 3
1
end_operator
begin_operator
unload-truck package3 truck2 s4
1
4 4
1
0 11 7 4
1
end_operator
begin_operator
unload-truck package3 truck2 s5
1
4 5
1
0 11 7 5
1
end_operator
begin_operator
unload-truck package3 truck3 s0
1
5 0
1
0 11 8 0
1
end_operator
begin_operator
unload-truck package3 truck3 s1
1
5 1
1
0 11 8 1
1
end_operator
begin_operator
unload-truck package3 truck3 s2
1
5 2
1
0 11 8 2
1
end_operator
begin_operator
unload-truck package3 truck3 s3
1
5 3
1
0 11 8 3
1
end_operator
begin_operator
unload-truck package3 truck3 s4
1
5 4
1
0 11 8 4
1
end_operator
begin_operator
unload-truck package3 truck3 s5
1
5 5
1
0 11 8 5
1
end_operator
begin_operator
unload-truck package4 truck1 s0
1
3 0
1
0 10 6 0
1
end_operator
begin_operator
unload-truck package4 truck1 s1
1
3 1
1
0 10 6 1
1
end_operator
begin_operator
unload-truck package4 truck1 s2
1
3 2
1
0 10 6 2
1
end_operator
begin_operator
unload-truck package4 truck1 s3
1
3 3
1
0 10 6 3
1
end_operator
begin_operator
unload-truck package4 truck1 s4
1
3 4
1
0 10 6 4
1
end_operator
begin_operator
unload-truck package4 truck1 s5
1
3 5
1
0 10 6 5
1
end_operator
begin_operator
unload-truck package4 truck2 s0
1
4 0
1
0 10 7 0
1
end_operator
begin_operator
unload-truck package4 truck2 s1
1
4 1
1
0 10 7 1
1
end_operator
begin_operator
unload-truck package4 truck2 s2
1
4 2
1
0 10 7 2
1
end_operator
begin_operator
unload-truck package4 truck2 s3
1
4 3
1
0 10 7 3
1
end_operator
begin_operator
unload-truck package4 truck2 s4
1
4 4
1
0 10 7 4
1
end_operator
begin_operator
unload-truck package4 truck2 s5
1
4 5
1
0 10 7 5
1
end_operator
begin_operator
unload-truck package4 truck3 s0
1
5 0
1
0 10 8 0
1
end_operator
begin_operator
unload-truck package4 truck3 s1
1
5 1
1
0 10 8 1
1
end_operator
begin_operator
unload-truck package4 truck3 s2
1
5 2
1
0 10 8 2
1
end_operator
begin_operator
unload-truck package4 truck3 s3
1
5 3
1
0 10 8 3
1
end_operator
begin_operator
unload-truck package4 truck3 s4
1
5 4
1
0 10 8 4
1
end_operator
begin_operator
unload-truck package4 truck3 s5
1
5 5
1
0 10 8 5
1
end_operator
begin_operator
unload-truck package5 truck1 s0
1
3 0
1
0 9 6 0
1
end_operator
begin_operator
unload-truck package5 truck1 s1
1
3 1
1
0 9 6 1
1
end_operator
begin_operator
unload-truck package5 truck1 s2
1
3 2
1
0 9 6 2
1
end_operator
begin_operator
unload-truck package5 truck1 s3
1
3 3
1
0 9 6 3
1
end_operator
begin_operator
unload-truck package5 truck1 s4
1
3 4
1
0 9 6 4
1
end_operator
begin_operator
unload-truck package5 truck1 s5
1
3 5
1
0 9 6 5
1
end_operator
begin_operator
unload-truck package5 truck2 s0
1
4 0
1
0 9 7 0
1
end_operator
begin_operator
unload-truck package5 truck2 s1
1
4 1
1
0 9 7 1
1
end_operator
begin_operator
unload-truck package5 truck2 s2
1
4 2
1
0 9 7 2
1
end_operator
begin_operator
unload-truck package5 truck2 s3
1
4 3
1
0 9 7 3
1
end_operator
begin_operator
unload-truck package5 truck2 s4
1
4 4
1
0 9 7 4
1
end_operator
begin_operator
unload-truck package5 truck2 s5
1
4 5
1
0 9 7 5
1
end_operator
begin_operator
unload-truck package5 truck3 s0
1
5 0
1
0 9 8 0
1
end_operator
begin_operator
unload-truck package5 truck3 s1
1
5 1
1
0 9 8 1
1
end_operator
begin_operator
unload-truck package5 truck3 s2
1
5 2
1
0 9 8 2
1
end_operator
begin_operator
unload-truck package5 truck3 s3
1
5 3
1
0 9 8 3
1
end_operator
begin_operator
unload-truck package5 truck3 s4
1
5 4
1
0 9 8 4
1
end_operator
begin_operator
unload-truck package5 truck3 s5
1
5 5
1
0 9 8 5
1
end_operator
begin_operator
unload-truck package6 truck1 s0
1
3 0
1
0 8 6 0
1
end_operator
begin_operator
unload-truck package6 truck1 s1
1
3 1
1
0 8 6 1
1
end_operator
begin_operator
unload-truck package6 truck1 s2
1
3 2
1
0 8 6 2
1
end_operator
begin_operator
unload-truck package6 truck1 s3
1
3 3
1
0 8 6 3
1
end_operator
begin_operator
unload-truck package6 truck1 s4
1
3 4
1
0 8 6 4
1
end_operator
begin_operator
unload-truck package6 truck1 s5
1
3 5
1
0 8 6 5
1
end_operator
begin_operator
unload-truck package6 truck2 s0
1
4 0
1
0 8 7 0
1
end_operator
begin_operator
unload-truck package6 truck2 s1
1
4 1
1
0 8 7 1
1
end_operator
begin_operator
unload-truck package6 truck2 s2
1
4 2
1
0 8 7 2
1
end_operator
begin_operator
unload-truck package6 truck2 s3
1
4 3
1
0 8 7 3
1
end_operator
begin_operator
unload-truck package6 truck2 s4
1
4 4
1
0 8 7 4
1
end_operator
begin_operator
unload-truck package6 truck2 s5
1
4 5
1
0 8 7 5
1
end_operator
begin_operator
unload-truck package6 truck3 s0
1
5 0
1
0 8 8 0
1
end_operator
begin_operator
unload-truck package6 truck3 s1
1
5 1
1
0 8 8 1
1
end_operator
begin_operator
unload-truck package6 truck3 s2
1
5 2
1
0 8 8 2
1
end_operator
begin_operator
unload-truck package6 truck3 s3
1
5 3
1
0 8 8 3
1
end_operator
begin_operator
unload-truck package6 truck3 s4
1
5 4
1
0 8 8 4
1
end_operator
begin_operator
unload-truck package6 truck3 s5
1
5 5
1
0 8 8 5
1
end_operator
begin_operator
walk driver1 p1-0 s0
0
1
0 6 0 9
1
end_operator
begin_operator
walk driver1 p1-0 s1
0
1
0 6 0 10
1
end_operator
begin_operator
walk driver1 p1-4 s1
0
1
0 6 1 10
1
end_operator
begin_operator
walk driver1 p1-4 s4
0
1
0 6 1 13
1
end_operator
begin_operator
walk driver1 p1-5 s1
0
1
0 6 2 10
1
end_operator
begin_operator
walk driver1 p1-5 s5
0
1
0 6 2 14
1
end_operator
begin_operator
walk driver1 p2-1 s1
0
1
0 6 3 10
1
end_operator
begin_operator
walk driver1 p2-1 s2
0
1
0 6 3 11
1
end_operator
begin_operator
walk driver1 p2-3 s2
0
1
0 6 4 11
1
end_operator
begin_operator
walk driver1 p2-3 s3
0
1
0 6 4 12
1
end_operator
begin_operator
walk driver1 p3-0 s0
0
1
0 6 5 9
1
end_operator
begin_operator
walk driver1 p3-0 s3
0
1
0 6 5 12
1
end_operator
begin_operator
walk driver1 p3-1 s1
0
1
0 6 6 10
1
end_operator
begin_operator
walk driver1 p3-1 s3
0
1
0 6 6 12
1
end_operator
begin_operator
walk driver1 p3-5 s3
0
1
0 6 7 12
1
end_operator
begin_operator
walk driver1 p3-5 s5
0
1
0 6 7 14
1
end_operator
begin_operator
walk driver1 p4-5 s4
0
1
0 6 8 13
1
end_operator
begin_operator
walk driver1 p4-5 s5
0
1
0 6 8 14
1
end_operator
begin_operator
walk driver1 s0 p1-0
0
1
0 6 9 0
1
end_operator
begin_operator
walk driver1 s0 p3-0
0
1
0 6 9 5
1
end_operator
begin_operator
walk driver1 s1 p1-0
0
1
0 6 10 0
1
end_operator
begin_operator
walk driver1 s1 p1-4
0
1
0 6 10 1
1
end_operator
begin_operator
walk driver1 s1 p1-5
0
1
0 6 10 2
1
end_operator
begin_operator
walk driver1 s1 p2-1
0
1
0 6 10 3
1
end_operator
begin_operator
walk driver1 s1 p3-1
0
1
0 6 10 6
1
end_operator
begin_operator
walk driver1 s2 p2-1
0
1
0 6 11 3
1
end_operator
begin_operator
walk driver1 s2 p2-3
0
1
0 6 11 4
1
end_operator
begin_operator
walk driver1 s3 p2-3
0
1
0 6 12 4
1
end_operator
begin_operator
walk driver1 s3 p3-0
0
1
0 6 12 5
1
end_operator
begin_operator
walk driver1 s3 p3-1
0
1
0 6 12 6
1
end_operator
begin_operator
walk driver1 s3 p3-5
0
1
0 6 12 7
1
end_operator
begin_operator
walk driver1 s4 p1-4
0
1
0 6 13 1
1
end_operator
begin_operator
walk driver1 s4 p4-5
0
1
0 6 13 8
1
end_operator
begin_operator
walk driver1 s5 p1-5
0
1
0 6 14 2
1
end_operator
begin_operator
walk driver1 s5 p3-5
0
1
0 6 14 7
1
end_operator
begin_operator
walk driver1 s5 p4-5
0
1
0 6 14 8
1
end_operator
begin_operator
walk driver2 p1-0 s0
0
1
0 7 0 9
1
end_operator
begin_operator
walk driver2 p1-0 s1
0
1
0 7 0 10
1
end_operator
begin_operator
walk driver2 p1-4 s1
0
1
0 7 1 10
1
end_operator
begin_operator
walk driver2 p1-4 s4
0
1
0 7 1 13
1
end_operator
begin_operator
walk driver2 p1-5 s1
0
1
0 7 2 10
1
end_operator
begin_operator
walk driver2 p1-5 s5
0
1
0 7 2 14
1
end_operator
begin_operator
walk driver2 p2-1 s1
0
1
0 7 3 10
1
end_operator
begin_operator
walk driver2 p2-1 s2
0
1
0 7 3 11
1
end_operator
begin_operator
walk driver2 p2-3 s2
0
1
0 7 4 11
1
end_operator
begin_operator
walk driver2 p2-3 s3
0
1
0 7 4 12
1
end_operator
begin_operator
walk driver2 p3-0 s0
0
1
0 7 5 9
1
end_operator
begin_operator
walk driver2 p3-0 s3
0
1
0 7 5 12
1
end_operator
begin_operator
walk driver2 p3-1 s1
0
1
0 7 6 10
1
end_operator
begin_operator
walk driver2 p3-1 s3
0
1
0 7 6 12
1
end_operator
begin_operator
walk driver2 p3-5 s3
0
1
0 7 7 12
1
end_operator
begin_operator
walk driver2 p3-5 s5
0
1
0 7 7 14
1
end_operator
begin_operator
walk driver2 p4-5 s4
0
1
0 7 8 13
1
end_operator
begin_operator
walk driver2 p4-5 s5
0
1
0 7 8 14
1
end_operator
begin_operator
walk driver2 s0 p1-0
0
1
0 7 9 0
1
end_operator
begin_operator
walk driver2 s0 p3-0
0
1
0 7 9 5
1
end_operator
begin_operator
walk driver2 s1 p1-0
0
1
0 7 10 0
1
end_operator
begin_operator
walk driver2 s1 p1-4
0
1
0 7 10 1
1
end_operator
begin_operator
walk driver2 s1 p1-5
0
1
0 7 10 2
1
end_operator
begin_operator
walk driver2 s1 p2-1
0
1
0 7 10 3
1
end_operator
begin_operator
walk driver2 s1 p3-1
0
1
0 7 10 6
1
end_operator
begin_operator
walk driver2 s2 p2-1
0
1
0 7 11 3
1
end_operator
begin_operator
walk driver2 s2 p2-3
0
1
0 7 11 4
1
end_operator
begin_operator
walk driver2 s3 p2-3
0
1
0 7 12 4
1
end_operator
begin_operator
walk driver2 s3 p3-0
0
1
0 7 12 5
1
end_operator
begin_operator
walk driver2 s3 p3-1
0
1
0 7 12 6
1
end_operator
begin_operator
walk driver2 s3 p3-5
0
1
0 7 12 7
1
end_operator
begin_operator
walk driver2 s4 p1-4
0
1
0 7 13 1
1
end_operator
begin_operator
walk driver2 s4 p4-5
0
1
0 7 13 8
1
end_operator
begin_operator
walk driver2 s5 p1-5
0
1
0 7 14 2
1
end_operator
begin_operator
walk driver2 s5 p3-5
0
1
0 7 14 7
1
end_operator
begin_operator
walk driver2 s5 p4-5
0
1
0 7 14 8
1
end_operator
0
