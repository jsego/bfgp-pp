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
Atom power_avail(satellite1)
NegatedAtom power_avail(satellite1)
end_variable
begin_variable
var1
-1
2
Atom power_on(instrument3)
NegatedAtom power_on(instrument3)
end_variable
begin_variable
var2
-1
2
Atom power_on(instrument0)
NegatedAtom power_on(instrument0)
end_variable
begin_variable
var3
-1
2
Atom power_on(instrument1)
NegatedAtom power_on(instrument1)
end_variable
begin_variable
var4
-1
2
Atom power_on(instrument2)
NegatedAtom power_on(instrument2)
end_variable
begin_variable
var5
-1
2
Atom power_avail(satellite0)
NegatedAtom power_avail(satellite0)
end_variable
begin_variable
var6
-1
8
Atom pointing(satellite1, phenomenon5)
Atom pointing(satellite1, phenomenon6)
Atom pointing(satellite1, phenomenon7)
Atom pointing(satellite1, star0)
Atom pointing(satellite1, star1)
Atom pointing(satellite1, star2)
Atom pointing(satellite1, star3)
Atom pointing(satellite1, star4)
end_variable
begin_variable
var7
-1
8
Atom pointing(satellite0, phenomenon5)
Atom pointing(satellite0, phenomenon6)
Atom pointing(satellite0, phenomenon7)
Atom pointing(satellite0, star0)
Atom pointing(satellite0, star1)
Atom pointing(satellite0, star2)
Atom pointing(satellite0, star3)
Atom pointing(satellite0, star4)
end_variable
begin_variable
var8
-1
2
Atom calibrated(instrument3)
NegatedAtom calibrated(instrument3)
end_variable
begin_variable
var9
-1
2
Atom calibrated(instrument2)
NegatedAtom calibrated(instrument2)
end_variable
begin_variable
var10
-1
2
Atom calibrated(instrument0)
NegatedAtom calibrated(instrument0)
end_variable
begin_variable
var11
-1
2
Atom have_image(star4, spectrograph2)
NegatedAtom have_image(star4, spectrograph2)
end_variable
begin_variable
var12
-1
2
Atom have_image(star3, infrared0)
NegatedAtom have_image(star3, infrared0)
end_variable
begin_variable
var13
-1
2
Atom have_image(phenomenon7, spectrograph2)
NegatedAtom have_image(phenomenon7, spectrograph2)
end_variable
begin_variable
var14
-1
2
Atom have_image(phenomenon5, spectrograph2)
NegatedAtom have_image(phenomenon5, spectrograph2)
end_variable
0
begin_state
0
1
1
1
1
0
3
7
1
1
1
1
1
1
1
end_state
begin_goal
5
7 0
11 0
12 0
13 0
14 0
end_goal
132
begin_operator
calibrate satellite0 instrument0 star1
2
7 4
2 0
1
0 10 -1 0
1
end_operator
begin_operator
calibrate satellite0 instrument2 star0
2
7 3
4 0
1
0 9 -1 0
1
end_operator
begin_operator
calibrate satellite1 instrument3 star0
2
6 3
1 0
1
0 8 -1 0
1
end_operator
begin_operator
switch_off instrument0 satellite0
0
2
0 5 -1 0
0 2 0 1
1
end_operator
begin_operator
switch_off instrument1 satellite0
0
2
0 5 -1 0
0 3 0 1
1
end_operator
begin_operator
switch_off instrument2 satellite0
0
2
0 5 -1 0
0 4 0 1
1
end_operator
begin_operator
switch_off instrument3 satellite1
0
2
0 0 -1 0
0 1 0 1
1
end_operator
begin_operator
switch_on instrument0 satellite0
0
3
0 10 -1 1
0 5 0 1
0 2 -1 0
1
end_operator
begin_operator
switch_on instrument1 satellite0
0
2
0 5 0 1
0 3 -1 0
1
end_operator
begin_operator
switch_on instrument2 satellite0
0
3
0 9 -1 1
0 5 0 1
0 4 -1 0
1
end_operator
begin_operator
switch_on instrument3 satellite1
0
3
0 8 -1 1
0 0 0 1
0 1 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon5 instrument0 spectrograph2
3
10 0
7 0
2 0
1
0 14 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon7 instrument0 spectrograph2
3
10 0
7 2
2 0
1
0 13 -1 0
1
end_operator
begin_operator
take_image satellite0 star3 instrument0 infrared0
3
10 0
7 6
2 0
1
0 12 -1 0
1
end_operator
begin_operator
take_image satellite0 star3 instrument2 infrared0
3
9 0
7 6
4 0
1
0 12 -1 0
1
end_operator
begin_operator
take_image satellite0 star4 instrument0 spectrograph2
3
10 0
7 7
2 0
1
0 11 -1 0
1
end_operator
begin_operator
take_image satellite1 phenomenon5 instrument3 spectrograph2
3
8 0
6 0
1 0
1
0 14 -1 0
1
end_operator
begin_operator
take_image satellite1 phenomenon7 instrument3 spectrograph2
3
8 0
6 2
1 0
1
0 13 -1 0
1
end_operator
begin_operator
take_image satellite1 star3 instrument3 infrared0
3
8 0
6 6
1 0
1
0 12 -1 0
1
end_operator
begin_operator
take_image satellite1 star4 instrument3 spectrograph2
3
8 0
6 7
1 0
1
0 11 -1 0
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 phenomenon6
0
1
0 7 1 0
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 phenomenon7
0
1
0 7 2 0
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 star0
0
1
0 7 3 0
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 star1
0
1
0 7 4 0
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 star2
0
1
0 7 5 0
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 star3
0
1
0 7 6 0
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 star4
0
1
0 7 7 0
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 phenomenon5
0
1
0 7 0 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 phenomenon7
0
1
0 7 2 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 star0
0
1
0 7 3 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 star1
0
1
0 7 4 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 star2
0
1
0 7 5 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 star3
0
1
0 7 6 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 star4
0
1
0 7 7 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon7 phenomenon5
0
1
0 7 0 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon7 phenomenon6
0
1
0 7 1 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon7 star0
0
1
0 7 3 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon7 star1
0
1
0 7 4 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon7 star2
0
1
0 7 5 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon7 star3
0
1
0 7 6 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon7 star4
0
1
0 7 7 2
1
end_operator
begin_operator
turn_to satellite0 star0 phenomenon5
0
1
0 7 0 3
1
end_operator
begin_operator
turn_to satellite0 star0 phenomenon6
0
1
0 7 1 3
1
end_operator
begin_operator
turn_to satellite0 star0 phenomenon7
0
1
0 7 2 3
1
end_operator
begin_operator
turn_to satellite0 star0 star1
0
1
0 7 4 3
1
end_operator
begin_operator
turn_to satellite0 star0 star2
0
1
0 7 5 3
1
end_operator
begin_operator
turn_to satellite0 star0 star3
0
1
0 7 6 3
1
end_operator
begin_operator
turn_to satellite0 star0 star4
0
1
0 7 7 3
1
end_operator
begin_operator
turn_to satellite0 star1 phenomenon5
0
1
0 7 0 4
1
end_operator
begin_operator
turn_to satellite0 star1 phenomenon6
0
1
0 7 1 4
1
end_operator
begin_operator
turn_to satellite0 star1 phenomenon7
0
1
0 7 2 4
1
end_operator
begin_operator
turn_to satellite0 star1 star0
0
1
0 7 3 4
1
end_operator
begin_operator
turn_to satellite0 star1 star2
0
1
0 7 5 4
1
end_operator
begin_operator
turn_to satellite0 star1 star3
0
1
0 7 6 4
1
end_operator
begin_operator
turn_to satellite0 star1 star4
0
1
0 7 7 4
1
end_operator
begin_operator
turn_to satellite0 star2 phenomenon5
0
1
0 7 0 5
1
end_operator
begin_operator
turn_to satellite0 star2 phenomenon6
0
1
0 7 1 5
1
end_operator
begin_operator
turn_to satellite0 star2 phenomenon7
0
1
0 7 2 5
1
end_operator
begin_operator
turn_to satellite0 star2 star0
0
1
0 7 3 5
1
end_operator
begin_operator
turn_to satellite0 star2 star1
0
1
0 7 4 5
1
end_operator
begin_operator
turn_to satellite0 star2 star3
0
1
0 7 6 5
1
end_operator
begin_operator
turn_to satellite0 star2 star4
0
1
0 7 7 5
1
end_operator
begin_operator
turn_to satellite0 star3 phenomenon5
0
1
0 7 0 6
1
end_operator
begin_operator
turn_to satellite0 star3 phenomenon6
0
1
0 7 1 6
1
end_operator
begin_operator
turn_to satellite0 star3 phenomenon7
0
1
0 7 2 6
1
end_operator
begin_operator
turn_to satellite0 star3 star0
0
1
0 7 3 6
1
end_operator
begin_operator
turn_to satellite0 star3 star1
0
1
0 7 4 6
1
end_operator
begin_operator
turn_to satellite0 star3 star2
0
1
0 7 5 6
1
end_operator
begin_operator
turn_to satellite0 star3 star4
0
1
0 7 7 6
1
end_operator
begin_operator
turn_to satellite0 star4 phenomenon5
0
1
0 7 0 7
1
end_operator
begin_operator
turn_to satellite0 star4 phenomenon6
0
1
0 7 1 7
1
end_operator
begin_operator
turn_to satellite0 star4 phenomenon7
0
1
0 7 2 7
1
end_operator
begin_operator
turn_to satellite0 star4 star0
0
1
0 7 3 7
1
end_operator
begin_operator
turn_to satellite0 star4 star1
0
1
0 7 4 7
1
end_operator
begin_operator
turn_to satellite0 star4 star2
0
1
0 7 5 7
1
end_operator
begin_operator
turn_to satellite0 star4 star3
0
1
0 7 6 7
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 phenomenon6
0
1
0 6 1 0
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 phenomenon7
0
1
0 6 2 0
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 star0
0
1
0 6 3 0
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 star1
0
1
0 6 4 0
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 star2
0
1
0 6 5 0
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 star3
0
1
0 6 6 0
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 star4
0
1
0 6 7 0
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 phenomenon5
0
1
0 6 0 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 phenomenon7
0
1
0 6 2 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 star0
0
1
0 6 3 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 star1
0
1
0 6 4 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 star2
0
1
0 6 5 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 star3
0
1
0 6 6 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 star4
0
1
0 6 7 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon7 phenomenon5
0
1
0 6 0 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon7 phenomenon6
0
1
0 6 1 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon7 star0
0
1
0 6 3 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon7 star1
0
1
0 6 4 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon7 star2
0
1
0 6 5 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon7 star3
0
1
0 6 6 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon7 star4
0
1
0 6 7 2
1
end_operator
begin_operator
turn_to satellite1 star0 phenomenon5
0
1
0 6 0 3
1
end_operator
begin_operator
turn_to satellite1 star0 phenomenon6
0
1
0 6 1 3
1
end_operator
begin_operator
turn_to satellite1 star0 phenomenon7
0
1
0 6 2 3
1
end_operator
begin_operator
turn_to satellite1 star0 star1
0
1
0 6 4 3
1
end_operator
begin_operator
turn_to satellite1 star0 star2
0
1
0 6 5 3
1
end_operator
begin_operator
turn_to satellite1 star0 star3
0
1
0 6 6 3
1
end_operator
begin_operator
turn_to satellite1 star0 star4
0
1
0 6 7 3
1
end_operator
begin_operator
turn_to satellite1 star1 phenomenon5
0
1
0 6 0 4
1
end_operator
begin_operator
turn_to satellite1 star1 phenomenon6
0
1
0 6 1 4
1
end_operator
begin_operator
turn_to satellite1 star1 phenomenon7
0
1
0 6 2 4
1
end_operator
begin_operator
turn_to satellite1 star1 star0
0
1
0 6 3 4
1
end_operator
begin_operator
turn_to satellite1 star1 star2
0
1
0 6 5 4
1
end_operator
begin_operator
turn_to satellite1 star1 star3
0
1
0 6 6 4
1
end_operator
begin_operator
turn_to satellite1 star1 star4
0
1
0 6 7 4
1
end_operator
begin_operator
turn_to satellite1 star2 phenomenon5
0
1
0 6 0 5
1
end_operator
begin_operator
turn_to satellite1 star2 phenomenon6
0
1
0 6 1 5
1
end_operator
begin_operator
turn_to satellite1 star2 phenomenon7
0
1
0 6 2 5
1
end_operator
begin_operator
turn_to satellite1 star2 star0
0
1
0 6 3 5
1
end_operator
begin_operator
turn_to satellite1 star2 star1
0
1
0 6 4 5
1
end_operator
begin_operator
turn_to satellite1 star2 star3
0
1
0 6 6 5
1
end_operator
begin_operator
turn_to satellite1 star2 star4
0
1
0 6 7 5
1
end_operator
begin_operator
turn_to satellite1 star3 phenomenon5
0
1
0 6 0 6
1
end_operator
begin_operator
turn_to satellite1 star3 phenomenon6
0
1
0 6 1 6
1
end_operator
begin_operator
turn_to satellite1 star3 phenomenon7
0
1
0 6 2 6
1
end_operator
begin_operator
turn_to satellite1 star3 star0
0
1
0 6 3 6
1
end_operator
begin_operator
turn_to satellite1 star3 star1
0
1
0 6 4 6
1
end_operator
begin_operator
turn_to satellite1 star3 star2
0
1
0 6 5 6
1
end_operator
begin_operator
turn_to satellite1 star3 star4
0
1
0 6 7 6
1
end_operator
begin_operator
turn_to satellite1 star4 phenomenon5
0
1
0 6 0 7
1
end_operator
begin_operator
turn_to satellite1 star4 phenomenon6
0
1
0 6 1 7
1
end_operator
begin_operator
turn_to satellite1 star4 phenomenon7
0
1
0 6 2 7
1
end_operator
begin_operator
turn_to satellite1 star4 star0
0
1
0 6 3 7
1
end_operator
begin_operator
turn_to satellite1 star4 star1
0
1
0 6 4 7
1
end_operator
begin_operator
turn_to satellite1 star4 star2
0
1
0 6 5 7
1
end_operator
begin_operator
turn_to satellite1 star4 star3
0
1
0 6 6 7
1
end_operator
0
