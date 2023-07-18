begin_version
3
end_version
begin_metric
0
end_metric
17
begin_variable
var0
-1
2
Atom power_on(instrument1)
NegatedAtom power_on(instrument1)
end_variable
begin_variable
var1
-1
2
Atom power_on(instrument2)
NegatedAtom power_on(instrument2)
end_variable
begin_variable
var2
-1
2
Atom power_avail(satellite1)
NegatedAtom power_avail(satellite1)
end_variable
begin_variable
var3
-1
2
Atom power_avail(satellite0)
NegatedAtom power_avail(satellite0)
end_variable
begin_variable
var4
-1
2
Atom power_on(instrument0)
NegatedAtom power_on(instrument0)
end_variable
begin_variable
var5
-1
10
Atom pointing(satellite1, groundstation1)
Atom pointing(satellite1, phenomenon8)
Atom pointing(satellite1, phenomenon9)
Atom pointing(satellite1, planet3)
Atom pointing(satellite1, planet5)
Atom pointing(satellite1, star0)
Atom pointing(satellite1, star2)
Atom pointing(satellite1, star4)
Atom pointing(satellite1, star6)
Atom pointing(satellite1, star7)
end_variable
begin_variable
var6
-1
10
Atom pointing(satellite0, groundstation1)
Atom pointing(satellite0, phenomenon8)
Atom pointing(satellite0, phenomenon9)
Atom pointing(satellite0, planet3)
Atom pointing(satellite0, planet5)
Atom pointing(satellite0, star0)
Atom pointing(satellite0, star2)
Atom pointing(satellite0, star4)
Atom pointing(satellite0, star6)
Atom pointing(satellite0, star7)
end_variable
begin_variable
var7
-1
2
Atom calibrated(instrument2)
NegatedAtom calibrated(instrument2)
end_variable
begin_variable
var8
-1
2
Atom calibrated(instrument1)
NegatedAtom calibrated(instrument1)
end_variable
begin_variable
var9
-1
2
Atom have_image(star6, infrared1)
NegatedAtom have_image(star6, infrared1)
end_variable
begin_variable
var10
-1
2
Atom have_image(star4, infrared1)
NegatedAtom have_image(star4, infrared1)
end_variable
begin_variable
var11
-1
2
Atom have_image(planet3, infrared1)
NegatedAtom have_image(planet3, infrared1)
end_variable
begin_variable
var12
-1
2
Atom calibrated(instrument0)
NegatedAtom calibrated(instrument0)
end_variable
begin_variable
var13
-1
2
Atom have_image(star7, infrared0)
NegatedAtom have_image(star7, infrared0)
end_variable
begin_variable
var14
-1
2
Atom have_image(planet5, thermograph2)
NegatedAtom have_image(planet5, thermograph2)
end_variable
begin_variable
var15
-1
2
Atom have_image(phenomenon9, infrared0)
NegatedAtom have_image(phenomenon9, infrared0)
end_variable
begin_variable
var16
-1
2
Atom have_image(phenomenon8, thermograph2)
NegatedAtom have_image(phenomenon8, thermograph2)
end_variable
0
begin_state
1
1
0
0
1
5
8
1
1
1
1
1
1
1
1
1
1
end_state
begin_goal
8
5 4
9 0
10 0
11 0
13 0
14 0
15 0
16 0
end_goal
205
begin_operator
calibrate satellite0 instrument0 star0
2
6 5
4 0
1
0 12 -1 0
1
end_operator
begin_operator
calibrate satellite1 instrument1 star2
2
5 6
0 0
1
0 8 -1 0
1
end_operator
begin_operator
calibrate satellite1 instrument2 star2
2
5 6
1 0
1
0 7 -1 0
1
end_operator
begin_operator
switch_off instrument0 satellite0
0
2
0 3 -1 0
0 4 0 1
1
end_operator
begin_operator
switch_off instrument1 satellite1
0
2
0 2 -1 0
0 0 0 1
1
end_operator
begin_operator
switch_off instrument2 satellite1
0
2
0 2 -1 0
0 1 0 1
1
end_operator
begin_operator
switch_on instrument0 satellite0
0
3
0 12 -1 1
0 3 0 1
0 4 -1 0
1
end_operator
begin_operator
switch_on instrument1 satellite1
0
3
0 8 -1 1
0 2 0 1
0 0 -1 0
1
end_operator
begin_operator
switch_on instrument2 satellite1
0
3
0 7 -1 1
0 2 0 1
0 1 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon8 instrument0 thermograph2
3
12 0
6 1
4 0
1
0 16 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon9 instrument0 infrared0
3
12 0
6 2
4 0
1
0 15 -1 0
1
end_operator
begin_operator
take_image satellite0 planet5 instrument0 thermograph2
3
12 0
6 4
4 0
1
0 14 -1 0
1
end_operator
begin_operator
take_image satellite0 star7 instrument0 infrared0
3
12 0
6 9
4 0
1
0 13 -1 0
1
end_operator
begin_operator
take_image satellite1 phenomenon8 instrument1 thermograph2
3
8 0
5 1
0 0
1
0 16 -1 0
1
end_operator
begin_operator
take_image satellite1 phenomenon8 instrument2 thermograph2
3
7 0
5 1
1 0
1
0 16 -1 0
1
end_operator
begin_operator
take_image satellite1 phenomenon9 instrument1 infrared0
3
8 0
5 2
0 0
1
0 15 -1 0
1
end_operator
begin_operator
take_image satellite1 planet3 instrument1 infrared1
3
8 0
5 3
0 0
1
0 11 -1 0
1
end_operator
begin_operator
take_image satellite1 planet3 instrument2 infrared1
3
7 0
5 3
1 0
1
0 11 -1 0
1
end_operator
begin_operator
take_image satellite1 planet5 instrument1 thermograph2
3
8 0
5 4
0 0
1
0 14 -1 0
1
end_operator
begin_operator
take_image satellite1 planet5 instrument2 thermograph2
3
7 0
5 4
1 0
1
0 14 -1 0
1
end_operator
begin_operator
take_image satellite1 star4 instrument1 infrared1
3
8 0
5 7
0 0
1
0 10 -1 0
1
end_operator
begin_operator
take_image satellite1 star4 instrument2 infrared1
3
7 0
5 7
1 0
1
0 10 -1 0
1
end_operator
begin_operator
take_image satellite1 star6 instrument1 infrared1
3
8 0
5 8
0 0
1
0 9 -1 0
1
end_operator
begin_operator
take_image satellite1 star6 instrument2 infrared1
3
7 0
5 8
1 0
1
0 9 -1 0
1
end_operator
begin_operator
take_image satellite1 star7 instrument1 infrared0
3
8 0
5 9
0 0
1
0 13 -1 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 phenomenon8
0
1
0 6 1 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 phenomenon9
0
1
0 6 2 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 planet3
0
1
0 6 3 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 planet5
0
1
0 6 4 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 star0
0
1
0 6 5 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 star2
0
1
0 6 6 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 star4
0
1
0 6 7 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 star6
0
1
0 6 8 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 star7
0
1
0 6 9 0
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 groundstation1
0
1
0 6 0 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 phenomenon9
0
1
0 6 2 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 planet3
0
1
0 6 3 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 planet5
0
1
0 6 4 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 star0
0
1
0 6 5 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 star2
0
1
0 6 6 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 star4
0
1
0 6 7 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 star6
0
1
0 6 8 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 star7
0
1
0 6 9 1
1
end_operator
begin_operator
turn_to satellite0 phenomenon9 groundstation1
0
1
0 6 0 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon9 phenomenon8
0
1
0 6 1 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon9 planet3
0
1
0 6 3 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon9 planet5
0
1
0 6 4 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon9 star0
0
1
0 6 5 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon9 star2
0
1
0 6 6 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon9 star4
0
1
0 6 7 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon9 star6
0
1
0 6 8 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon9 star7
0
1
0 6 9 2
1
end_operator
begin_operator
turn_to satellite0 planet3 groundstation1
0
1
0 6 0 3
1
end_operator
begin_operator
turn_to satellite0 planet3 phenomenon8
0
1
0 6 1 3
1
end_operator
begin_operator
turn_to satellite0 planet3 phenomenon9
0
1
0 6 2 3
1
end_operator
begin_operator
turn_to satellite0 planet3 planet5
0
1
0 6 4 3
1
end_operator
begin_operator
turn_to satellite0 planet3 star0
0
1
0 6 5 3
1
end_operator
begin_operator
turn_to satellite0 planet3 star2
0
1
0 6 6 3
1
end_operator
begin_operator
turn_to satellite0 planet3 star4
0
1
0 6 7 3
1
end_operator
begin_operator
turn_to satellite0 planet3 star6
0
1
0 6 8 3
1
end_operator
begin_operator
turn_to satellite0 planet3 star7
0
1
0 6 9 3
1
end_operator
begin_operator
turn_to satellite0 planet5 groundstation1
0
1
0 6 0 4
1
end_operator
begin_operator
turn_to satellite0 planet5 phenomenon8
0
1
0 6 1 4
1
end_operator
begin_operator
turn_to satellite0 planet5 phenomenon9
0
1
0 6 2 4
1
end_operator
begin_operator
turn_to satellite0 planet5 planet3
0
1
0 6 3 4
1
end_operator
begin_operator
turn_to satellite0 planet5 star0
0
1
0 6 5 4
1
end_operator
begin_operator
turn_to satellite0 planet5 star2
0
1
0 6 6 4
1
end_operator
begin_operator
turn_to satellite0 planet5 star4
0
1
0 6 7 4
1
end_operator
begin_operator
turn_to satellite0 planet5 star6
0
1
0 6 8 4
1
end_operator
begin_operator
turn_to satellite0 planet5 star7
0
1
0 6 9 4
1
end_operator
begin_operator
turn_to satellite0 star0 groundstation1
0
1
0 6 0 5
1
end_operator
begin_operator
turn_to satellite0 star0 phenomenon8
0
1
0 6 1 5
1
end_operator
begin_operator
turn_to satellite0 star0 phenomenon9
0
1
0 6 2 5
1
end_operator
begin_operator
turn_to satellite0 star0 planet3
0
1
0 6 3 5
1
end_operator
begin_operator
turn_to satellite0 star0 planet5
0
1
0 6 4 5
1
end_operator
begin_operator
turn_to satellite0 star0 star2
0
1
0 6 6 5
1
end_operator
begin_operator
turn_to satellite0 star0 star4
0
1
0 6 7 5
1
end_operator
begin_operator
turn_to satellite0 star0 star6
0
1
0 6 8 5
1
end_operator
begin_operator
turn_to satellite0 star0 star7
0
1
0 6 9 5
1
end_operator
begin_operator
turn_to satellite0 star2 groundstation1
0
1
0 6 0 6
1
end_operator
begin_operator
turn_to satellite0 star2 phenomenon8
0
1
0 6 1 6
1
end_operator
begin_operator
turn_to satellite0 star2 phenomenon9
0
1
0 6 2 6
1
end_operator
begin_operator
turn_to satellite0 star2 planet3
0
1
0 6 3 6
1
end_operator
begin_operator
turn_to satellite0 star2 planet5
0
1
0 6 4 6
1
end_operator
begin_operator
turn_to satellite0 star2 star0
0
1
0 6 5 6
1
end_operator
begin_operator
turn_to satellite0 star2 star4
0
1
0 6 7 6
1
end_operator
begin_operator
turn_to satellite0 star2 star6
0
1
0 6 8 6
1
end_operator
begin_operator
turn_to satellite0 star2 star7
0
1
0 6 9 6
1
end_operator
begin_operator
turn_to satellite0 star4 groundstation1
0
1
0 6 0 7
1
end_operator
begin_operator
turn_to satellite0 star4 phenomenon8
0
1
0 6 1 7
1
end_operator
begin_operator
turn_to satellite0 star4 phenomenon9
0
1
0 6 2 7
1
end_operator
begin_operator
turn_to satellite0 star4 planet3
0
1
0 6 3 7
1
end_operator
begin_operator
turn_to satellite0 star4 planet5
0
1
0 6 4 7
1
end_operator
begin_operator
turn_to satellite0 star4 star0
0
1
0 6 5 7
1
end_operator
begin_operator
turn_to satellite0 star4 star2
0
1
0 6 6 7
1
end_operator
begin_operator
turn_to satellite0 star4 star6
0
1
0 6 8 7
1
end_operator
begin_operator
turn_to satellite0 star4 star7
0
1
0 6 9 7
1
end_operator
begin_operator
turn_to satellite0 star6 groundstation1
0
1
0 6 0 8
1
end_operator
begin_operator
turn_to satellite0 star6 phenomenon8
0
1
0 6 1 8
1
end_operator
begin_operator
turn_to satellite0 star6 phenomenon9
0
1
0 6 2 8
1
end_operator
begin_operator
turn_to satellite0 star6 planet3
0
1
0 6 3 8
1
end_operator
begin_operator
turn_to satellite0 star6 planet5
0
1
0 6 4 8
1
end_operator
begin_operator
turn_to satellite0 star6 star0
0
1
0 6 5 8
1
end_operator
begin_operator
turn_to satellite0 star6 star2
0
1
0 6 6 8
1
end_operator
begin_operator
turn_to satellite0 star6 star4
0
1
0 6 7 8
1
end_operator
begin_operator
turn_to satellite0 star6 star7
0
1
0 6 9 8
1
end_operator
begin_operator
turn_to satellite0 star7 groundstation1
0
1
0 6 0 9
1
end_operator
begin_operator
turn_to satellite0 star7 phenomenon8
0
1
0 6 1 9
1
end_operator
begin_operator
turn_to satellite0 star7 phenomenon9
0
1
0 6 2 9
1
end_operator
begin_operator
turn_to satellite0 star7 planet3
0
1
0 6 3 9
1
end_operator
begin_operator
turn_to satellite0 star7 planet5
0
1
0 6 4 9
1
end_operator
begin_operator
turn_to satellite0 star7 star0
0
1
0 6 5 9
1
end_operator
begin_operator
turn_to satellite0 star7 star2
0
1
0 6 6 9
1
end_operator
begin_operator
turn_to satellite0 star7 star4
0
1
0 6 7 9
1
end_operator
begin_operator
turn_to satellite0 star7 star6
0
1
0 6 8 9
1
end_operator
begin_operator
turn_to satellite1 groundstation1 phenomenon8
0
1
0 5 1 0
1
end_operator
begin_operator
turn_to satellite1 groundstation1 phenomenon9
0
1
0 5 2 0
1
end_operator
begin_operator
turn_to satellite1 groundstation1 planet3
0
1
0 5 3 0
1
end_operator
begin_operator
turn_to satellite1 groundstation1 planet5
0
1
0 5 4 0
1
end_operator
begin_operator
turn_to satellite1 groundstation1 star0
0
1
0 5 5 0
1
end_operator
begin_operator
turn_to satellite1 groundstation1 star2
0
1
0 5 6 0
1
end_operator
begin_operator
turn_to satellite1 groundstation1 star4
0
1
0 5 7 0
1
end_operator
begin_operator
turn_to satellite1 groundstation1 star6
0
1
0 5 8 0
1
end_operator
begin_operator
turn_to satellite1 groundstation1 star7
0
1
0 5 9 0
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 groundstation1
0
1
0 5 0 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 phenomenon9
0
1
0 5 2 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 planet3
0
1
0 5 3 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 planet5
0
1
0 5 4 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 star0
0
1
0 5 5 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 star2
0
1
0 5 6 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 star4
0
1
0 5 7 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 star6
0
1
0 5 8 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 star7
0
1
0 5 9 1
1
end_operator
begin_operator
turn_to satellite1 phenomenon9 groundstation1
0
1
0 5 0 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon9 phenomenon8
0
1
0 5 1 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon9 planet3
0
1
0 5 3 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon9 planet5
0
1
0 5 4 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon9 star0
0
1
0 5 5 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon9 star2
0
1
0 5 6 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon9 star4
0
1
0 5 7 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon9 star6
0
1
0 5 8 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon9 star7
0
1
0 5 9 2
1
end_operator
begin_operator
turn_to satellite1 planet3 groundstation1
0
1
0 5 0 3
1
end_operator
begin_operator
turn_to satellite1 planet3 phenomenon8
0
1
0 5 1 3
1
end_operator
begin_operator
turn_to satellite1 planet3 phenomenon9
0
1
0 5 2 3
1
end_operator
begin_operator
turn_to satellite1 planet3 planet5
0
1
0 5 4 3
1
end_operator
begin_operator
turn_to satellite1 planet3 star0
0
1
0 5 5 3
1
end_operator
begin_operator
turn_to satellite1 planet3 star2
0
1
0 5 6 3
1
end_operator
begin_operator
turn_to satellite1 planet3 star4
0
1
0 5 7 3
1
end_operator
begin_operator
turn_to satellite1 planet3 star6
0
1
0 5 8 3
1
end_operator
begin_operator
turn_to satellite1 planet3 star7
0
1
0 5 9 3
1
end_operator
begin_operator
turn_to satellite1 planet5 groundstation1
0
1
0 5 0 4
1
end_operator
begin_operator
turn_to satellite1 planet5 phenomenon8
0
1
0 5 1 4
1
end_operator
begin_operator
turn_to satellite1 planet5 phenomenon9
0
1
0 5 2 4
1
end_operator
begin_operator
turn_to satellite1 planet5 planet3
0
1
0 5 3 4
1
end_operator
begin_operator
turn_to satellite1 planet5 star0
0
1
0 5 5 4
1
end_operator
begin_operator
turn_to satellite1 planet5 star2
0
1
0 5 6 4
1
end_operator
begin_operator
turn_to satellite1 planet5 star4
0
1
0 5 7 4
1
end_operator
begin_operator
turn_to satellite1 planet5 star6
0
1
0 5 8 4
1
end_operator
begin_operator
turn_to satellite1 planet5 star7
0
1
0 5 9 4
1
end_operator
begin_operator
turn_to satellite1 star0 groundstation1
0
1
0 5 0 5
1
end_operator
begin_operator
turn_to satellite1 star0 phenomenon8
0
1
0 5 1 5
1
end_operator
begin_operator
turn_to satellite1 star0 phenomenon9
0
1
0 5 2 5
1
end_operator
begin_operator
turn_to satellite1 star0 planet3
0
1
0 5 3 5
1
end_operator
begin_operator
turn_to satellite1 star0 planet5
0
1
0 5 4 5
1
end_operator
begin_operator
turn_to satellite1 star0 star2
0
1
0 5 6 5
1
end_operator
begin_operator
turn_to satellite1 star0 star4
0
1
0 5 7 5
1
end_operator
begin_operator
turn_to satellite1 star0 star6
0
1
0 5 8 5
1
end_operator
begin_operator
turn_to satellite1 star0 star7
0
1
0 5 9 5
1
end_operator
begin_operator
turn_to satellite1 star2 groundstation1
0
1
0 5 0 6
1
end_operator
begin_operator
turn_to satellite1 star2 phenomenon8
0
1
0 5 1 6
1
end_operator
begin_operator
turn_to satellite1 star2 phenomenon9
0
1
0 5 2 6
1
end_operator
begin_operator
turn_to satellite1 star2 planet3
0
1
0 5 3 6
1
end_operator
begin_operator
turn_to satellite1 star2 planet5
0
1
0 5 4 6
1
end_operator
begin_operator
turn_to satellite1 star2 star0
0
1
0 5 5 6
1
end_operator
begin_operator
turn_to satellite1 star2 star4
0
1
0 5 7 6
1
end_operator
begin_operator
turn_to satellite1 star2 star6
0
1
0 5 8 6
1
end_operator
begin_operator
turn_to satellite1 star2 star7
0
1
0 5 9 6
1
end_operator
begin_operator
turn_to satellite1 star4 groundstation1
0
1
0 5 0 7
1
end_operator
begin_operator
turn_to satellite1 star4 phenomenon8
0
1
0 5 1 7
1
end_operator
begin_operator
turn_to satellite1 star4 phenomenon9
0
1
0 5 2 7
1
end_operator
begin_operator
turn_to satellite1 star4 planet3
0
1
0 5 3 7
1
end_operator
begin_operator
turn_to satellite1 star4 planet5
0
1
0 5 4 7
1
end_operator
begin_operator
turn_to satellite1 star4 star0
0
1
0 5 5 7
1
end_operator
begin_operator
turn_to satellite1 star4 star2
0
1
0 5 6 7
1
end_operator
begin_operator
turn_to satellite1 star4 star6
0
1
0 5 8 7
1
end_operator
begin_operator
turn_to satellite1 star4 star7
0
1
0 5 9 7
1
end_operator
begin_operator
turn_to satellite1 star6 groundstation1
0
1
0 5 0 8
1
end_operator
begin_operator
turn_to satellite1 star6 phenomenon8
0
1
0 5 1 8
1
end_operator
begin_operator
turn_to satellite1 star6 phenomenon9
0
1
0 5 2 8
1
end_operator
begin_operator
turn_to satellite1 star6 planet3
0
1
0 5 3 8
1
end_operator
begin_operator
turn_to satellite1 star6 planet5
0
1
0 5 4 8
1
end_operator
begin_operator
turn_to satellite1 star6 star0
0
1
0 5 5 8
1
end_operator
begin_operator
turn_to satellite1 star6 star2
0
1
0 5 6 8
1
end_operator
begin_operator
turn_to satellite1 star6 star4
0
1
0 5 7 8
1
end_operator
begin_operator
turn_to satellite1 star6 star7
0
1
0 5 9 8
1
end_operator
begin_operator
turn_to satellite1 star7 groundstation1
0
1
0 5 0 9
1
end_operator
begin_operator
turn_to satellite1 star7 phenomenon8
0
1
0 5 1 9
1
end_operator
begin_operator
turn_to satellite1 star7 phenomenon9
0
1
0 5 2 9
1
end_operator
begin_operator
turn_to satellite1 star7 planet3
0
1
0 5 3 9
1
end_operator
begin_operator
turn_to satellite1 star7 planet5
0
1
0 5 4 9
1
end_operator
begin_operator
turn_to satellite1 star7 star0
0
1
0 5 5 9
1
end_operator
begin_operator
turn_to satellite1 star7 star2
0
1
0 5 6 9
1
end_operator
begin_operator
turn_to satellite1 star7 star4
0
1
0 5 7 9
1
end_operator
begin_operator
turn_to satellite1 star7 star6
0
1
0 5 8 9
1
end_operator
0
