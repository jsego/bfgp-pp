;; satellites=25, instruments=41, modes=4, directions=21, out_folder=testing/medium, instance_id=13, seed=1019

(define (problem satellite-13)
 (:domain satellite)
 (:objects 
    sat1 sat2 sat3 sat4 sat5 sat6 sat7 sat8 sat9 sat10 sat11 sat12 sat13 sat14 sat15 sat16 sat17 sat18 sat19 sat20 sat21 sat22 sat23 sat24 sat25 - satellite
    ins1 ins2 ins3 ins4 ins5 ins6 ins7 ins8 ins9 ins10 ins11 ins12 ins13 ins14 ins15 ins16 ins17 ins18 ins19 ins20 ins21 ins22 ins23 ins24 ins25 ins26 ins27 ins28 ins29 ins30 ins31 ins32 ins33 ins34 ins35 ins36 ins37 ins38 ins39 ins40 ins41 - instrument
    mod1 mod2 mod3 mod4 - mode
    dir1 dir2 dir3 dir4 dir5 dir6 dir7 dir8 dir9 dir10 dir11 dir12 dir13 dir14 dir15 dir16 dir17 dir18 dir19 dir20 dir21 - direction
    )
 (:init 
    (pointing sat1 dir2)
    (pointing sat2 dir11)
    (pointing sat3 dir7)
    (pointing sat4 dir4)
    (pointing sat5 dir8)
    (pointing sat6 dir15)
    (pointing sat7 dir20)
    (pointing sat8 dir18)
    (pointing sat9 dir8)
    (pointing sat10 dir10)
    (pointing sat11 dir13)
    (pointing sat12 dir13)
    (pointing sat13 dir10)
    (pointing sat14 dir9)
    (pointing sat15 dir8)
    (pointing sat16 dir9)
    (pointing sat17 dir4)
    (pointing sat18 dir21)
    (pointing sat19 dir12)
    (pointing sat20 dir14)
    (pointing sat21 dir2)
    (pointing sat22 dir6)
    (pointing sat23 dir15)
    (pointing sat24 dir10)
    (pointing sat25 dir16)
    (power_avail sat1)
    (power_avail sat2)
    (power_avail sat3)
    (power_avail sat4)
    (power_avail sat5)
    (power_avail sat6)
    (power_avail sat7)
    (power_avail sat8)
    (power_avail sat9)
    (power_avail sat10)
    (power_avail sat11)
    (power_avail sat12)
    (power_avail sat13)
    (power_avail sat14)
    (power_avail sat15)
    (power_avail sat16)
    (power_avail sat17)
    (power_avail sat18)
    (power_avail sat19)
    (power_avail sat20)
    (power_avail sat21)
    (power_avail sat22)
    (power_avail sat23)
    (power_avail sat24)
    (power_avail sat25)
    (calibration_target ins1 dir21)
    (calibration_target ins2 dir16)
    (calibration_target ins3 dir2)
    (calibration_target ins4 dir4)
    (calibration_target ins5 dir16)
    (calibration_target ins6 dir6)
    (calibration_target ins7 dir20)
    (calibration_target ins8 dir7)
    (calibration_target ins9 dir17)
    (calibration_target ins10 dir13)
    (calibration_target ins11 dir14)
    (calibration_target ins12 dir16)
    (calibration_target ins13 dir6)
    (calibration_target ins14 dir14)
    (calibration_target ins15 dir2)
    (calibration_target ins16 dir4)
    (calibration_target ins17 dir21)
    (calibration_target ins18 dir10)
    (calibration_target ins19 dir4)
    (calibration_target ins20 dir15)
    (calibration_target ins21 dir13)
    (calibration_target ins22 dir19)
    (calibration_target ins23 dir17)
    (calibration_target ins24 dir4)
    (calibration_target ins25 dir10)
    (calibration_target ins26 dir6)
    (calibration_target ins27 dir14)
    (calibration_target ins28 dir7)
    (calibration_target ins29 dir10)
    (calibration_target ins30 dir21)
    (calibration_target ins31 dir15)
    (calibration_target ins32 dir7)
    (calibration_target ins33 dir15)
    (calibration_target ins34 dir7)
    (calibration_target ins35 dir19)
    (calibration_target ins36 dir7)
    (calibration_target ins37 dir8)
    (calibration_target ins38 dir17)
    (calibration_target ins39 dir4)
    (calibration_target ins40 dir19)
    (calibration_target ins41 dir12)
    (on_board ins1 sat11)
    (on_board ins2 sat21)
    (on_board ins3 sat18)
    (on_board ins4 sat9)
    (on_board ins5 sat19)
    (on_board ins6 sat22)
    (on_board ins7 sat8)
    (on_board ins8 sat10)
    (on_board ins9 sat6)
    (on_board ins10 sat23)
    (on_board ins11 sat13)
    (on_board ins12 sat12)
    (on_board ins13 sat7)
    (on_board ins14 sat15)
    (on_board ins15 sat24)
    (on_board ins16 sat14)
    (on_board ins17 sat17)
    (on_board ins18 sat3)
    (on_board ins19 sat2)
    (on_board ins20 sat20)
    (on_board ins21 sat16)
    (on_board ins22 sat4)
    (on_board ins23 sat5)
    (on_board ins24 sat1)
    (on_board ins25 sat25)
    (on_board ins26 sat22)
    (on_board ins27 sat15)
    (on_board ins28 sat14)
    (on_board ins29 sat15)
    (on_board ins30 sat8)
    (on_board ins31 sat20)
    (on_board ins32 sat24)
    (on_board ins33 sat9)
    (on_board ins34 sat11)
    (on_board ins35 sat25)
    (on_board ins36 sat25)
    (on_board ins37 sat16)
    (on_board ins38 sat1)
    (on_board ins39 sat19)
    (on_board ins40 sat22)
    (on_board ins41 sat20)
    (supports ins19 mod4)
    (supports ins33 mod1)
    (supports ins12 mod2)
    (supports ins30 mod1)
    (supports ins28 mod3)
    (supports ins22 mod2)
    (supports ins34 mod4)
    (supports ins14 mod3)
    (supports ins2 mod4)
    (supports ins34 mod3)
    (supports ins28 mod1)
    (supports ins23 mod1)
    (supports ins11 mod1)
    (supports ins17 mod2)
    (supports ins5 mod3)
    (supports ins30 mod2)
    (supports ins38 mod2)
    (supports ins7 mod1)
    (supports ins15 mod2)
    (supports ins32 mod1)
    (supports ins12 mod1)
    (supports ins29 mod1)
    (supports ins27 mod3)
    (supports ins13 mod3)
    (supports ins1 mod3)
    (supports ins31 mod1)
    (supports ins10 mod1)
    (supports ins23 mod2)
    (supports ins2 mod1)
    (supports ins8 mod1)
    (supports ins4 mod2)
    (supports ins31 mod4)
    (supports ins3 mod4)
    (supports ins26 mod2)
    (supports ins39 mod3)
    (supports ins40 mod3)
    (supports ins24 mod2)
    (supports ins2 mod3)
    (supports ins17 mod1)
    (supports ins21 mod3)
    (supports ins7 mod3)
    (supports ins3 mod1)
    (supports ins18 mod1)
    (supports ins16 mod1)
    (supports ins37 mod2)
    (supports ins18 mod2)
    (supports ins7 mod2)
    (supports ins14 mod2)
    (supports ins35 mod1)
    (supports ins8 mod4)
    (supports ins20 mod3)
    (supports ins37 mod1)
    (supports ins10 mod3)
    (supports ins16 mod3)
    (supports ins35 mod3)
    (supports ins26 mod4)
    (supports ins39 mod4)
    (supports ins26 mod3)
    (supports ins3 mod2)
    (supports ins41 mod4)
    (supports ins33 mod4)
    (supports ins3 mod3)
    (supports ins36 mod1)
    (supports ins4 mod4)
    (supports ins13 mod4)
    (supports ins5 mod4)
    (supports ins9 mod1)
    (supports ins40 mod1)
    (supports ins20 mod4)
    (supports ins34 mod2)
    (supports ins6 mod1)
    (supports ins25 mod1))
 (:goal  (and (pointing sat1 dir4)
   (pointing sat2 dir19)
   (pointing sat6 dir17)
   (pointing sat9 dir5)
   (pointing sat10 dir5)
   (pointing sat13 dir11)
   (pointing sat16 dir15)
   (pointing sat18 dir13)
   (pointing sat19 dir14)
   (pointing sat20 dir13)
   (pointing sat23 dir16)
   (pointing sat25 dir11)
   (have_image dir7 mod1)
   (have_image dir12 mod3)
   (have_image dir19 mod1)
   (have_image dir18 mod4)
   (have_image dir8 mod4)
   (have_image dir4 mod2)
   (have_image dir3 mod4)
   (have_image dir2 mod4)
   (have_image dir8 mod2)
   (have_image dir16 mod4)
   (have_image dir17 mod3)
   (have_image dir21 mod4)
   (have_image dir19 mod3)
   (have_image dir9 mod2)
   (have_image dir10 mod1)
   (have_image dir9 mod3)
   (have_image dir7 mod3)
   (have_image dir14 mod4)
   (have_image dir9 mod4)
   (have_image dir13 mod3)
   (have_image dir14 mod1)
   (have_image dir13 mod4)
   (have_image dir15 mod4)
   (have_image dir6 mod2)
   (have_image dir1 mod4)
   (have_image dir16 mod3)
   (have_image dir2 mod1)
   (have_image dir5 mod4)
   (have_image dir4 mod1)
   (have_image dir1 mod3)
   (have_image dir9 mod1)
   (have_image dir14 mod2)
   (have_image dir11 mod1)
   (have_image dir2 mod3)
   (have_image dir5 mod3)
   (have_image dir21 mod1)
   (have_image dir16 mod2)
   (have_image dir17 mod2)
   (have_image dir3 mod2)
   (have_image dir10 mod4)
   (have_image dir7 mod2)
   (have_image dir12 mod1)
   (have_image dir19 mod2)
   (have_image dir21 mod3)
   (have_image dir18 mod1)
   (have_image dir20 mod1)
   (have_image dir3 mod3)
   (have_image dir1 mod2)
   (have_image dir11 mod4)
   (have_image dir11 mod3)
   (have_image dir5 mod1)
   (have_image dir6 mod1)
   (have_image dir18 mod3)
   (have_image dir2 mod2)
   (have_image dir14 mod3))))
