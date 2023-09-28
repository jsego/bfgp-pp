begin_version
3
end_version
begin_metric
0
end_metric
22
begin_variable
var0
-1
6
Atom at(rover2, waypoint0)
Atom at(rover2, waypoint1)
Atom at(rover2, waypoint2)
Atom at(rover2, waypoint3)
Atom at(rover2, waypoint4)
Atom at(rover2, waypoint5)
end_variable
begin_variable
var1
-1
2
Atom calibrated(camera1, rover2)
NegatedAtom calibrated(camera1, rover2)
end_variable
begin_variable
var2
-1
2
Atom have_image(rover2, objective0, high_res)
NegatedAtom have_image(rover2, objective0, high_res)
end_variable
begin_variable
var3
-1
6
Atom at(rover1, waypoint0)
Atom at(rover1, waypoint1)
Atom at(rover1, waypoint2)
Atom at(rover1, waypoint3)
Atom at(rover1, waypoint4)
Atom at(rover1, waypoint5)
end_variable
begin_variable
var4
-1
6
Atom at(rover0, waypoint0)
Atom at(rover0, waypoint1)
Atom at(rover0, waypoint2)
Atom at(rover0, waypoint3)
Atom at(rover0, waypoint4)
Atom at(rover0, waypoint5)
end_variable
begin_variable
var5
-1
2
Atom calibrated(camera0, rover0)
NegatedAtom calibrated(camera0, rover0)
end_variable
begin_variable
var6
-1
2
Atom have_image(rover0, objective0, high_res)
NegatedAtom have_image(rover0, objective0, high_res)
end_variable
begin_variable
var7
-1
2
Atom communicated_image_data(objective0, high_res)
NegatedAtom communicated_image_data(objective0, high_res)
end_variable
begin_variable
var8
-1
3
Atom at_soil_sample(waypoint1)
Atom have_soil_analysis(rover0, waypoint1)
Atom have_soil_analysis(rover2, waypoint1)
end_variable
begin_variable
var9
-1
3
Atom at_soil_sample(waypoint4)
Atom have_soil_analysis(rover0, waypoint4)
Atom have_soil_analysis(rover2, waypoint4)
end_variable
begin_variable
var10
-1
4
Atom at_rock_sample(waypoint2)
Atom have_rock_analysis(rover0, waypoint2)
Atom have_rock_analysis(rover1, waypoint2)
Atom have_rock_analysis(rover2, waypoint2)
end_variable
begin_variable
var11
-1
4
Atom at_rock_sample(waypoint3)
Atom have_rock_analysis(rover0, waypoint3)
Atom have_rock_analysis(rover1, waypoint3)
Atom have_rock_analysis(rover2, waypoint3)
end_variable
begin_variable
var12
-1
2
Atom empty(rover0store)
Atom full(rover0store)
end_variable
begin_variable
var13
-1
2
Atom empty(rover1store)
Atom full(rover1store)
end_variable
begin_variable
var14
-1
4
Atom at_rock_sample(waypoint4)
Atom have_rock_analysis(rover0, waypoint4)
Atom have_rock_analysis(rover1, waypoint4)
Atom have_rock_analysis(rover2, waypoint4)
end_variable
begin_variable
var15
-1
4
Atom at_rock_sample(waypoint5)
Atom have_rock_analysis(rover0, waypoint5)
Atom have_rock_analysis(rover1, waypoint5)
Atom have_rock_analysis(rover2, waypoint5)
end_variable
begin_variable
var16
-1
2
Atom empty(rover2store)
Atom full(rover2store)
end_variable
begin_variable
var17
-1
2
Atom communicated_soil_data(waypoint4)
NegatedAtom communicated_soil_data(waypoint4)
end_variable
begin_variable
var18
-1
2
Atom communicated_soil_data(waypoint1)
NegatedAtom communicated_soil_data(waypoint1)
end_variable
begin_variable
var19
-1
2
Atom communicated_rock_data(waypoint4)
NegatedAtom communicated_rock_data(waypoint4)
end_variable
begin_variable
var20
-1
2
Atom communicated_rock_data(waypoint3)
NegatedAtom communicated_rock_data(waypoint3)
end_variable
begin_variable
var21
-1
2
Atom communicated_rock_data(waypoint2)
NegatedAtom communicated_rock_data(waypoint2)
end_variable
0
begin_state
4
1
1
3
2
1
1
1
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
1
1
end_state
begin_goal
6
7 0
17 0
18 0
19 0
20 0
21 0
end_goal
130
begin_operator
calibrate rover0 camera0 objective0 waypoint0
1
4 0
1
0 5 -1 0
1
end_operator
begin_operator
calibrate rover0 camera0 objective0 waypoint1
1
4 1
1
0 5 -1 0
1
end_operator
begin_operator
calibrate rover0 camera0 objective0 waypoint2
1
4 2
1
0 5 -1 0
1
end_operator
begin_operator
calibrate rover0 camera0 objective0 waypoint3
1
4 3
1
0 5 -1 0
1
end_operator
begin_operator
calibrate rover0 camera0 objective0 waypoint4
1
4 4
1
0 5 -1 0
1
end_operator
begin_operator
calibrate rover2 camera1 objective1 waypoint0
1
0 0
1
0 1 -1 0
1
end_operator
begin_operator
calibrate rover2 camera1 objective1 waypoint1
1
0 1
1
0 1 -1 0
1
end_operator
begin_operator
calibrate rover2 camera1 objective1 waypoint2
1
0 2
1
0 1 -1 0
1
end_operator
begin_operator
calibrate rover2 camera1 objective1 waypoint3
1
0 3
1
0 1 -1 0
1
end_operator
begin_operator
communicate_image_data rover0 general objective0 high_res waypoint0 waypoint3
2
4 0
6 0
1
0 7 -1 0
1
end_operator
begin_operator
communicate_image_data rover0 general objective0 high_res waypoint2 waypoint3
2
4 2
6 0
1
0 7 -1 0
1
end_operator
begin_operator
communicate_image_data rover0 general objective0 high_res waypoint4 waypoint3
2
4 4
6 0
1
0 7 -1 0
1
end_operator
begin_operator
communicate_image_data rover2 general objective0 high_res waypoint0 waypoint3
2
0 0
2 0
1
0 7 -1 0
1
end_operator
begin_operator
communicate_image_data rover2 general objective0 high_res waypoint2 waypoint3
2
0 2
2 0
1
0 7 -1 0
1
end_operator
begin_operator
communicate_image_data rover2 general objective0 high_res waypoint4 waypoint3
2
0 4
2 0
1
0 7 -1 0
1
end_operator
begin_operator
communicate_rock_data rover0 general waypoint2 waypoint0 waypoint3
2
4 0
10 1
1
0 21 -1 0
1
end_operator
begin_operator
communicate_rock_data rover0 general waypoint2 waypoint2 waypoint3
2
4 2
10 1
1
0 21 -1 0
1
end_operator
begin_operator
communicate_rock_data rover0 general waypoint2 waypoint4 waypoint3
2
4 4
10 1
1
0 21 -1 0
1
end_operator
begin_operator
communicate_rock_data rover0 general waypoint3 waypoint0 waypoint3
2
4 0
11 1
1
0 20 -1 0
1
end_operator
begin_operator
communicate_rock_data rover0 general waypoint3 waypoint2 waypoint3
2
4 2
11 1
1
0 20 -1 0
1
end_operator
begin_operator
communicate_rock_data rover0 general waypoint3 waypoint4 waypoint3
2
4 4
11 1
1
0 20 -1 0
1
end_operator
begin_operator
communicate_rock_data rover0 general waypoint4 waypoint0 waypoint3
2
4 0
14 1
1
0 19 -1 0
1
end_operator
begin_operator
communicate_rock_data rover0 general waypoint4 waypoint2 waypoint3
2
4 2
14 1
1
0 19 -1 0
1
end_operator
begin_operator
communicate_rock_data rover0 general waypoint4 waypoint4 waypoint3
2
4 4
14 1
1
0 19 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint2 waypoint0 waypoint3
2
3 0
10 2
1
0 21 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint2 waypoint2 waypoint3
2
3 2
10 2
1
0 21 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint2 waypoint4 waypoint3
2
3 4
10 2
1
0 21 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint3 waypoint0 waypoint3
2
3 0
11 2
1
0 20 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint3 waypoint2 waypoint3
2
3 2
11 2
1
0 20 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint3 waypoint4 waypoint3
2
3 4
11 2
1
0 20 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint4 waypoint0 waypoint3
2
3 0
14 2
1
0 19 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint4 waypoint2 waypoint3
2
3 2
14 2
1
0 19 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint4 waypoint4 waypoint3
2
3 4
14 2
1
0 19 -1 0
1
end_operator
begin_operator
communicate_rock_data rover2 general waypoint2 waypoint0 waypoint3
2
0 0
10 3
1
0 21 -1 0
1
end_operator
begin_operator
communicate_rock_data rover2 general waypoint2 waypoint2 waypoint3
2
0 2
10 3
1
0 21 -1 0
1
end_operator
begin_operator
communicate_rock_data rover2 general waypoint2 waypoint4 waypoint3
2
0 4
10 3
1
0 21 -1 0
1
end_operator
begin_operator
communicate_rock_data rover2 general waypoint3 waypoint0 waypoint3
2
0 0
11 3
1
0 20 -1 0
1
end_operator
begin_operator
communicate_rock_data rover2 general waypoint3 waypoint2 waypoint3
2
0 2
11 3
1
0 20 -1 0
1
end_operator
begin_operator
communicate_rock_data rover2 general waypoint3 waypoint4 waypoint3
2
0 4
11 3
1
0 20 -1 0
1
end_operator
begin_operator
communicate_rock_data rover2 general waypoint4 waypoint0 waypoint3
2
0 0
14 3
1
0 19 -1 0
1
end_operator
begin_operator
communicate_rock_data rover2 general waypoint4 waypoint2 waypoint3
2
0 2
14 3
1
0 19 -1 0
1
end_operator
begin_operator
communicate_rock_data rover2 general waypoint4 waypoint4 waypoint3
2
0 4
14 3
1
0 19 -1 0
1
end_operator
begin_operator
communicate_soil_data rover0 general waypoint1 waypoint0 waypoint3
2
4 0
8 1
1
0 18 -1 0
1
end_operator
begin_operator
communicate_soil_data rover0 general waypoint1 waypoint2 waypoint3
2
4 2
8 1
1
0 18 -1 0
1
end_operator
begin_operator
communicate_soil_data rover0 general waypoint1 waypoint4 waypoint3
2
4 4
8 1
1
0 18 -1 0
1
end_operator
begin_operator
communicate_soil_data rover0 general waypoint4 waypoint0 waypoint3
2
4 0
9 1
1
0 17 -1 0
1
end_operator
begin_operator
communicate_soil_data rover0 general waypoint4 waypoint2 waypoint3
2
4 2
9 1
1
0 17 -1 0
1
end_operator
begin_operator
communicate_soil_data rover0 general waypoint4 waypoint4 waypoint3
2
4 4
9 1
1
0 17 -1 0
1
end_operator
begin_operator
communicate_soil_data rover2 general waypoint1 waypoint0 waypoint3
2
0 0
8 2
1
0 18 -1 0
1
end_operator
begin_operator
communicate_soil_data rover2 general waypoint1 waypoint2 waypoint3
2
0 2
8 2
1
0 18 -1 0
1
end_operator
begin_operator
communicate_soil_data rover2 general waypoint1 waypoint4 waypoint3
2
0 4
8 2
1
0 18 -1 0
1
end_operator
begin_operator
communicate_soil_data rover2 general waypoint4 waypoint0 waypoint3
2
0 0
9 2
1
0 17 -1 0
1
end_operator
begin_operator
communicate_soil_data rover2 general waypoint4 waypoint2 waypoint3
2
0 2
9 2
1
0 17 -1 0
1
end_operator
begin_operator
communicate_soil_data rover2 general waypoint4 waypoint4 waypoint3
2
0 4
9 2
1
0 17 -1 0
1
end_operator
begin_operator
drop rover0 rover0store
0
1
0 12 1 0
1
end_operator
begin_operator
drop rover1 rover1store
0
1
0 13 1 0
1
end_operator
begin_operator
drop rover2 rover2store
0
1
0 16 1 0
1
end_operator
begin_operator
navigate rover0 waypoint0 waypoint2
0
1
0 4 0 2
1
end_operator
begin_operator
navigate rover0 waypoint0 waypoint4
0
1
0 4 0 4
1
end_operator
begin_operator
navigate rover0 waypoint1 waypoint2
0
1
0 4 1 2
1
end_operator
begin_operator
navigate rover0 waypoint2 waypoint0
0
1
0 4 2 0
1
end_operator
begin_operator
navigate rover0 waypoint2 waypoint1
0
1
0 4 2 1
1
end_operator
begin_operator
navigate rover0 waypoint2 waypoint3
0
1
0 4 2 3
1
end_operator
begin_operator
navigate rover0 waypoint2 waypoint5
0
1
0 4 2 5
1
end_operator
begin_operator
navigate rover0 waypoint3 waypoint2
0
1
0 4 3 2
1
end_operator
begin_operator
navigate rover0 waypoint4 waypoint0
0
1
0 4 4 0
1
end_operator
begin_operator
navigate rover0 waypoint5 waypoint2
0
1
0 4 5 2
1
end_operator
begin_operator
navigate rover1 waypoint0 waypoint1
0
1
0 3 0 1
1
end_operator
begin_operator
navigate rover1 waypoint0 waypoint3
0
1
0 3 0 3
1
end_operator
begin_operator
navigate rover1 waypoint0 waypoint5
0
1
0 3 0 5
1
end_operator
begin_operator
navigate rover1 waypoint1 waypoint0
0
1
0 3 1 0
1
end_operator
begin_operator
navigate rover1 waypoint2 waypoint3
0
1
0 3 2 3
1
end_operator
begin_operator
navigate rover1 waypoint3 waypoint0
0
1
0 3 3 0
1
end_operator
begin_operator
navigate rover1 waypoint3 waypoint2
0
1
0 3 3 2
1
end_operator
begin_operator
navigate rover1 waypoint3 waypoint4
0
1
0 3 3 4
1
end_operator
begin_operator
navigate rover1 waypoint4 waypoint3
0
1
0 3 4 3
1
end_operator
begin_operator
navigate rover1 waypoint5 waypoint0
0
1
0 3 5 0
1
end_operator
begin_operator
navigate rover2 waypoint0 waypoint1
0
1
0 0 0 1
1
end_operator
begin_operator
navigate rover2 waypoint0 waypoint3
0
1
0 0 0 3
1
end_operator
begin_operator
navigate rover2 waypoint0 waypoint4
0
1
0 0 0 4
1
end_operator
begin_operator
navigate rover2 waypoint1 waypoint0
0
1
0 0 1 0
1
end_operator
begin_operator
navigate rover2 waypoint2 waypoint5
0
1
0 0 2 5
1
end_operator
begin_operator
navigate rover2 waypoint3 waypoint0
0
1
0 0 3 0
1
end_operator
begin_operator
navigate rover2 waypoint4 waypoint0
0
1
0 0 4 0
1
end_operator
begin_operator
navigate rover2 waypoint4 waypoint5
0
1
0 0 4 5
1
end_operator
begin_operator
navigate rover2 waypoint5 waypoint2
0
1
0 0 5 2
1
end_operator
begin_operator
navigate rover2 waypoint5 waypoint4
0
1
0 0 5 4
1
end_operator
begin_operator
sample_rock rover0 rover0store waypoint2
1
4 2
2
0 10 0 1
0 12 0 1
1
end_operator
begin_operator
sample_rock rover0 rover0store waypoint3
1
4 3
2
0 11 0 1
0 12 0 1
1
end_operator
begin_operator
sample_rock rover0 rover0store waypoint4
1
4 4
2
0 14 0 1
0 12 0 1
1
end_operator
begin_operator
sample_rock rover0 rover0store waypoint5
1
4 5
2
0 15 0 1
0 12 0 1
1
end_operator
begin_operator
sample_rock rover1 rover1store waypoint2
1
3 2
2
0 10 0 2
0 13 0 1
1
end_operator
begin_operator
sample_rock rover1 rover1store waypoint3
1
3 3
2
0 11 0 2
0 13 0 1
1
end_operator
begin_operator
sample_rock rover1 rover1store waypoint4
1
3 4
2
0 14 0 2
0 13 0 1
1
end_operator
begin_operator
sample_rock rover1 rover1store waypoint5
1
3 5
2
0 15 0 2
0 13 0 1
1
end_operator
begin_operator
sample_rock rover2 rover2store waypoint2
1
0 2
2
0 10 0 3
0 16 0 1
1
end_operator
begin_operator
sample_rock rover2 rover2store waypoint3
1
0 3
2
0 11 0 3
0 16 0 1
1
end_operator
begin_operator
sample_rock rover2 rover2store waypoint4
1
0 4
2
0 14 0 3
0 16 0 1
1
end_operator
begin_operator
sample_rock rover2 rover2store waypoint5
1
0 5
2
0 15 0 3
0 16 0 1
1
end_operator
begin_operator
sample_soil rover0 rover0store waypoint1
1
4 1
2
0 8 0 1
0 12 0 1
1
end_operator
begin_operator
sample_soil rover0 rover0store waypoint4
1
4 4
2
0 9 0 1
0 12 0 1
1
end_operator
begin_operator
sample_soil rover2 rover2store waypoint1
1
0 1
2
0 8 0 2
0 16 0 1
1
end_operator
begin_operator
sample_soil rover2 rover2store waypoint4
1
0 4
2
0 9 0 2
0 16 0 1
1
end_operator
begin_operator
take_image rover0 waypoint0 objective0 camera0 colour
1
4 0
1
0 5 0 1
1
end_operator
begin_operator
take_image rover0 waypoint0 objective0 camera0 high_res
1
4 0
2
0 5 0 1
0 6 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint0 objective1 camera0 colour
1
4 0
1
0 5 0 1
1
end_operator
begin_operator
take_image rover0 waypoint0 objective1 camera0 high_res
1
4 0
1
0 5 0 1
1
end_operator
begin_operator
take_image rover0 waypoint1 objective0 camera0 colour
1
4 1
1
0 5 0 1
1
end_operator
begin_operator
take_image rover0 waypoint1 objective0 camera0 high_res
1
4 1
2
0 5 0 1
0 6 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint1 objective1 camera0 colour
1
4 1
1
0 5 0 1
1
end_operator
begin_operator
take_image rover0 waypoint1 objective1 camera0 high_res
1
4 1
1
0 5 0 1
1
end_operator
begin_operator
take_image rover0 waypoint2 objective0 camera0 colour
1
4 2
1
0 5 0 1
1
end_operator
begin_operator
take_image rover0 waypoint2 objective0 camera0 high_res
1
4 2
2
0 5 0 1
0 6 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint2 objective1 camera0 colour
1
4 2
1
0 5 0 1
1
end_operator
begin_operator
take_image rover0 waypoint2 objective1 camera0 high_res
1
4 2
1
0 5 0 1
1
end_operator
begin_operator
take_image rover0 waypoint3 objective0 camera0 colour
1
4 3
1
0 5 0 1
1
end_operator
begin_operator
take_image rover0 waypoint3 objective0 camera0 high_res
1
4 3
2
0 5 0 1
0 6 -1 0
1
end_operator
begin_operator
take_image rover0 waypoint3 objective1 camera0 colour
1
4 3
1
0 5 0 1
1
end_operator
begin_operator
take_image rover0 waypoint3 objective1 camera0 high_res
1
4 3
1
0 5 0 1
1
end_operator
begin_operator
take_image rover0 waypoint4 objective0 camera0 colour
1
4 4
1
0 5 0 1
1
end_operator
begin_operator
take_image rover0 waypoint4 objective0 camera0 high_res
1
4 4
2
0 5 0 1
0 6 -1 0
1
end_operator
begin_operator
take_image rover2 waypoint0 objective0 camera1 high_res
1
0 0
2
0 1 0 1
0 2 -1 0
1
end_operator
begin_operator
take_image rover2 waypoint0 objective1 camera1 high_res
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover2 waypoint1 objective0 camera1 high_res
1
0 1
2
0 1 0 1
0 2 -1 0
1
end_operator
begin_operator
take_image rover2 waypoint1 objective1 camera1 high_res
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover2 waypoint2 objective0 camera1 high_res
1
0 2
2
0 1 0 1
0 2 -1 0
1
end_operator
begin_operator
take_image rover2 waypoint2 objective1 camera1 high_res
1
0 2
1
0 1 0 1
1
end_operator
begin_operator
take_image rover2 waypoint3 objective0 camera1 high_res
1
0 3
2
0 1 0 1
0 2 -1 0
1
end_operator
begin_operator
take_image rover2 waypoint3 objective1 camera1 high_res
1
0 3
1
0 1 0 1
1
end_operator
begin_operator
take_image rover2 waypoint4 objective0 camera1 high_res
1
0 4
2
0 1 0 1
0 2 -1 0
1
end_operator
0
