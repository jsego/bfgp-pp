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
Atom power_avail(satellite0)
Atom power_on(instrument0)
Atom power_on(instrument1)
end_variable
begin_variable
var1
-1
8
Atom pointing(satellite0, groundstation1)
Atom pointing(satellite0, groundstation2)
Atom pointing(satellite0, phenomenon5)
Atom pointing(satellite0, phenomenon6)
Atom pointing(satellite0, planet3)
Atom pointing(satellite0, planet4)
Atom pointing(satellite0, star0)
Atom pointing(satellite0, star7)
end_variable
begin_variable
var2
-1
2
Atom calibrated(instrument1)
NegatedAtom calibrated(instrument1)
end_variable
begin_variable
var3
-1
2
Atom have_image(phenomenon5, image2)
NegatedAtom have_image(phenomenon5, image2)
end_variable
begin_variable
var4
-1
2
Atom calibrated(instrument0)
NegatedAtom calibrated(instrument0)
end_variable
begin_variable
var5
-1
2
Atom have_image(star7, infrared0)
NegatedAtom have_image(star7, infrared0)
end_variable
begin_variable
var6
-1
2
Atom have_image(planet4, infrared0)
NegatedAtom have_image(planet4, infrared0)
end_variable
begin_variable
var7
-1
2
Atom have_image(planet3, infrared0)
NegatedAtom have_image(planet3, infrared0)
end_variable
begin_variable
var8
-1
2
Atom have_image(phenomenon6, infrared0)
NegatedAtom have_image(phenomenon6, infrared0)
end_variable
0
begin_state
0
5
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
3 0
5 0
6 0
7 0
8 0
end_goal
71
begin_operator
calibrate satellite0 instrument0 star0
2
1 6
0 1
1
0 4 -1 0
1
end_operator
begin_operator
calibrate satellite0 instrument1 groundstation2
2
1 1
0 2
1
0 2 -1 0
1
end_operator
begin_operator
switch_off instrument0 satellite0
0
1
0 0 1 0
1
end_operator
begin_operator
switch_off instrument1 satellite0
0
1
0 0 2 0
1
end_operator
begin_operator
switch_on instrument0 satellite0
0
2
0 4 -1 1
0 0 0 1
1
end_operator
begin_operator
switch_on instrument1 satellite0
0
2
0 2 -1 1
0 0 0 2
1
end_operator
begin_operator
take_image satellite0 phenomenon5 instrument1 image2
3
2 0
1 2
0 2
1
0 3 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon6 instrument0 infrared0
3
4 0
1 3
0 1
1
0 8 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon6 instrument1 infrared0
3
2 0
1 3
0 2
1
0 8 -1 0
1
end_operator
begin_operator
take_image satellite0 planet3 instrument0 infrared0
3
4 0
1 4
0 1
1
0 7 -1 0
1
end_operator
begin_operator
take_image satellite0 planet3 instrument1 infrared0
3
2 0
1 4
0 2
1
0 7 -1 0
1
end_operator
begin_operator
take_image satellite0 planet4 instrument0 infrared0
3
4 0
1 5
0 1
1
0 6 -1 0
1
end_operator
begin_operator
take_image satellite0 planet4 instrument1 infrared0
3
2 0
1 5
0 2
1
0 6 -1 0
1
end_operator
begin_operator
take_image satellite0 star7 instrument0 infrared0
3
4 0
1 7
0 1
1
0 5 -1 0
1
end_operator
begin_operator
take_image satellite0 star7 instrument1 infrared0
3
2 0
1 7
0 2
1
0 5 -1 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 groundstation2
0
1
0 1 1 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 phenomenon5
0
1
0 1 2 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 phenomenon6
0
1
0 1 3 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 planet3
0
1
0 1 4 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 planet4
0
1
0 1 5 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 star0
0
1
0 1 6 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 star7
0
1
0 1 7 0
1
end_operator
begin_operator
turn_to satellite0 groundstation2 groundstation1
0
1
0 1 0 1
1
end_operator
begin_operator
turn_to satellite0 groundstation2 phenomenon5
0
1
0 1 2 1
1
end_operator
begin_operator
turn_to satellite0 groundstation2 phenomenon6
0
1
0 1 3 1
1
end_operator
begin_operator
turn_to satellite0 groundstation2 planet3
0
1
0 1 4 1
1
end_operator
begin_operator
turn_to satellite0 groundstation2 planet4
0
1
0 1 5 1
1
end_operator
begin_operator
turn_to satellite0 groundstation2 star0
0
1
0 1 6 1
1
end_operator
begin_operator
turn_to satellite0 groundstation2 star7
0
1
0 1 7 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 groundstation1
0
1
0 1 0 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 groundstation2
0
1
0 1 1 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 phenomenon6
0
1
0 1 3 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 planet3
0
1
0 1 4 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 planet4
0
1
0 1 5 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 star0
0
1
0 1 6 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 star7
0
1
0 1 7 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 groundstation1
0
1
0 1 0 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 groundstation2
0
1
0 1 1 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 phenomenon5
0
1
0 1 2 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 planet3
0
1
0 1 4 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 planet4
0
1
0 1 5 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 star0
0
1
0 1 6 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 star7
0
1
0 1 7 3
1
end_operator
begin_operator
turn_to satellite0 planet3 groundstation1
0
1
0 1 0 4
1
end_operator
begin_operator
turn_to satellite0 planet3 groundstation2
0
1
0 1 1 4
1
end_operator
begin_operator
turn_to satellite0 planet3 phenomenon5
0
1
0 1 2 4
1
end_operator
begin_operator
turn_to satellite0 planet3 phenomenon6
0
1
0 1 3 4
1
end_operator
begin_operator
turn_to satellite0 planet3 planet4
0
1
0 1 5 4
1
end_operator
begin_operator
turn_to satellite0 planet3 star0
0
1
0 1 6 4
1
end_operator
begin_operator
turn_to satellite0 planet3 star7
0
1
0 1 7 4
1
end_operator
begin_operator
turn_to satellite0 planet4 groundstation1
0
1
0 1 0 5
1
end_operator
begin_operator
turn_to satellite0 planet4 groundstation2
0
1
0 1 1 5
1
end_operator
begin_operator
turn_to satellite0 planet4 phenomenon5
0
1
0 1 2 5
1
end_operator
begin_operator
turn_to satellite0 planet4 phenomenon6
0
1
0 1 3 5
1
end_operator
begin_operator
turn_to satellite0 planet4 planet3
0
1
0 1 4 5
1
end_operator
begin_operator
turn_to satellite0 planet4 star0
0
1
0 1 6 5
1
end_operator
begin_operator
turn_to satellite0 planet4 star7
0
1
0 1 7 5
1
end_operator
begin_operator
turn_to satellite0 star0 groundstation1
0
1
0 1 0 6
1
end_operator
begin_operator
turn_to satellite0 star0 groundstation2
0
1
0 1 1 6
1
end_operator
begin_operator
turn_to satellite0 star0 phenomenon5
0
1
0 1 2 6
1
end_operator
begin_operator
turn_to satellite0 star0 phenomenon6
0
1
0 1 3 6
1
end_operator
begin_operator
turn_to satellite0 star0 planet3
0
1
0 1 4 6
1
end_operator
begin_operator
turn_to satellite0 star0 planet4
0
1
0 1 5 6
1
end_operator
begin_operator
turn_to satellite0 star0 star7
0
1
0 1 7 6
1
end_operator
begin_operator
turn_to satellite0 star7 groundstation1
0
1
0 1 0 7
1
end_operator
begin_operator
turn_to satellite0 star7 groundstation2
0
1
0 1 1 7
1
end_operator
begin_operator
turn_to satellite0 star7 phenomenon5
0
1
0 1 2 7
1
end_operator
begin_operator
turn_to satellite0 star7 phenomenon6
0
1
0 1 3 7
1
end_operator
begin_operator
turn_to satellite0 star7 planet3
0
1
0 1 4 7
1
end_operator
begin_operator
turn_to satellite0 star7 planet4
0
1
0 1 5 7
1
end_operator
begin_operator
turn_to satellite0 star7 star0
0
1
0 1 6 7
1
end_operator
0
