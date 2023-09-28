begin_version
3
end_version
begin_metric
0
end_metric
30
begin_variable
var0
-1
8
Atom at(rover3, waypoint0)
Atom at(rover3, waypoint1)
Atom at(rover3, waypoint2)
Atom at(rover3, waypoint3)
Atom at(rover3, waypoint4)
Atom at(rover3, waypoint5)
Atom at(rover3, waypoint6)
Atom at(rover3, waypoint7)
end_variable
begin_variable
var1
-1
2
Atom calibrated(camera3, rover3)
NegatedAtom calibrated(camera3, rover3)
end_variable
begin_variable
var2
-1
2
Atom have_image(rover3, objective3, low_res)
NegatedAtom have_image(rover3, objective3, low_res)
end_variable
begin_variable
var3
-1
2
Atom have_image(rover3, objective2, low_res)
NegatedAtom have_image(rover3, objective2, low_res)
end_variable
begin_variable
var4
-1
2
Atom calibrated(camera0, rover3)
NegatedAtom calibrated(camera0, rover3)
end_variable
begin_variable
var5
-1
2
Atom have_image(rover3, objective1, high_res)
NegatedAtom have_image(rover3, objective1, high_res)
end_variable
begin_variable
var6
-1
7
Atom at(rover2, waypoint0)
Atom at(rover2, waypoint1)
Atom at(rover2, waypoint2)
Atom at(rover2, waypoint3)
Atom at(rover2, waypoint5)
Atom at(rover2, waypoint6)
Atom at(rover2, waypoint7)
end_variable
begin_variable
var7
-1
2
Atom calibrated(camera1, rover2)
NegatedAtom calibrated(camera1, rover2)
end_variable
begin_variable
var8
-1
2
Atom have_image(rover2, objective1, high_res)
NegatedAtom have_image(rover2, objective1, high_res)
end_variable
begin_variable
var9
-1
2
Atom communicated_image_data(objective1, high_res)
NegatedAtom communicated_image_data(objective1, high_res)
end_variable
begin_variable
var10
-1
8
Atom at(rover1, waypoint0)
Atom at(rover1, waypoint1)
Atom at(rover1, waypoint2)
Atom at(rover1, waypoint3)
Atom at(rover1, waypoint4)
Atom at(rover1, waypoint5)
Atom at(rover1, waypoint6)
Atom at(rover1, waypoint7)
end_variable
begin_variable
var11
-1
2
Atom empty(rover2store)
Atom full(rover2store)
end_variable
begin_variable
var12
-1
3
Atom at_rock_sample(waypoint0)
Atom have_rock_analysis(rover1, waypoint0)
Atom have_rock_analysis(rover3, waypoint0)
end_variable
begin_variable
var13
-1
3
Atom at_rock_sample(waypoint2)
Atom have_rock_analysis(rover1, waypoint2)
Atom have_rock_analysis(rover3, waypoint2)
end_variable
begin_variable
var14
-1
3
Atom at_rock_sample(waypoint3)
Atom have_rock_analysis(rover1, waypoint3)
Atom have_rock_analysis(rover3, waypoint3)
end_variable
begin_variable
var15
-1
3
Atom at_rock_sample(waypoint5)
Atom have_rock_analysis(rover1, waypoint5)
Atom have_rock_analysis(rover3, waypoint5)
end_variable
begin_variable
var16
-1
3
Atom at_rock_sample(waypoint6)
Atom have_rock_analysis(rover1, waypoint6)
Atom have_rock_analysis(rover3, waypoint6)
end_variable
begin_variable
var17
-1
3
Atom at_rock_sample(waypoint7)
Atom have_rock_analysis(rover1, waypoint7)
Atom have_rock_analysis(rover3, waypoint7)
end_variable
begin_variable
var18
-1
2
Atom empty(rover1store)
Atom full(rover1store)
end_variable
begin_variable
var19
-1
2
Atom empty(rover3store)
Atom full(rover3store)
end_variable
begin_variable
var20
-1
4
Atom at_soil_sample(waypoint0)
Atom have_soil_analysis(rover1, waypoint0)
Atom have_soil_analysis(rover2, waypoint0)
Atom have_soil_analysis(rover3, waypoint0)
end_variable
begin_variable
var21
-1
2
Atom communicated_soil_data(waypoint0)
NegatedAtom communicated_soil_data(waypoint0)
end_variable
begin_variable
var22
-1
2
Atom communicated_rock_data(waypoint6)
NegatedAtom communicated_rock_data(waypoint6)
end_variable
begin_variable
var23
-1
2
Atom communicated_rock_data(waypoint3)
NegatedAtom communicated_rock_data(waypoint3)
end_variable
begin_variable
var24
-1
8
Atom at(rover0, waypoint0)
Atom at(rover0, waypoint1)
Atom at(rover0, waypoint2)
Atom at(rover0, waypoint3)
Atom at(rover0, waypoint4)
Atom at(rover0, waypoint5)
Atom at(rover0, waypoint6)
Atom at(rover0, waypoint7)
end_variable
begin_variable
var25
-1
2
Atom calibrated(camera2, rover0)
NegatedAtom calibrated(camera2, rover0)
end_variable
begin_variable
var26
-1
2
Atom have_image(rover0, objective3, low_res)
NegatedAtom have_image(rover0, objective3, low_res)
end_variable
begin_variable
var27
-1
2
Atom communicated_image_data(objective3, low_res)
NegatedAtom communicated_image_data(objective3, low_res)
end_variable
begin_variable
var28
-1
2
Atom have_image(rover0, objective2, low_res)
NegatedAtom have_image(rover0, objective2, low_res)
end_variable
begin_variable
var29
-1
2
Atom communicated_image_data(objective2, low_res)
NegatedAtom communicated_image_data(objective2, low_res)
end_variable
0
begin_state
7
1
1
1
1
1
6
1
1
1
4
0
0
0
0
0
0
0
0
0
0
1
1
1
4
1
1
1
1
1
end_state
begin_goal
6
9 0
21 0
22 0
23 0
27 0
29 0
end_goal
259
begin_operator
calibrate rover0 camera2 objective0 waypoint0
1
24 0
1
0 25 -1 0
1
end_operator
begin_operator
calibrate rover0 camera2 objective0 waypoint1
1
24 1
1
0 25 -1 0
1
end_operator
begin_operator
calibrate rover0 camera2 objective0 waypoint2
1
24 2
1
0 25 -1 0
1
end_operator
begin_operator
calibrate rover2 camera1 objective1 waypoint0
1
6 0
1
0 7 -1 0
1
end_operator
begin_operator
calibrate rover2 camera1 objective1 waypoint1
1
6 1
1
0 7 -1 0
1
end_operator
begin_operator
calibrate rover2 camera1 objective1 waypoint2
1
6 2
1
0 7 -1 0
1
end_operator
begin_operator
calibrate rover2 camera1 objective1 waypoint3
1
6 3
1
0 7 -1 0
1
end_operator
begin_operator
calibrate rover3 camera0 objective2 waypoint0
1
0 0
1
0 4 -1 0
1
end_operator
begin_operator
calibrate rover3 camera0 objective2 waypoint1
1
0 1
1
0 4 -1 0
1
end_operator
begin_operator
calibrate rover3 camera0 objective2 waypoint2
1
0 2
1
0 4 -1 0
1
end_operator
begin_operator
calibrate rover3 camera0 objective2 waypoint3
1
0 3
1
0 4 -1 0
1
end_operator
begin_operator
calibrate rover3 camera0 objective2 waypoint4
1
0 4
1
0 4 -1 0
1
end_operator
begin_operator
calibrate rover3 camera3 objective3 waypoint0
1
0 0
1
0 1 -1 0
1
end_operator
begin_operator
calibrate rover3 camera3 objective3 waypoint1
1
0 1
1
0 1 -1 0
1
end_operator
begin_operator
calibrate rover3 camera3 objective3 waypoint2
1
0 2
1
0 1 -1 0
1
end_operator
begin_operator
calibrate rover3 camera3 objective3 waypoint3
1
0 3
1
0 1 -1 0
1
end_operator
begin_operator
calibrate rover3 camera3 objective3 waypoint4
1
0 4
1
0 1 -1 0
1
end_operator
begin_operator
calibrate rover3 camera3 objective3 waypoint5
1
0 5
1
0 1 -1 0
1
end_operator
begin_operator
communicate_image_data rover0 general objective2 low_res waypoint0 waypoint2
2
24 0
28 0
1
0 29 -1 0
1
end_operator
begin_operator
communicate_image_data rover0 general objective2 low_res waypoint3 waypoint2
2
24 3
28 0
1
0 29 -1 0
1
end_operator
begin_operator
communicate_image_data rover0 general objective2 low_res waypoint4 waypoint2
2
24 4
28 0
1
0 29 -1 0
1
end_operator
begin_operator
communicate_image_data rover0 general objective2 low_res waypoint5 waypoint2
2
24 5
28 0
1
0 29 -1 0
1
end_operator
begin_operator
communicate_image_data rover0 general objective2 low_res waypoint7 waypoint2
2
24 7
28 0
1
0 29 -1 0
1
end_operator
begin_operator
communicate_image_data rover0 general objective3 low_res waypoint0 waypoint2
2
24 0
26 0
1
0 27 -1 0
1
end_operator
begin_operator
communicate_image_data rover0 general objective3 low_res waypoint3 waypoint2
2
24 3
26 0
1
0 27 -1 0
1
end_operator
begin_operator
communicate_image_data rover0 general objective3 low_res waypoint4 waypoint2
2
24 4
26 0
1
0 27 -1 0
1
end_operator
begin_operator
communicate_image_data rover0 general objective3 low_res waypoint5 waypoint2
2
24 5
26 0
1
0 27 -1 0
1
end_operator
begin_operator
communicate_image_data rover0 general objective3 low_res waypoint7 waypoint2
2
24 7
26 0
1
0 27 -1 0
1
end_operator
begin_operator
communicate_image_data rover2 general objective1 high_res waypoint0 waypoint2
2
6 0
8 0
1
0 9 -1 0
1
end_operator
begin_operator
communicate_image_data rover2 general objective1 high_res waypoint3 waypoint2
2
6 3
8 0
1
0 9 -1 0
1
end_operator
begin_operator
communicate_image_data rover2 general objective1 high_res waypoint5 waypoint2
2
6 4
8 0
1
0 9 -1 0
1
end_operator
begin_operator
communicate_image_data rover2 general objective1 high_res waypoint7 waypoint2
2
6 6
8 0
1
0 9 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective1 high_res waypoint0 waypoint2
2
0 0
5 0
1
0 9 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective1 high_res waypoint3 waypoint2
2
0 3
5 0
1
0 9 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective1 high_res waypoint4 waypoint2
2
0 4
5 0
1
0 9 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective1 high_res waypoint5 waypoint2
2
0 5
5 0
1
0 9 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective1 high_res waypoint7 waypoint2
2
0 7
5 0
1
0 9 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective2 low_res waypoint0 waypoint2
2
0 0
3 0
1
0 29 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective2 low_res waypoint3 waypoint2
2
0 3
3 0
1
0 29 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective2 low_res waypoint4 waypoint2
2
0 4
3 0
1
0 29 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective2 low_res waypoint5 waypoint2
2
0 5
3 0
1
0 29 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective2 low_res waypoint7 waypoint2
2
0 7
3 0
1
0 29 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective3 low_res waypoint0 waypoint2
2
0 0
2 0
1
0 27 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective3 low_res waypoint3 waypoint2
2
0 3
2 0
1
0 27 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective3 low_res waypoint4 waypoint2
2
0 4
2 0
1
0 27 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective3 low_res waypoint5 waypoint2
2
0 5
2 0
1
0 27 -1 0
1
end_operator
begin_operator
communicate_image_data rover3 general objective3 low_res waypoint7 waypoint2
2
0 7
2 0
1
0 27 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint3 waypoint0 waypoint2
2
10 0
14 1
1
0 23 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint3 waypoint3 waypoint2
2
10 3
14 1
1
0 23 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint3 waypoint4 waypoint2
2
10 4
14 1
1
0 23 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint3 waypoint5 waypoint2
2
10 5
14 1
1
0 23 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint3 waypoint7 waypoint2
2
10 7
14 1
1
0 23 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint6 waypoint0 waypoint2
2
10 0
16 1
1
0 22 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint6 waypoint3 waypoint2
2
10 3
16 1
1
0 22 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint6 waypoint4 waypoint2
2
10 4
16 1
1
0 22 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint6 waypoint5 waypoint2
2
10 5
16 1
1
0 22 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint6 waypoint7 waypoint2
2
10 7
16 1
1
0 22 -1 0
1
end_operator
begin_operator
communicate_rock_data rover3 general waypoint3 waypoint0 waypoint2
2
0 0
14 2
1
0 23 -1 0
1
end_operator
begin_operator
communicate_rock_data rover3 general waypoint3 waypoint3 waypoint2
2
0 3
14 2
1
0 23 -1 0
1
end_operator
begin_operator
communicate_rock_data rover3 general waypoint3 waypoint4 waypoint2
2
0 4
14 2
1
0 23 -1 0
1
end_operator
begin_operator
communicate_rock_data rover3 general waypoint3 waypoint5 waypoint2
2
0 5
14 2
1
0 23 -1 0
1
end_operator
begin_operator
communicate_rock_data rover3 general waypoint3 waypoint7 waypoint2
2
0 7
14 2
1
0 23 -1 0
1
end_operator
begin_operator
communicate_rock_data rover3 general waypoint6 waypoint0 waypoint2
2
0 0
16 2
1
0 22 -1 0
1
end_operator
begin_operator
communicate_rock_data rover3 general waypoint6 waypoint3 waypoint2
2
0 3
16 2
1
0 22 -1 0
1
end_operator
begin_operator
communicate_rock_data rover3 general waypoint6 waypoint4 waypoint2
2
0 4
16 2
1
0 22 -1 0
1
end_operator
begin_operator
communicate_rock_data rover3 general waypoint6 waypoint5 waypoint2
2
0 5
16 2
1
0 22 -1 0
1
end_operator
begin_operator
communicate_rock_data rover3 general waypoint6 waypoint7 waypoint2
2
0 7
16 2
1
0 22 -1 0
1
end_operator
begin_operator
communicate_soil_data rover1 general waypoint0 waypoint0 waypoint2
2
10 0
20 1
1
0 21 -1 0
1
end_operator
begin_operator
communicate_soil_data rover1 general waypoint0 waypoint3 waypoint2
2
10 3
20 1
1
0 21 -1 0
1
end_operator
begin_operator
communicate_soil_data rover1 general waypoint0 waypoint4 waypoint2
2
10 4
20 1
1
0 21 -1 0
1
end_operator
begin_operator
communicate_soil_data rover1 general waypoint0 waypoint5 waypoint2
2
10 5
20 1
1
0 21 -1 0
1
end_operator
begin_operator
communicate_soil_data rover1 general waypoint0 waypoint7 waypoint2
2
10 7
20 1
1
0 21 -1 0
1
end_operator
begin_operator
communicate_soil_data rover2 general waypoint0 waypoint0 waypoint2
2
6 0
20 2
1
0 21 -1 0
1
end_operator
begin_operator
communicate_soil_data rover2 general waypoint0 waypoint3 waypoint2
2
6 3
20 2
1
0 21 -1 0
1
end_operator
begin_operator
communicate_soil_data rover2 general waypoint0 waypoint5 waypoint2
2
6 4
20 2
1
0 21 -1 0
1
end_operator
begin_operator
communicate_soil_data rover2 general waypoint0 waypoint7 waypoint2
2
6 6
20 2
1
0 21 -1 0
1
end_operator
begin_operator
communicate_soil_data rover3 general waypoint0 waypoint0 waypoint2
2
0 0
20 3
1
0 21 -1 0
1
end_operator
begin_operator
communicate_soil_data rover3 general waypoint0 waypoint3 waypoint2
2
0 3
20 3
1
0 21 -1 0
1
end_operator
begin_operator
communicate_soil_data rover3 general waypoint0 waypoint4 waypoint2
2
0 4
20 3
1
0 21 -1 0
1
end_operator
begin_operator
communicate_soil_data rover3 general waypoint0 waypoint5 waypoint2
2
0 5
20 3
1
0 21 -1 0
1
end_operator
begin_operator
communicate_soil_data rover3 general waypoint0 waypoint7 waypoint2
2
0 7
20 3
1
0 21 -1 0
1
end_operator
begin_operator
drop rover1 rover1store
0
1
0 18 1 0
1
end_operator
begin_operator
drop rover2 rover2store
0
1
0 11 1 0
1
end_operator
begin_operator
drop rover3 rover3store
0
1
0 19 1 0
1
end_operator
begin_operator
navigate rover0 waypoint0 waypoint5
0
1
0 24 0 5
1
end_operator
begin_operator
navigate rover0 waypoint1 waypoint5
0
1
0 24 1 5
1
end_operator
begin_operator
navigate rover0 waypoint2 waypoint3
0
1
0 24 2 3
1
end_operator
begin_operator
navigate rover0 waypoint2 waypoint4
0
1
0 24 2 4
1
end_operator
begin_operator
navigate rover0 waypoint2 waypoint7
0
1
0 24 2 7
1
end_operator
begin_operator
navigate rover0 waypoint3 waypoint2
0
1
0 24 3 2
1
end_operator
begin_operator
navigate rover0 waypoint4 waypoint2
0
1
0 24 4 2
1
end_operator
begin_operator
navigate rover0 waypoint4 waypoint5
0
1
0 24 4 5
1
end_operator
begin_operator
navigate rover0 waypoint5 waypoint0
0
1
0 24 5 0
1
end_operator
begin_operator
navigate rover0 waypoint5 waypoint1
0
1
0 24 5 1
1
end_operator
begin_operator
navigate rover0 waypoint5 waypoint4
0
1
0 24 5 4
1
end_operator
begin_operator
navigate rover0 waypoint5 waypoint6
0
1
0 24 5 6
1
end_operator
begin_operator
navigate rover0 waypoint6 waypoint5
0
1
0 24 6 5
1
end_operator
begin_operator
navigate rover0 waypoint7 waypoint2
0
1
0 24 7 2
1
end_operator
begin_operator
navigate rover1 waypoint0 waypoint2
0
1
0 10 0 2
1
end_operator
begin_operator
navigate rover1 waypoint1 waypoint5
0
1
0 10 1 5
1
end_operator
begin_operator
navigate rover1 waypoint2 waypoint0
0
1
0 10 2 0
1
end_operator
begin_operator
navigate rover1 waypoint2 waypoint3
0
1
0 10 2 3
1
end_operator
begin_operator
navigate rover1 waypoint2 waypoint4
0
1
0 10 2 4
1
end_operator
begin_operator
navigate rover1 waypoint2 waypoint7
0
1
0 10 2 7
1
end_operator
begin_operator
navigate rover1 waypoint3 waypoint2
0
1
0 10 3 2
1
end_operator
begin_operator
navigate rover1 waypoint4 waypoint2
0
1
0 10 4 2
1
end_operator
begin_operator
navigate rover1 waypoint4 waypoint5
0
1
0 10 4 5
1
end_operator
begin_operator
navigate rover1 waypoint4 waypoint6
0
1
0 10 4 6
1
end_operator
begin_operator
navigate rover1 waypoint5 waypoint1
0
1
0 10 5 1
1
end_operator
begin_operator
navigate rover1 waypoint5 waypoint4
0
1
0 10 5 4
1
end_operator
begin_operator
navigate rover1 waypoint6 waypoint4
0
1
0 10 6 4
1
end_operator
begin_operator
navigate rover1 waypoint7 waypoint2
0
1
0 10 7 2
1
end_operator
begin_operator
navigate rover2 waypoint0 waypoint7
0
1
0 6 0 6
1
end_operator
begin_operator
navigate rover2 waypoint1 waypoint7
0
1
0 6 1 6
1
end_operator
begin_operator
navigate rover2 waypoint2 waypoint7
0
1
0 6 2 6
1
end_operator
begin_operator
navigate rover2 waypoint3 waypoint7
0
1
0 6 3 6
1
end_operator
begin_operator
navigate rover2 waypoint5 waypoint7
0
1
0 6 4 6
1
end_operator
begin_operator
navigate rover2 waypoint6 waypoint7
0
1
0 6 5 6
1
end_operator
begin_operator
navigate rover2 waypoint7 waypoint0
0
1
0 6 6 0
1
end_operator
begin_operator
navigate rover2 waypoint7 waypoint1
0
1
0 6 6 1
1
end_operator
begin_operator
navigate rover2 waypoint7 waypoint2
0
1
0 6 6 2
1
end_operator
begin_operator
navigate rover2 waypoint7 waypoint3
0
1
0 6 6 3
1
end_operator
begin_operator
navigate rover2 waypoint7 waypoint5
0
1
0 6 6 4
1
end_operator
begin_operator
navigate rover2 waypoint7 waypoint6
0
1
0 6 6 5
1
end_operator
begin_operator
navigate rover3 waypoint0 waypoint6
0
1
0 0 0 6
1
end_operator
begin_operator
navigate rover3 waypoint0 waypoint7
0
1
0 0 0 7
1
end_operator
begin_operator
navigate rover3 waypoint1 waypoint7
0
1
0 0 1 7
1
end_operator
begin_operator
navigate rover3 waypoint2 waypoint7
0
1
0 0 2 7
1
end_operator
begin_operator
navigate rover3 waypoint3 waypoint7
0
1
0 0 3 7
1
end_operator
begin_operator
navigate rover3 waypoint4 waypoint7
0
1
0 0 4 7
1
end_operator
begin_operator
navigate rover3 waypoint5 waypoint7
0
1
0 0 5 7
1
end_operator
begin_operator
navigate rover3 waypoint6 waypoint0
0
1
0 0 6 0
1
end_operator
begin_operator
navigate rover3 waypoint7 waypoint0
0
1
0 0 7 0
1
end_operator
begin_operator
navigate rover3 waypoint7 waypoint1
0
1
0 0 7 1
1
end_operator
begin_operator
navigate rover3 waypoint7 waypoint2
0
1
0 0 7 2
1
end_operator
begin_operator
navigate rover3 waypoint7 waypoint3
0
1
0 0 7 3
1
end_operator
begin_operator
navigate rover3 waypoint7 waypoint4
0
1
0 0 7 4
1
end_operator
begin_operator
navigate rover3 waypoint7 waypoint5
0
1
0 0 7 5
1
end_operator
begin_operator
sample_rock rover1 rover1store waypoint0
1
10 0
2
0 12 0 1
0 18 0 1
1
end_operator
begin_operator
sample_rock rover1 rover1store waypoint2
1
10 2
2
0 13 0 1
0 18 0 1
1
end_operator
begin_operator
sample_rock rover1 rover1store waypoint3
1
10 3
2
0 14 0 1
0 18 0 1
1
end_operator
begin_operator
sample_rock rover1 rover1store waypoint5
1
10 5
2
0 15 0 1
0 18 0 1
1
end_operator
begin_operator
sample_rock rover1 rover1store waypoint6
1
10 6
2
0 16 0 1
0 18 0 1
1
end_operator
begin_operator
sample_rock rover1 rover1store waypoint7
1
10 7
2
0 17 0 1
0 18 0 1
1
end_operator
begin_operator
sample_rock rover3 rover3store waypoint0
1
0 0
2
0 12 0 2
0 19 0 1
1
end_operator
begin_operator
sample_rock rover3 rover3store waypoint2
1
0 2
2
0 13 0 2
0 19 0 1
1
end_operator
begin_operator
sample_rock rover3 rover3store waypoint3
1
0 3
2
0 14 0 2
0 19 0 1
1
end_operator
begin_operator
sample_rock rover3 rover3store waypoint5
1
0 5
2
0 15 0 2
0 19 0 1
1
end_operator
begin_operator
sample_rock rover3 rover3store waypoint6
1
0 6
2
0 16 0 2
0 19 0 1
1
end_operator
begin_operator
sample_rock rover3 rover3store waypoint7
1
0 7
2
0 17 0 2
0 19 0 1
1
end_operator
begin_operator
sample_soil rover1 rover1store waypoint0
1
10 0
2
0 20 0 1
0 18 0 1
1
end_operator
begin_operator
sample_soil rover2 rover2store waypoint0
1
6 0
2
0 20 0 2
0 11 0 1
1
end_operator
begin_operator
sample_soil rover3 rover3store waypoint0
1
0 0
2
0 20 0 3
0 19 0 1
1
end_operator
begin_operator
take_image rover0 waypoint0 objective0 camera2 low_res
1
24 0
1
0 25 0 1
1
end_operator
begin_operator
take_image rover0 waypoint0 objective1 camera2 low_res
1
24 0
1
0 25 0 1
1
end_operator
begin_operator
take_image rover0 waypoint0 objective2 camera2 low_res
1
24 0
2
0 25 0 1
0 28 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint0 objective3 camera2 low_res
1
24 0
2
0 25 0 1
0 26 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint1 objective0 camera2 low_res
1
24 1
1
0 25 0 1
1
end_operator
begin_operator
take_image rover0 waypoint1 objective1 camera2 low_res
1
24 1
1
0 25 0 1
1
end_operator
begin_operator
take_image rover0 waypoint1 objective2 camera2 low_res
1
24 1
2
0 25 0 1
0 28 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint1 objective3 camera2 low_res
1
24 1
2
0 25 0 1
0 26 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint2 objective0 camera2 low_res
1
24 2
1
0 25 0 1
1
end_operator
begin_operator
take_image rover0 waypoint2 objective1 camera2 low_res
1
24 2
1
0 25 0 1
1
end_operator
begin_operator
take_image rover0 waypoint2 objective2 camera2 low_res
1
24 2
2
0 25 0 1
0 28 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint2 objective3 camera2 low_res
1
24 2
2
0 25 0 1
0 26 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint3 objective1 camera2 low_res
1
24 3
1
0 25 0 1
1
end_operator
begin_operator
take_image rover0 waypoint3 objective2 camera2 low_res
1
24 3
2
0 25 0 1
0 28 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint3 objective3 camera2 low_res
1
24 3
2
0 25 0 1
0 26 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint4 objective2 camera2 low_res
1
24 4
2
0 25 0 1
0 28 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint4 objective3 camera2 low_res
1
24 4
2
0 25 0 1
0 26 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint5 objective3 camera2 low_res
1
24 5
2
0 25 0 1
0 26 -1 0
1
end_operator
begin_operator
take_image rover2 waypoint0 objective0 camera1 high_res
1
6 0
1
0 7 0 1
1
end_operator
begin_operator
take_image rover2 waypoint0 objective1 camera1 high_res
1
6 0
2
0 7 0 1
0 8 -1 0
1
end_operator
begin_operator
take_image rover2 waypoint0 objective2 camera1 high_res
1
6 0
1
0 7 0 1
1
end_operator
begin_operator
take_image rover2 waypoint0 objective3 camera1 high_res
1
6 0
1
0 7 0 1
1
end_operator
begin_operator
take_image rover2 waypoint1 objective0 camera1 high_res
1
6 1
1
0 7 0 1
1
end_operator
begin_operator
take_image rover2 waypoint1 objective1 camera1 high_res
1
6 1
2
0 7 0 1
0 8 -1 0
1
end_operator
begin_operator
take_image rover2 waypoint1 objective2 camera1 high_res
1
6 1
1
0 7 0 1
1
end_operator
begin_operator
take_image rover2 waypoint1 objective3 camera1 high_res
1
6 1
1
0 7 0 1
1
end_operator
begin_operator
take_image rover2 waypoint2 objective0 camera1 high_res
1
6 2
1
0 7 0 1
1
end_operator
begin_operator
take_image rover2 waypoint2 objective1 camera1 high_res
1
6 2
2
0 7 0 1
0 8 -1 0
1
end_operator
begin_operator
take_image rover2 waypoint2 objective2 camera1 high_res
1
6 2
1
0 7 0 1
1
end_operator
begin_operator
take_image rover2 waypoint2 objective3 camera1 high_res
1
6 2
1
0 7 0 1
1
end_operator
begin_operator
take_image rover2 waypoint3 objective1 camera1 high_res
1
6 3
2
0 7 0 1
0 8 -1 0
1
end_operator
begin_operator
take_image rover2 waypoint3 objective2 camera1 high_res
1
6 3
1
0 7 0 1
1
end_operator
begin_operator
take_image rover2 waypoint3 objective3 camera1 high_res
1
6 3
1
0 7 0 1
1
end_operator
begin_operator
take_image rover2 waypoint5 objective3 camera1 high_res
1
6 4
1
0 7 0 1
1
end_operator
begin_operator
take_image rover3 waypoint0 objective0 camera0 high_res
1
0 0
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint0 objective0 camera3 colour
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint0 objective0 camera3 high_res
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint0 objective0 camera3 low_res
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint0 objective1 camera0 high_res
1
0 0
2
0 4 0 1
0 5 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint0 objective1 camera3 colour
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint0 objective1 camera3 high_res
1
0 0
2
0 1 0 1
0 5 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint0 objective1 camera3 low_res
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint0 objective2 camera0 high_res
1
0 0
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint0 objective2 camera3 colour
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint0 objective2 camera3 high_res
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint0 objective2 camera3 low_res
1
0 0
2
0 1 0 1
0 3 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint0 objective3 camera0 high_res
1
0 0
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint0 objective3 camera3 colour
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint0 objective3 camera3 high_res
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint0 objective3 camera3 low_res
1
0 0
2
0 1 0 1
0 2 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint1 objective0 camera0 high_res
1
0 1
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint1 objective0 camera3 colour
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint1 objective0 camera3 high_res
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint1 objective0 camera3 low_res
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint1 objective1 camera0 high_res
1
0 1
2
0 4 0 1
0 5 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint1 objective1 camera3 colour
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint1 objective1 camera3 high_res
1
0 1
2
0 1 0 1
0 5 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint1 objective1 camera3 low_res
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint1 objective2 camera0 high_res
1
0 1
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint1 objective2 camera3 colour
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint1 objective2 camera3 high_res
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint1 objective2 camera3 low_res
1
0 1
2
0 1 0 1
0 3 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint1 objective3 camera0 high_res
1
0 1
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint1 objective3 camera3 colour
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint1 objective3 camera3 high_res
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint1 objective3 camera3 low_res
1
0 1
2
0 1 0 1
0 2 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint2 objective0 camera0 high_res
1
0 2
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint2 objective0 camera3 colour
1
0 2
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint2 objective0 camera3 high_res
1
0 2
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint2 objective0 camera3 low_res
1
0 2
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint2 objective1 camera0 high_res
1
0 2
2
0 4 0 1
0 5 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint2 objective1 camera3 colour
1
0 2
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint2 objective1 camera3 high_res
1
0 2
2
0 1 0 1
0 5 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint2 objective1 camera3 low_res
1
0 2
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint2 objective2 camera0 high_res
1
0 2
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint2 objective2 camera3 colour
1
0 2
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint2 objective2 camera3 high_res
1
0 2
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint2 objective2 camera3 low_res
1
0 2
2
0 1 0 1
0 3 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint2 objective3 camera0 high_res
1
0 2
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint2 objective3 camera3 colour
1
0 2
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint2 objective3 camera3 high_res
1
0 2
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint2 objective3 camera3 low_res
1
0 2
2
0 1 0 1
0 2 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint3 objective1 camera0 high_res
1
0 3
2
0 4 0 1
0 5 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint3 objective1 camera3 colour
1
0 3
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint3 objective1 camera3 high_res
1
0 3
2
0 1 0 1
0 5 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint3 objective1 camera3 low_res
1
0 3
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint3 objective2 camera0 high_res
1
0 3
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint3 objective2 camera3 colour
1
0 3
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint3 objective2 camera3 high_res
1
0 3
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint3 objective2 camera3 low_res
1
0 3
2
0 1 0 1
0 3 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint3 objective3 camera0 high_res
1
0 3
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint3 objective3 camera3 colour
1
0 3
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint3 objective3 camera3 high_res
1
0 3
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint3 objective3 camera3 low_res
1
0 3
2
0 1 0 1
0 2 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint4 objective2 camera0 high_res
1
0 4
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint4 objective2 camera3 colour
1
0 4
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint4 objective2 camera3 high_res
1
0 4
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint4 objective2 camera3 low_res
1
0 4
2
0 1 0 1
0 3 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint4 objective3 camera0 high_res
1
0 4
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint4 objective3 camera3 colour
1
0 4
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint4 objective3 camera3 high_res
1
0 4
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint4 objective3 camera3 low_res
1
0 4
2
0 1 0 1
0 2 -1 0
1
end_operator
begin_operator
take_image rover3 waypoint5 objective3 camera0 high_res
1
0 5
1
0 4 0 1
1
end_operator
begin_operator
take_image rover3 waypoint5 objective3 camera3 colour
1
0 5
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint5 objective3 camera3 high_res
1
0 5
1
0 1 0 1
1
end_operator
begin_operator
take_image rover3 waypoint5 objective3 camera3 low_res
1
0 5
2
0 1 0 1
0 2 -1 0
1
end_operator
0
