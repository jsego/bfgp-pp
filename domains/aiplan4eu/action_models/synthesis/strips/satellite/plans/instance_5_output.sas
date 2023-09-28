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
2
Atom power_on(instrument6)
NegatedAtom power_on(instrument6)
end_variable
begin_variable
var1
-1
2
Atom power_on(instrument7)
NegatedAtom power_on(instrument7)
end_variable
begin_variable
var2
-1
2
Atom power_on(instrument8)
NegatedAtom power_on(instrument8)
end_variable
begin_variable
var3
-1
2
Atom power_avail(satellite2)
NegatedAtom power_avail(satellite2)
end_variable
begin_variable
var4
-1
2
Atom power_on(instrument3)
NegatedAtom power_on(instrument3)
end_variable
begin_variable
var5
-1
2
Atom power_on(instrument4)
NegatedAtom power_on(instrument4)
end_variable
begin_variable
var6
-1
2
Atom power_on(instrument5)
NegatedAtom power_on(instrument5)
end_variable
begin_variable
var7
-1
2
Atom power_avail(satellite1)
NegatedAtom power_avail(satellite1)
end_variable
begin_variable
var8
-1
2
Atom power_on(instrument0)
NegatedAtom power_on(instrument0)
end_variable
begin_variable
var9
-1
2
Atom power_on(instrument1)
NegatedAtom power_on(instrument1)
end_variable
begin_variable
var10
-1
2
Atom power_on(instrument2)
NegatedAtom power_on(instrument2)
end_variable
begin_variable
var11
-1
2
Atom power_avail(satellite0)
NegatedAtom power_avail(satellite0)
end_variable
begin_variable
var12
-1
10
Atom pointing(satellite2, groundstation0)
Atom pointing(satellite2, groundstation1)
Atom pointing(satellite2, groundstation2)
Atom pointing(satellite2, phenomenon5)
Atom pointing(satellite2, phenomenon6)
Atom pointing(satellite2, phenomenon8)
Atom pointing(satellite2, planet9)
Atom pointing(satellite2, star3)
Atom pointing(satellite2, star4)
Atom pointing(satellite2, star7)
end_variable
begin_variable
var13
-1
10
Atom pointing(satellite1, groundstation0)
Atom pointing(satellite1, groundstation1)
Atom pointing(satellite1, groundstation2)
Atom pointing(satellite1, phenomenon5)
Atom pointing(satellite1, phenomenon6)
Atom pointing(satellite1, phenomenon8)
Atom pointing(satellite1, planet9)
Atom pointing(satellite1, star3)
Atom pointing(satellite1, star4)
Atom pointing(satellite1, star7)
end_variable
begin_variable
var14
-1
10
Atom pointing(satellite0, groundstation0)
Atom pointing(satellite0, groundstation1)
Atom pointing(satellite0, groundstation2)
Atom pointing(satellite0, phenomenon5)
Atom pointing(satellite0, phenomenon6)
Atom pointing(satellite0, phenomenon8)
Atom pointing(satellite0, planet9)
Atom pointing(satellite0, star3)
Atom pointing(satellite0, star4)
Atom pointing(satellite0, star7)
end_variable
begin_variable
var15
-1
2
Atom calibrated(instrument8)
NegatedAtom calibrated(instrument8)
end_variable
begin_variable
var16
-1
2
Atom calibrated(instrument7)
NegatedAtom calibrated(instrument7)
end_variable
begin_variable
var17
-1
2
Atom calibrated(instrument6)
NegatedAtom calibrated(instrument6)
end_variable
begin_variable
var18
-1
2
Atom calibrated(instrument5)
NegatedAtom calibrated(instrument5)
end_variable
begin_variable
var19
-1
2
Atom calibrated(instrument4)
NegatedAtom calibrated(instrument4)
end_variable
begin_variable
var20
-1
2
Atom calibrated(instrument3)
NegatedAtom calibrated(instrument3)
end_variable
begin_variable
var21
-1
2
Atom calibrated(instrument2)
NegatedAtom calibrated(instrument2)
end_variable
begin_variable
var22
-1
2
Atom calibrated(instrument1)
NegatedAtom calibrated(instrument1)
end_variable
begin_variable
var23
-1
2
Atom calibrated(instrument0)
NegatedAtom calibrated(instrument0)
end_variable
begin_variable
var24
-1
2
Atom have_image(star7, thermograph0)
NegatedAtom have_image(star7, thermograph0)
end_variable
begin_variable
var25
-1
2
Atom have_image(star3, thermograph0)
NegatedAtom have_image(star3, thermograph0)
end_variable
begin_variable
var26
-1
2
Atom have_image(planet9, spectrograph1)
NegatedAtom have_image(planet9, spectrograph1)
end_variable
begin_variable
var27
-1
2
Atom have_image(phenomenon8, image2)
NegatedAtom have_image(phenomenon8, image2)
end_variable
begin_variable
var28
-1
2
Atom have_image(phenomenon6, image2)
NegatedAtom have_image(phenomenon6, image2)
end_variable
begin_variable
var29
-1
2
Atom have_image(phenomenon5, image2)
NegatedAtom have_image(phenomenon5, image2)
end_variable
0
begin_state
1
1
1
0
1
1
1
0
1
1
1
0
3
2
5
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
1
1
1
1
1
end_state
begin_goal
8
13 2
14 3
24 0
25 0
26 0
27 0
28 0
29 0
end_goal
339
begin_operator
calibrate satellite0 instrument0 groundstation2
2
14 2
8 0
1
0 23 -1 0
1
end_operator
begin_operator
calibrate satellite0 instrument1 groundstation1
2
14 1
9 0
1
0 22 -1 0
1
end_operator
begin_operator
calibrate satellite0 instrument2 groundstation0
2
14 0
10 0
1
0 21 -1 0
1
end_operator
begin_operator
calibrate satellite1 instrument3 groundstation0
2
13 0
4 0
1
0 20 -1 0
1
end_operator
begin_operator
calibrate satellite1 instrument4 groundstation2
2
13 2
5 0
1
0 19 -1 0
1
end_operator
begin_operator
calibrate satellite1 instrument5 groundstation1
2
13 1
6 0
1
0 18 -1 0
1
end_operator
begin_operator
calibrate satellite2 instrument6 groundstation1
2
12 1
0 0
1
0 17 -1 0
1
end_operator
begin_operator
calibrate satellite2 instrument7 groundstation1
2
12 1
1 0
1
0 16 -1 0
1
end_operator
begin_operator
calibrate satellite2 instrument8 groundstation0
2
12 0
2 0
1
0 15 -1 0
1
end_operator
begin_operator
switch_off instrument0 satellite0
0
2
0 11 -1 0
0 8 0 1
1
end_operator
begin_operator
switch_off instrument1 satellite0
0
2
0 11 -1 0
0 9 0 1
1
end_operator
begin_operator
switch_off instrument2 satellite0
0
2
0 11 -1 0
0 10 0 1
1
end_operator
begin_operator
switch_off instrument3 satellite1
0
2
0 7 -1 0
0 4 0 1
1
end_operator
begin_operator
switch_off instrument4 satellite1
0
2
0 7 -1 0
0 5 0 1
1
end_operator
begin_operator
switch_off instrument5 satellite1
0
2
0 7 -1 0
0 6 0 1
1
end_operator
begin_operator
switch_off instrument6 satellite2
0
2
0 3 -1 0
0 0 0 1
1
end_operator
begin_operator
switch_off instrument7 satellite2
0
2
0 3 -1 0
0 1 0 1
1
end_operator
begin_operator
switch_off instrument8 satellite2
0
2
0 3 -1 0
0 2 0 1
1
end_operator
begin_operator
switch_on instrument0 satellite0
0
3
0 23 -1 1
0 11 0 1
0 8 -1 0
1
end_operator
begin_operator
switch_on instrument1 satellite0
0
3
0 22 -1 1
0 11 0 1
0 9 -1 0
1
end_operator
begin_operator
switch_on instrument2 satellite0
0
3
0 21 -1 1
0 11 0 1
0 10 -1 0
1
end_operator
begin_operator
switch_on instrument3 satellite1
0
3
0 20 -1 1
0 7 0 1
0 4 -1 0
1
end_operator
begin_operator
switch_on instrument4 satellite1
0
3
0 19 -1 1
0 7 0 1
0 5 -1 0
1
end_operator
begin_operator
switch_on instrument5 satellite1
0
3
0 18 -1 1
0 7 0 1
0 6 -1 0
1
end_operator
begin_operator
switch_on instrument6 satellite2
0
3
0 17 -1 1
0 3 0 1
0 0 -1 0
1
end_operator
begin_operator
switch_on instrument7 satellite2
0
3
0 16 -1 1
0 3 0 1
0 1 -1 0
1
end_operator
begin_operator
switch_on instrument8 satellite2
0
3
0 15 -1 1
0 3 0 1
0 2 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon5 instrument0 image2
3
23 0
14 3
8 0
1
0 29 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon5 instrument1 image2
3
22 0
14 3
9 0
1
0 29 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon5 instrument2 image2
3
21 0
14 3
10 0
1
0 29 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon6 instrument0 image2
3
23 0
14 4
8 0
1
0 28 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon6 instrument1 image2
3
22 0
14 4
9 0
1
0 28 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon6 instrument2 image2
3
21 0
14 4
10 0
1
0 28 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon8 instrument0 image2
3
23 0
14 5
8 0
1
0 27 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon8 instrument1 image2
3
22 0
14 5
9 0
1
0 27 -1 0
1
end_operator
begin_operator
take_image satellite0 phenomenon8 instrument2 image2
3
21 0
14 5
10 0
1
0 27 -1 0
1
end_operator
begin_operator
take_image satellite0 planet9 instrument0 spectrograph1
3
23 0
14 6
8 0
1
0 26 -1 0
1
end_operator
begin_operator
take_image satellite0 planet9 instrument1 spectrograph1
3
22 0
14 6
9 0
1
0 26 -1 0
1
end_operator
begin_operator
take_image satellite0 star3 instrument0 thermograph0
3
23 0
14 7
8 0
1
0 25 -1 0
1
end_operator
begin_operator
take_image satellite0 star3 instrument1 thermograph0
3
22 0
14 7
9 0
1
0 25 -1 0
1
end_operator
begin_operator
take_image satellite0 star7 instrument0 thermograph0
3
23 0
14 9
8 0
1
0 24 -1 0
1
end_operator
begin_operator
take_image satellite0 star7 instrument1 thermograph0
3
22 0
14 9
9 0
1
0 24 -1 0
1
end_operator
begin_operator
take_image satellite1 phenomenon5 instrument4 image2
3
19 0
13 3
5 0
1
0 29 -1 0
1
end_operator
begin_operator
take_image satellite1 phenomenon5 instrument5 image2
3
18 0
13 3
6 0
1
0 29 -1 0
1
end_operator
begin_operator
take_image satellite1 phenomenon6 instrument4 image2
3
19 0
13 4
5 0
1
0 28 -1 0
1
end_operator
begin_operator
take_image satellite1 phenomenon6 instrument5 image2
3
18 0
13 4
6 0
1
0 28 -1 0
1
end_operator
begin_operator
take_image satellite1 phenomenon8 instrument4 image2
3
19 0
13 5
5 0
1
0 27 -1 0
1
end_operator
begin_operator
take_image satellite1 phenomenon8 instrument5 image2
3
18 0
13 5
6 0
1
0 27 -1 0
1
end_operator
begin_operator
take_image satellite1 planet9 instrument3 spectrograph1
3
20 0
13 6
4 0
1
0 26 -1 0
1
end_operator
begin_operator
take_image satellite1 planet9 instrument4 spectrograph1
3
19 0
13 6
5 0
1
0 26 -1 0
1
end_operator
begin_operator
take_image satellite1 planet9 instrument5 spectrograph1
3
18 0
13 6
6 0
1
0 26 -1 0
1
end_operator
begin_operator
take_image satellite1 star3 instrument3 thermograph0
3
20 0
13 7
4 0
1
0 25 -1 0
1
end_operator
begin_operator
take_image satellite1 star3 instrument5 thermograph0
3
18 0
13 7
6 0
1
0 25 -1 0
1
end_operator
begin_operator
take_image satellite1 star7 instrument3 thermograph0
3
20 0
13 9
4 0
1
0 24 -1 0
1
end_operator
begin_operator
take_image satellite1 star7 instrument5 thermograph0
3
18 0
13 9
6 0
1
0 24 -1 0
1
end_operator
begin_operator
take_image satellite2 phenomenon5 instrument6 image2
3
17 0
12 3
0 0
1
0 29 -1 0
1
end_operator
begin_operator
take_image satellite2 phenomenon5 instrument7 image2
3
16 0
12 3
1 0
1
0 29 -1 0
1
end_operator
begin_operator
take_image satellite2 phenomenon5 instrument8 image2
3
15 0
12 3
2 0
1
0 29 -1 0
1
end_operator
begin_operator
take_image satellite2 phenomenon6 instrument6 image2
3
17 0
12 4
0 0
1
0 28 -1 0
1
end_operator
begin_operator
take_image satellite2 phenomenon6 instrument7 image2
3
16 0
12 4
1 0
1
0 28 -1 0
1
end_operator
begin_operator
take_image satellite2 phenomenon6 instrument8 image2
3
15 0
12 4
2 0
1
0 28 -1 0
1
end_operator
begin_operator
take_image satellite2 phenomenon8 instrument6 image2
3
17 0
12 5
0 0
1
0 27 -1 0
1
end_operator
begin_operator
take_image satellite2 phenomenon8 instrument7 image2
3
16 0
12 5
1 0
1
0 27 -1 0
1
end_operator
begin_operator
take_image satellite2 phenomenon8 instrument8 image2
3
15 0
12 5
2 0
1
0 27 -1 0
1
end_operator
begin_operator
take_image satellite2 planet9 instrument8 spectrograph1
3
15 0
12 6
2 0
1
0 26 -1 0
1
end_operator
begin_operator
take_image satellite2 star3 instrument7 thermograph0
3
16 0
12 7
1 0
1
0 25 -1 0
1
end_operator
begin_operator
take_image satellite2 star3 instrument8 thermograph0
3
15 0
12 7
2 0
1
0 25 -1 0
1
end_operator
begin_operator
take_image satellite2 star7 instrument7 thermograph0
3
16 0
12 9
1 0
1
0 24 -1 0
1
end_operator
begin_operator
take_image satellite2 star7 instrument8 thermograph0
3
15 0
12 9
2 0
1
0 24 -1 0
1
end_operator
begin_operator
turn_to satellite0 groundstation0 groundstation1
0
1
0 14 1 0
1
end_operator
begin_operator
turn_to satellite0 groundstation0 groundstation2
0
1
0 14 2 0
1
end_operator
begin_operator
turn_to satellite0 groundstation0 phenomenon5
0
1
0 14 3 0
1
end_operator
begin_operator
turn_to satellite0 groundstation0 phenomenon6
0
1
0 14 4 0
1
end_operator
begin_operator
turn_to satellite0 groundstation0 phenomenon8
0
1
0 14 5 0
1
end_operator
begin_operator
turn_to satellite0 groundstation0 planet9
0
1
0 14 6 0
1
end_operator
begin_operator
turn_to satellite0 groundstation0 star3
0
1
0 14 7 0
1
end_operator
begin_operator
turn_to satellite0 groundstation0 star4
0
1
0 14 8 0
1
end_operator
begin_operator
turn_to satellite0 groundstation0 star7
0
1
0 14 9 0
1
end_operator
begin_operator
turn_to satellite0 groundstation1 groundstation0
0
1
0 14 0 1
1
end_operator
begin_operator
turn_to satellite0 groundstation1 groundstation2
0
1
0 14 2 1
1
end_operator
begin_operator
turn_to satellite0 groundstation1 phenomenon5
0
1
0 14 3 1
1
end_operator
begin_operator
turn_to satellite0 groundstation1 phenomenon6
0
1
0 14 4 1
1
end_operator
begin_operator
turn_to satellite0 groundstation1 phenomenon8
0
1
0 14 5 1
1
end_operator
begin_operator
turn_to satellite0 groundstation1 planet9
0
1
0 14 6 1
1
end_operator
begin_operator
turn_to satellite0 groundstation1 star3
0
1
0 14 7 1
1
end_operator
begin_operator
turn_to satellite0 groundstation1 star4
0
1
0 14 8 1
1
end_operator
begin_operator
turn_to satellite0 groundstation1 star7
0
1
0 14 9 1
1
end_operator
begin_operator
turn_to satellite0 groundstation2 groundstation0
0
1
0 14 0 2
1
end_operator
begin_operator
turn_to satellite0 groundstation2 groundstation1
0
1
0 14 1 2
1
end_operator
begin_operator
turn_to satellite0 groundstation2 phenomenon5
0
1
0 14 3 2
1
end_operator
begin_operator
turn_to satellite0 groundstation2 phenomenon6
0
1
0 14 4 2
1
end_operator
begin_operator
turn_to satellite0 groundstation2 phenomenon8
0
1
0 14 5 2
1
end_operator
begin_operator
turn_to satellite0 groundstation2 planet9
0
1
0 14 6 2
1
end_operator
begin_operator
turn_to satellite0 groundstation2 star3
0
1
0 14 7 2
1
end_operator
begin_operator
turn_to satellite0 groundstation2 star4
0
1
0 14 8 2
1
end_operator
begin_operator
turn_to satellite0 groundstation2 star7
0
1
0 14 9 2
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 groundstation0
0
1
0 14 0 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 groundstation1
0
1
0 14 1 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 groundstation2
0
1
0 14 2 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 phenomenon6
0
1
0 14 4 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 phenomenon8
0
1
0 14 5 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 planet9
0
1
0 14 6 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 star3
0
1
0 14 7 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 star4
0
1
0 14 8 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon5 star7
0
1
0 14 9 3
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 groundstation0
0
1
0 14 0 4
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 groundstation1
0
1
0 14 1 4
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 groundstation2
0
1
0 14 2 4
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 phenomenon5
0
1
0 14 3 4
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 phenomenon8
0
1
0 14 5 4
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 planet9
0
1
0 14 6 4
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 star3
0
1
0 14 7 4
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 star4
0
1
0 14 8 4
1
end_operator
begin_operator
turn_to satellite0 phenomenon6 star7
0
1
0 14 9 4
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 groundstation0
0
1
0 14 0 5
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 groundstation1
0
1
0 14 1 5
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 groundstation2
0
1
0 14 2 5
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 phenomenon5
0
1
0 14 3 5
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 phenomenon6
0
1
0 14 4 5
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 planet9
0
1
0 14 6 5
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 star3
0
1
0 14 7 5
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 star4
0
1
0 14 8 5
1
end_operator
begin_operator
turn_to satellite0 phenomenon8 star7
0
1
0 14 9 5
1
end_operator
begin_operator
turn_to satellite0 planet9 groundstation0
0
1
0 14 0 6
1
end_operator
begin_operator
turn_to satellite0 planet9 groundstation1
0
1
0 14 1 6
1
end_operator
begin_operator
turn_to satellite0 planet9 groundstation2
0
1
0 14 2 6
1
end_operator
begin_operator
turn_to satellite0 planet9 phenomenon5
0
1
0 14 3 6
1
end_operator
begin_operator
turn_to satellite0 planet9 phenomenon6
0
1
0 14 4 6
1
end_operator
begin_operator
turn_to satellite0 planet9 phenomenon8
0
1
0 14 5 6
1
end_operator
begin_operator
turn_to satellite0 planet9 star3
0
1
0 14 7 6
1
end_operator
begin_operator
turn_to satellite0 planet9 star4
0
1
0 14 8 6
1
end_operator
begin_operator
turn_to satellite0 planet9 star7
0
1
0 14 9 6
1
end_operator
begin_operator
turn_to satellite0 star3 groundstation0
0
1
0 14 0 7
1
end_operator
begin_operator
turn_to satellite0 star3 groundstation1
0
1
0 14 1 7
1
end_operator
begin_operator
turn_to satellite0 star3 groundstation2
0
1
0 14 2 7
1
end_operator
begin_operator
turn_to satellite0 star3 phenomenon5
0
1
0 14 3 7
1
end_operator
begin_operator
turn_to satellite0 star3 phenomenon6
0
1
0 14 4 7
1
end_operator
begin_operator
turn_to satellite0 star3 phenomenon8
0
1
0 14 5 7
1
end_operator
begin_operator
turn_to satellite0 star3 planet9
0
1
0 14 6 7
1
end_operator
begin_operator
turn_to satellite0 star3 star4
0
1
0 14 8 7
1
end_operator
begin_operator
turn_to satellite0 star3 star7
0
1
0 14 9 7
1
end_operator
begin_operator
turn_to satellite0 star4 groundstation0
0
1
0 14 0 8
1
end_operator
begin_operator
turn_to satellite0 star4 groundstation1
0
1
0 14 1 8
1
end_operator
begin_operator
turn_to satellite0 star4 groundstation2
0
1
0 14 2 8
1
end_operator
begin_operator
turn_to satellite0 star4 phenomenon5
0
1
0 14 3 8
1
end_operator
begin_operator
turn_to satellite0 star4 phenomenon6
0
1
0 14 4 8
1
end_operator
begin_operator
turn_to satellite0 star4 phenomenon8
0
1
0 14 5 8
1
end_operator
begin_operator
turn_to satellite0 star4 planet9
0
1
0 14 6 8
1
end_operator
begin_operator
turn_to satellite0 star4 star3
0
1
0 14 7 8
1
end_operator
begin_operator
turn_to satellite0 star4 star7
0
1
0 14 9 8
1
end_operator
begin_operator
turn_to satellite0 star7 groundstation0
0
1
0 14 0 9
1
end_operator
begin_operator
turn_to satellite0 star7 groundstation1
0
1
0 14 1 9
1
end_operator
begin_operator
turn_to satellite0 star7 groundstation2
0
1
0 14 2 9
1
end_operator
begin_operator
turn_to satellite0 star7 phenomenon5
0
1
0 14 3 9
1
end_operator
begin_operator
turn_to satellite0 star7 phenomenon6
0
1
0 14 4 9
1
end_operator
begin_operator
turn_to satellite0 star7 phenomenon8
0
1
0 14 5 9
1
end_operator
begin_operator
turn_to satellite0 star7 planet9
0
1
0 14 6 9
1
end_operator
begin_operator
turn_to satellite0 star7 star3
0
1
0 14 7 9
1
end_operator
begin_operator
turn_to satellite0 star7 star4
0
1
0 14 8 9
1
end_operator
begin_operator
turn_to satellite1 groundstation0 groundstation1
0
1
0 13 1 0
1
end_operator
begin_operator
turn_to satellite1 groundstation0 groundstation2
0
1
0 13 2 0
1
end_operator
begin_operator
turn_to satellite1 groundstation0 phenomenon5
0
1
0 13 3 0
1
end_operator
begin_operator
turn_to satellite1 groundstation0 phenomenon6
0
1
0 13 4 0
1
end_operator
begin_operator
turn_to satellite1 groundstation0 phenomenon8
0
1
0 13 5 0
1
end_operator
begin_operator
turn_to satellite1 groundstation0 planet9
0
1
0 13 6 0
1
end_operator
begin_operator
turn_to satellite1 groundstation0 star3
0
1
0 13 7 0
1
end_operator
begin_operator
turn_to satellite1 groundstation0 star4
0
1
0 13 8 0
1
end_operator
begin_operator
turn_to satellite1 groundstation0 star7
0
1
0 13 9 0
1
end_operator
begin_operator
turn_to satellite1 groundstation1 groundstation0
0
1
0 13 0 1
1
end_operator
begin_operator
turn_to satellite1 groundstation1 groundstation2
0
1
0 13 2 1
1
end_operator
begin_operator
turn_to satellite1 groundstation1 phenomenon5
0
1
0 13 3 1
1
end_operator
begin_operator
turn_to satellite1 groundstation1 phenomenon6
0
1
0 13 4 1
1
end_operator
begin_operator
turn_to satellite1 groundstation1 phenomenon8
0
1
0 13 5 1
1
end_operator
begin_operator
turn_to satellite1 groundstation1 planet9
0
1
0 13 6 1
1
end_operator
begin_operator
turn_to satellite1 groundstation1 star3
0
1
0 13 7 1
1
end_operator
begin_operator
turn_to satellite1 groundstation1 star4
0
1
0 13 8 1
1
end_operator
begin_operator
turn_to satellite1 groundstation1 star7
0
1
0 13 9 1
1
end_operator
begin_operator
turn_to satellite1 groundstation2 groundstation0
0
1
0 13 0 2
1
end_operator
begin_operator
turn_to satellite1 groundstation2 groundstation1
0
1
0 13 1 2
1
end_operator
begin_operator
turn_to satellite1 groundstation2 phenomenon5
0
1
0 13 3 2
1
end_operator
begin_operator
turn_to satellite1 groundstation2 phenomenon6
0
1
0 13 4 2
1
end_operator
begin_operator
turn_to satellite1 groundstation2 phenomenon8
0
1
0 13 5 2
1
end_operator
begin_operator
turn_to satellite1 groundstation2 planet9
0
1
0 13 6 2
1
end_operator
begin_operator
turn_to satellite1 groundstation2 star3
0
1
0 13 7 2
1
end_operator
begin_operator
turn_to satellite1 groundstation2 star4
0
1
0 13 8 2
1
end_operator
begin_operator
turn_to satellite1 groundstation2 star7
0
1
0 13 9 2
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 groundstation0
0
1
0 13 0 3
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 groundstation1
0
1
0 13 1 3
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 groundstation2
0
1
0 13 2 3
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 phenomenon6
0
1
0 13 4 3
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 phenomenon8
0
1
0 13 5 3
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 planet9
0
1
0 13 6 3
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 star3
0
1
0 13 7 3
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 star4
0
1
0 13 8 3
1
end_operator
begin_operator
turn_to satellite1 phenomenon5 star7
0
1
0 13 9 3
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 groundstation0
0
1
0 13 0 4
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 groundstation1
0
1
0 13 1 4
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 groundstation2
0
1
0 13 2 4
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 phenomenon5
0
1
0 13 3 4
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 phenomenon8
0
1
0 13 5 4
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 planet9
0
1
0 13 6 4
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 star3
0
1
0 13 7 4
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 star4
0
1
0 13 8 4
1
end_operator
begin_operator
turn_to satellite1 phenomenon6 star7
0
1
0 13 9 4
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 groundstation0
0
1
0 13 0 5
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 groundstation1
0
1
0 13 1 5
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 groundstation2
0
1
0 13 2 5
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 phenomenon5
0
1
0 13 3 5
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 phenomenon6
0
1
0 13 4 5
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 planet9
0
1
0 13 6 5
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 star3
0
1
0 13 7 5
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 star4
0
1
0 13 8 5
1
end_operator
begin_operator
turn_to satellite1 phenomenon8 star7
0
1
0 13 9 5
1
end_operator
begin_operator
turn_to satellite1 planet9 groundstation0
0
1
0 13 0 6
1
end_operator
begin_operator
turn_to satellite1 planet9 groundstation1
0
1
0 13 1 6
1
end_operator
begin_operator
turn_to satellite1 planet9 groundstation2
0
1
0 13 2 6
1
end_operator
begin_operator
turn_to satellite1 planet9 phenomenon5
0
1
0 13 3 6
1
end_operator
begin_operator
turn_to satellite1 planet9 phenomenon6
0
1
0 13 4 6
1
end_operator
begin_operator
turn_to satellite1 planet9 phenomenon8
0
1
0 13 5 6
1
end_operator
begin_operator
turn_to satellite1 planet9 star3
0
1
0 13 7 6
1
end_operator
begin_operator
turn_to satellite1 planet9 star4
0
1
0 13 8 6
1
end_operator
begin_operator
turn_to satellite1 planet9 star7
0
1
0 13 9 6
1
end_operator
begin_operator
turn_to satellite1 star3 groundstation0
0
1
0 13 0 7
1
end_operator
begin_operator
turn_to satellite1 star3 groundstation1
0
1
0 13 1 7
1
end_operator
begin_operator
turn_to satellite1 star3 groundstation2
0
1
0 13 2 7
1
end_operator
begin_operator
turn_to satellite1 star3 phenomenon5
0
1
0 13 3 7
1
end_operator
begin_operator
turn_to satellite1 star3 phenomenon6
0
1
0 13 4 7
1
end_operator
begin_operator
turn_to satellite1 star3 phenomenon8
0
1
0 13 5 7
1
end_operator
begin_operator
turn_to satellite1 star3 planet9
0
1
0 13 6 7
1
end_operator
begin_operator
turn_to satellite1 star3 star4
0
1
0 13 8 7
1
end_operator
begin_operator
turn_to satellite1 star3 star7
0
1
0 13 9 7
1
end_operator
begin_operator
turn_to satellite1 star4 groundstation0
0
1
0 13 0 8
1
end_operator
begin_operator
turn_to satellite1 star4 groundstation1
0
1
0 13 1 8
1
end_operator
begin_operator
turn_to satellite1 star4 groundstation2
0
1
0 13 2 8
1
end_operator
begin_operator
turn_to satellite1 star4 phenomenon5
0
1
0 13 3 8
1
end_operator
begin_operator
turn_to satellite1 star4 phenomenon6
0
1
0 13 4 8
1
end_operator
begin_operator
turn_to satellite1 star4 phenomenon8
0
1
0 13 5 8
1
end_operator
begin_operator
turn_to satellite1 star4 planet9
0
1
0 13 6 8
1
end_operator
begin_operator
turn_to satellite1 star4 star3
0
1
0 13 7 8
1
end_operator
begin_operator
turn_to satellite1 star4 star7
0
1
0 13 9 8
1
end_operator
begin_operator
turn_to satellite1 star7 groundstation0
0
1
0 13 0 9
1
end_operator
begin_operator
turn_to satellite1 star7 groundstation1
0
1
0 13 1 9
1
end_operator
begin_operator
turn_to satellite1 star7 groundstation2
0
1
0 13 2 9
1
end_operator
begin_operator
turn_to satellite1 star7 phenomenon5
0
1
0 13 3 9
1
end_operator
begin_operator
turn_to satellite1 star7 phenomenon6
0
1
0 13 4 9
1
end_operator
begin_operator
turn_to satellite1 star7 phenomenon8
0
1
0 13 5 9
1
end_operator
begin_operator
turn_to satellite1 star7 planet9
0
1
0 13 6 9
1
end_operator
begin_operator
turn_to satellite1 star7 star3
0
1
0 13 7 9
1
end_operator
begin_operator
turn_to satellite1 star7 star4
0
1
0 13 8 9
1
end_operator
begin_operator
turn_to satellite2 groundstation0 groundstation1
0
1
0 12 1 0
1
end_operator
begin_operator
turn_to satellite2 groundstation0 groundstation2
0
1
0 12 2 0
1
end_operator
begin_operator
turn_to satellite2 groundstation0 phenomenon5
0
1
0 12 3 0
1
end_operator
begin_operator
turn_to satellite2 groundstation0 phenomenon6
0
1
0 12 4 0
1
end_operator
begin_operator
turn_to satellite2 groundstation0 phenomenon8
0
1
0 12 5 0
1
end_operator
begin_operator
turn_to satellite2 groundstation0 planet9
0
1
0 12 6 0
1
end_operator
begin_operator
turn_to satellite2 groundstation0 star3
0
1
0 12 7 0
1
end_operator
begin_operator
turn_to satellite2 groundstation0 star4
0
1
0 12 8 0
1
end_operator
begin_operator
turn_to satellite2 groundstation0 star7
0
1
0 12 9 0
1
end_operator
begin_operator
turn_to satellite2 groundstation1 groundstation0
0
1
0 12 0 1
1
end_operator
begin_operator
turn_to satellite2 groundstation1 groundstation2
0
1
0 12 2 1
1
end_operator
begin_operator
turn_to satellite2 groundstation1 phenomenon5
0
1
0 12 3 1
1
end_operator
begin_operator
turn_to satellite2 groundstation1 phenomenon6
0
1
0 12 4 1
1
end_operator
begin_operator
turn_to satellite2 groundstation1 phenomenon8
0
1
0 12 5 1
1
end_operator
begin_operator
turn_to satellite2 groundstation1 planet9
0
1
0 12 6 1
1
end_operator
begin_operator
turn_to satellite2 groundstation1 star3
0
1
0 12 7 1
1
end_operator
begin_operator
turn_to satellite2 groundstation1 star4
0
1
0 12 8 1
1
end_operator
begin_operator
turn_to satellite2 groundstation1 star7
0
1
0 12 9 1
1
end_operator
begin_operator
turn_to satellite2 groundstation2 groundstation0
0
1
0 12 0 2
1
end_operator
begin_operator
turn_to satellite2 groundstation2 groundstation1
0
1
0 12 1 2
1
end_operator
begin_operator
turn_to satellite2 groundstation2 phenomenon5
0
1
0 12 3 2
1
end_operator
begin_operator
turn_to satellite2 groundstation2 phenomenon6
0
1
0 12 4 2
1
end_operator
begin_operator
turn_to satellite2 groundstation2 phenomenon8
0
1
0 12 5 2
1
end_operator
begin_operator
turn_to satellite2 groundstation2 planet9
0
1
0 12 6 2
1
end_operator
begin_operator
turn_to satellite2 groundstation2 star3
0
1
0 12 7 2
1
end_operator
begin_operator
turn_to satellite2 groundstation2 star4
0
1
0 12 8 2
1
end_operator
begin_operator
turn_to satellite2 groundstation2 star7
0
1
0 12 9 2
1
end_operator
begin_operator
turn_to satellite2 phenomenon5 groundstation0
0
1
0 12 0 3
1
end_operator
begin_operator
turn_to satellite2 phenomenon5 groundstation1
0
1
0 12 1 3
1
end_operator
begin_operator
turn_to satellite2 phenomenon5 groundstation2
0
1
0 12 2 3
1
end_operator
begin_operator
turn_to satellite2 phenomenon5 phenomenon6
0
1
0 12 4 3
1
end_operator
begin_operator
turn_to satellite2 phenomenon5 phenomenon8
0
1
0 12 5 3
1
end_operator
begin_operator
turn_to satellite2 phenomenon5 planet9
0
1
0 12 6 3
1
end_operator
begin_operator
turn_to satellite2 phenomenon5 star3
0
1
0 12 7 3
1
end_operator
begin_operator
turn_to satellite2 phenomenon5 star4
0
1
0 12 8 3
1
end_operator
begin_operator
turn_to satellite2 phenomenon5 star7
0
1
0 12 9 3
1
end_operator
begin_operator
turn_to satellite2 phenomenon6 groundstation0
0
1
0 12 0 4
1
end_operator
begin_operator
turn_to satellite2 phenomenon6 groundstation1
0
1
0 12 1 4
1
end_operator
begin_operator
turn_to satellite2 phenomenon6 groundstation2
0
1
0 12 2 4
1
end_operator
begin_operator
turn_to satellite2 phenomenon6 phenomenon5
0
1
0 12 3 4
1
end_operator
begin_operator
turn_to satellite2 phenomenon6 phenomenon8
0
1
0 12 5 4
1
end_operator
begin_operator
turn_to satellite2 phenomenon6 planet9
0
1
0 12 6 4
1
end_operator
begin_operator
turn_to satellite2 phenomenon6 star3
0
1
0 12 7 4
1
end_operator
begin_operator
turn_to satellite2 phenomenon6 star4
0
1
0 12 8 4
1
end_operator
begin_operator
turn_to satellite2 phenomenon6 star7
0
1
0 12 9 4
1
end_operator
begin_operator
turn_to satellite2 phenomenon8 groundstation0
0
1
0 12 0 5
1
end_operator
begin_operator
turn_to satellite2 phenomenon8 groundstation1
0
1
0 12 1 5
1
end_operator
begin_operator
turn_to satellite2 phenomenon8 groundstation2
0
1
0 12 2 5
1
end_operator
begin_operator
turn_to satellite2 phenomenon8 phenomenon5
0
1
0 12 3 5
1
end_operator
begin_operator
turn_to satellite2 phenomenon8 phenomenon6
0
1
0 12 4 5
1
end_operator
begin_operator
turn_to satellite2 phenomenon8 planet9
0
1
0 12 6 5
1
end_operator
begin_operator
turn_to satellite2 phenomenon8 star3
0
1
0 12 7 5
1
end_operator
begin_operator
turn_to satellite2 phenomenon8 star4
0
1
0 12 8 5
1
end_operator
begin_operator
turn_to satellite2 phenomenon8 star7
0
1
0 12 9 5
1
end_operator
begin_operator
turn_to satellite2 planet9 groundstation0
0
1
0 12 0 6
1
end_operator
begin_operator
turn_to satellite2 planet9 groundstation1
0
1
0 12 1 6
1
end_operator
begin_operator
turn_to satellite2 planet9 groundstation2
0
1
0 12 2 6
1
end_operator
begin_operator
turn_to satellite2 planet9 phenomenon5
0
1
0 12 3 6
1
end_operator
begin_operator
turn_to satellite2 planet9 phenomenon6
0
1
0 12 4 6
1
end_operator
begin_operator
turn_to satellite2 planet9 phenomenon8
0
1
0 12 5 6
1
end_operator
begin_operator
turn_to satellite2 planet9 star3
0
1
0 12 7 6
1
end_operator
begin_operator
turn_to satellite2 planet9 star4
0
1
0 12 8 6
1
end_operator
begin_operator
turn_to satellite2 planet9 star7
0
1
0 12 9 6
1
end_operator
begin_operator
turn_to satellite2 star3 groundstation0
0
1
0 12 0 7
1
end_operator
begin_operator
turn_to satellite2 star3 groundstation1
0
1
0 12 1 7
1
end_operator
begin_operator
turn_to satellite2 star3 groundstation2
0
1
0 12 2 7
1
end_operator
begin_operator
turn_to satellite2 star3 phenomenon5
0
1
0 12 3 7
1
end_operator
begin_operator
turn_to satellite2 star3 phenomenon6
0
1
0 12 4 7
1
end_operator
begin_operator
turn_to satellite2 star3 phenomenon8
0
1
0 12 5 7
1
end_operator
begin_operator
turn_to satellite2 star3 planet9
0
1
0 12 6 7
1
end_operator
begin_operator
turn_to satellite2 star3 star4
0
1
0 12 8 7
1
end_operator
begin_operator
turn_to satellite2 star3 star7
0
1
0 12 9 7
1
end_operator
begin_operator
turn_to satellite2 star4 groundstation0
0
1
0 12 0 8
1
end_operator
begin_operator
turn_to satellite2 star4 groundstation1
0
1
0 12 1 8
1
end_operator
begin_operator
turn_to satellite2 star4 groundstation2
0
1
0 12 2 8
1
end_operator
begin_operator
turn_to satellite2 star4 phenomenon5
0
1
0 12 3 8
1
end_operator
begin_operator
turn_to satellite2 star4 phenomenon6
0
1
0 12 4 8
1
end_operator
begin_operator
turn_to satellite2 star4 phenomenon8
0
1
0 12 5 8
1
end_operator
begin_operator
turn_to satellite2 star4 planet9
0
1
0 12 6 8
1
end_operator
begin_operator
turn_to satellite2 star4 star3
0
1
0 12 7 8
1
end_operator
begin_operator
turn_to satellite2 star4 star7
0
1
0 12 9 8
1
end_operator
begin_operator
turn_to satellite2 star7 groundstation0
0
1
0 12 0 9
1
end_operator
begin_operator
turn_to satellite2 star7 groundstation1
0
1
0 12 1 9
1
end_operator
begin_operator
turn_to satellite2 star7 groundstation2
0
1
0 12 2 9
1
end_operator
begin_operator
turn_to satellite2 star7 phenomenon5
0
1
0 12 3 9
1
end_operator
begin_operator
turn_to satellite2 star7 phenomenon6
0
1
0 12 4 9
1
end_operator
begin_operator
turn_to satellite2 star7 phenomenon8
0
1
0 12 5 9
1
end_operator
begin_operator
turn_to satellite2 star7 planet9
0
1
0 12 6 9
1
end_operator
begin_operator
turn_to satellite2 star7 star3
0
1
0 12 7 9
1
end_operator
begin_operator
turn_to satellite2 star7 star4
0
1
0 12 8 9
1
end_operator
0
