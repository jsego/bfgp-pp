begin_version
3
end_version
begin_metric
0
end_metric
13
begin_variable
var0
-1
4
Atom at(rover1, waypoint0)
Atom at(rover1, waypoint1)
Atom at(rover1, waypoint2)
Atom at(rover1, waypoint3)
end_variable
begin_variable
var1
-1
2
Atom calibrated(camera1, rover1)
NegatedAtom calibrated(camera1, rover1)
end_variable
begin_variable
var2
-1
2
Atom have_image(rover1, objective0, colour)
NegatedAtom have_image(rover1, objective0, colour)
end_variable
begin_variable
var3
-1
2
Atom communicated_image_data(objective0, colour)
NegatedAtom communicated_image_data(objective0, colour)
end_variable
begin_variable
var4
-1
3
Atom at(rover0, waypoint0)
Atom at(rover0, waypoint1)
Atom at(rover0, waypoint3)
end_variable
begin_variable
var5
-1
2
Atom at_rock_sample(waypoint2)
Atom have_rock_analysis(rover1, waypoint2)
end_variable
begin_variable
var6
-1
2
Atom at_soil_sample(waypoint2)
Atom have_soil_analysis(rover1, waypoint2)
end_variable
begin_variable
var7
-1
3
Atom at_rock_sample(waypoint0)
Atom have_rock_analysis(rover0, waypoint0)
Atom have_rock_analysis(rover1, waypoint0)
end_variable
begin_variable
var8
-1
2
Atom empty(rover0store)
Atom full(rover0store)
end_variable
begin_variable
var9
-1
2
Atom empty(rover1store)
Atom full(rover1store)
end_variable
begin_variable
var10
-1
3
Atom at_rock_sample(waypoint1)
Atom have_rock_analysis(rover0, waypoint1)
Atom have_rock_analysis(rover1, waypoint1)
end_variable
begin_variable
var11
-1
2
Atom communicated_soil_data(waypoint2)
NegatedAtom communicated_soil_data(waypoint2)
end_variable
begin_variable
var12
-1
2
Atom communicated_rock_data(waypoint0)
NegatedAtom communicated_rock_data(waypoint0)
end_variable
0
begin_state
3
1
1
1
1
0
0
0
0
0
0
1
1
end_state
begin_goal
3
3 0
11 0
12 0
end_goal
43
begin_operator
calibrate rover1 camera1 objective0 waypoint0
1
0 0
1
0 1 -1 0
1
end_operator
begin_operator
calibrate rover1 camera1 objective0 waypoint1
1
0 1
1
0 1 -1 0
1
end_operator
begin_operator
communicate_image_data rover1 general objective0 colour waypoint1 waypoint0
2
0 1
2 0
1
0 3 -1 0
1
end_operator
begin_operator
communicate_image_data rover1 general objective0 colour waypoint2 waypoint0
2
0 2
2 0
1
0 3 -1 0
1
end_operator
begin_operator
communicate_image_data rover1 general objective0 colour waypoint3 waypoint0
2
0 3
2 0
1
0 3 -1 0
1
end_operator
begin_operator
communicate_rock_data rover0 general waypoint0 waypoint1 waypoint0
2
4 1
7 1
1
0 12 -1 0
1
end_operator
begin_operator
communicate_rock_data rover0 general waypoint0 waypoint3 waypoint0
2
4 2
7 1
1
0 12 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint0 waypoint1 waypoint0
2
0 1
7 2
1
0 12 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint0 waypoint2 waypoint0
2
0 2
7 2
1
0 12 -1 0
1
end_operator
begin_operator
communicate_rock_data rover1 general waypoint0 waypoint3 waypoint0
2
0 3
7 2
1
0 12 -1 0
1
end_operator
begin_operator
communicate_soil_data rover1 general waypoint2 waypoint1 waypoint0
2
0 1
6 1
1
0 11 -1 0
1
end_operator
begin_operator
communicate_soil_data rover1 general waypoint2 waypoint2 waypoint0
2
0 2
6 1
1
0 11 -1 0
1
end_operator
begin_operator
communicate_soil_data rover1 general waypoint2 waypoint3 waypoint0
2
0 3
6 1
1
0 11 -1 0
1
end_operator
begin_operator
drop rover0 rover0store
0
1
0 8 1 0
1
end_operator
begin_operator
drop rover1 rover1store
0
1
0 9 1 0
1
end_operator
begin_operator
navigate rover0 waypoint0 waypoint1
0
1
0 4 0 1
1
end_operator
begin_operator
navigate rover0 waypoint1 waypoint0
0
1
0 4 1 0
1
end_operator
begin_operator
navigate rover0 waypoint1 waypoint3
0
1
0 4 1 2
1
end_operator
begin_operator
navigate rover0 waypoint3 waypoint1
0
1
0 4 2 1
1
end_operator
begin_operator
navigate rover1 waypoint0 waypoint1
0
1
0 0 0 1
1
end_operator
begin_operator
navigate rover1 waypoint0 waypoint3
0
1
0 0 0 3
1
end_operator
begin_operator
navigate rover1 waypoint1 waypoint0
0
1
0 0 1 0
1
end_operator
begin_operator
navigate rover1 waypoint2 waypoint3
0
1
0 0 2 3
1
end_operator
begin_operator
navigate rover1 waypoint3 waypoint0
0
1
0 0 3 0
1
end_operator
begin_operator
navigate rover1 waypoint3 waypoint2
0
1
0 0 3 2
1
end_operator
begin_operator
sample_rock rover0 rover0store waypoint0
1
4 0
2
0 7 0 1
0 8 0 1
1
end_operator
begin_operator
sample_rock rover0 rover0store waypoint1
1
4 1
2
0 10 0 1
0 8 0 1
1
end_operator
begin_operator
sample_rock rover1 rover1store waypoint0
1
0 0
2
0 7 0 2
0 9 0 1
1
end_operator
begin_operator
sample_rock rover1 rover1store waypoint1
1
0 1
2
0 10 0 2
0 9 0 1
1
end_operator
begin_operator
sample_rock rover1 rover1store waypoint2
1
0 2
2
0 5 0 1
0 9 0 1
1
end_operator
begin_operator
sample_soil rover1 rover1store waypoint2
1
0 2
2
0 6 0 1
0 9 0 1
1
end_operator
begin_operator
take_image rover1 waypoint0 objective0 camera1 colour
1
0 0
2
0 1 0 1
0 2 -1 0
1
end_operator
begin_operator
take_image rover1 waypoint0 objective0 camera1 high_res
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover1 waypoint0 objective0 camera1 low_res
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover1 waypoint0 objective1 camera1 colour
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover1 waypoint0 objective1 camera1 high_res
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover1 waypoint0 objective1 camera1 low_res
1
0 0
1
0 1 0 1
1
end_operator
begin_operator
take_image rover1 waypoint1 objective0 camera1 colour
1
0 1
2
0 1 0 1
0 2 -1 0
1
end_operator
begin_operator
take_image rover1 waypoint1 objective0 camera1 high_res
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover1 waypoint1 objective0 camera1 low_res
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover1 waypoint1 objective1 camera1 colour
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover1 waypoint1 objective1 camera1 high_res
1
0 1
1
0 1 0 1
1
end_operator
begin_operator
take_image rover1 waypoint1 objective1 camera1 low_res
1
0 1
1
0 1 0 1
1
end_operator
0
