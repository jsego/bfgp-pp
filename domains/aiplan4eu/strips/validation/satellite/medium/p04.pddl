;; satellites=17, instruments=21, modes=3, directions=16, out_folder=testing/medium, instance_id=4, seed=1010

(define (problem satellite-04)
 (:domain satellite)
 (:objects 
    sat1 sat2 sat3 sat4 sat5 sat6 sat7 sat8 sat9 sat10 sat11 sat12 sat13 sat14 sat15 sat16 sat17 - satellite
    ins1 ins2 ins3 ins4 ins5 ins6 ins7 ins8 ins9 ins10 ins11 ins12 ins13 ins14 ins15 ins16 ins17 ins18 ins19 ins20 ins21 - instrument
    mod1 mod2 mod3 - mode
    dir1 dir2 dir3 dir4 dir5 dir6 dir7 dir8 dir9 dir10 dir11 dir12 dir13 dir14 dir15 dir16 - direction
    )
 (:init 
    (pointing sat1 dir8)
    (pointing sat2 dir3)
    (pointing sat3 dir14)
    (pointing sat4 dir14)
    (pointing sat5 dir14)
    (pointing sat6 dir6)
    (pointing sat7 dir5)
    (pointing sat8 dir14)
    (pointing sat9 dir7)
    (pointing sat10 dir4)
    (pointing sat11 dir12)
    (pointing sat12 dir9)
    (pointing sat13 dir5)
    (pointing sat14 dir13)
    (pointing sat15 dir16)
    (pointing sat16 dir12)
    (pointing sat17 dir3)
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
    (calibration_target ins1 dir1)
    (calibration_target ins2 dir10)
    (calibration_target ins3 dir5)
    (calibration_target ins4 dir5)
    (calibration_target ins5 dir6)
    (calibration_target ins6 dir1)
    (calibration_target ins7 dir7)
    (calibration_target ins8 dir14)
    (calibration_target ins9 dir4)
    (calibration_target ins10 dir1)
    (calibration_target ins11 dir1)
    (calibration_target ins12 dir3)
    (calibration_target ins13 dir2)
    (calibration_target ins14 dir2)
    (calibration_target ins15 dir10)
    (calibration_target ins16 dir7)
    (calibration_target ins17 dir8)
    (calibration_target ins18 dir3)
    (calibration_target ins19 dir8)
    (calibration_target ins20 dir10)
    (calibration_target ins21 dir10)
    (on_board ins1 sat5)
    (on_board ins2 sat4)
    (on_board ins3 sat13)
    (on_board ins4 sat9)
    (on_board ins5 sat12)
    (on_board ins6 sat14)
    (on_board ins7 sat1)
    (on_board ins8 sat16)
    (on_board ins9 sat10)
    (on_board ins10 sat17)
    (on_board ins11 sat2)
    (on_board ins12 sat11)
    (on_board ins13 sat15)
    (on_board ins14 sat3)
    (on_board ins15 sat6)
    (on_board ins16 sat7)
    (on_board ins17 sat8)
    (on_board ins18 sat15)
    (on_board ins19 sat9)
    (on_board ins20 sat1)
    (on_board ins21 sat4)
    (supports ins7 mod1)
    (supports ins8 mod3)
    (supports ins14 mod3)
    (supports ins14 mod2)
    (supports ins4 mod1)
    (supports ins15 mod2)
    (supports ins19 mod1)
    (supports ins17 mod2)
    (supports ins16 mod3)
    (supports ins20 mod1)
    (supports ins10 mod3)
    (supports ins5 mod3)
    (supports ins21 mod2)
    (supports ins6 mod2)
    (supports ins11 mod1)
    (supports ins2 mod2)
    (supports ins15 mod1)
    (supports ins19 mod3)
    (supports ins13 mod3)
    (supports ins9 mod3)
    (supports ins10 mod1)
    (supports ins13 mod2)
    (supports ins6 mod3)
    (supports ins16 mod1)
    (supports ins4 mod2)
    (supports ins5 mod1)
    (supports ins7 mod3)
    (supports ins3 mod3)
    (supports ins15 mod3)
    (supports ins9 mod2)
    (supports ins20 mod2)
    (supports ins16 mod2)
    (supports ins12 mod3)
    (supports ins18 mod2)
    (supports ins17 mod1)
    (supports ins1 mod2))
 (:goal  (and (pointing sat1 dir8)
   (pointing sat2 dir8)
   (pointing sat8 dir13)
   (pointing sat11 dir11)
   (pointing sat14 dir9)
   (pointing sat15 dir11)
   (pointing sat16 dir12)
   (have_image dir1 mod1)
   (have_image dir15 mod1)
   (have_image dir8 mod3)
   (have_image dir4 mod2)
   (have_image dir10 mod1)
   (have_image dir14 mod3)
   (have_image dir6 mod2)
   (have_image dir14 mod2)
   (have_image dir13 mod1)
   (have_image dir12 mod2)
   (have_image dir15 mod2)
   (have_image dir7 mod3)
   (have_image dir1 mod2)
   (have_image dir10 mod2)
   (have_image dir3 mod3)
   (have_image dir11 mod2)
   (have_image dir2 mod1)
   (have_image dir5 mod1)
   (have_image dir5 mod2)
   (have_image dir12 mod1)
   (have_image dir12 mod3)
   (have_image dir13 mod2)
   (have_image dir15 mod3)
   (have_image dir1 mod3)
   (have_image dir13 mod3)
   (have_image dir9 mod1)
   (have_image dir5 mod3)
   (have_image dir2 mod2)
   (have_image dir8 mod1)
   (have_image dir3 mod2)
   (have_image dir6 mod1)
   (have_image dir16 mod2)
   (have_image dir6 mod3)
   (have_image dir4 mod3)
   (have_image dir9 mod2)
   (have_image dir11 mod1)
   (have_image dir14 mod1)
   (have_image dir7 mod1)
   (have_image dir11 mod3)
   (have_image dir16 mod1))))
