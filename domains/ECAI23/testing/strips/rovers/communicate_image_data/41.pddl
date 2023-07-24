
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem roverprob4135)
    (:domain Rover)

    (:objects
        camera0 camera1 camera2 camera3 - camera
        general - lander
        colour high_res low_res - mode
        objective0 objective1 objective2 objective3 objective4 - objective
        rover0 rover1 rover2 rover3 - rover
        rover0store rover1store rover2store rover3store - store
        waypoint0 waypoint1 waypoint10 waypoint2 waypoint3 waypoint4 waypoint5 waypoint6 waypoint7 waypoint8 waypoint9 - waypoint
    )

    (:init
        (visible waypoint3 waypoint9)
        (visible waypoint0 waypoint8)
        (visible waypoint2 waypoint0)
        (visible waypoint6 waypoint5)
        (visible waypoint1 waypoint7)
        (visible waypoint7 waypoint9)
        (visible waypoint3 waypoint8)
        (visible waypoint1 waypoint0)
        (visible waypoint6 waypoint3)
        (visible waypoint8 waypoint4)
        (visible waypoint9 waypoint8)
        (visible waypoint4 waypoint0)
        (visible waypoint10 waypoint6)
        (visible waypoint2 waypoint1)
        (visible waypoint3 waypoint10)
        (visible waypoint5 waypoint6)
        (visible waypoint7 waypoint10)
        (visible waypoint1 waypoint2)
        (visible waypoint4 waypoint1)
        (visible waypoint4 waypoint2)
        (visible waypoint8 waypoint3)
        (visible waypoint0 waypoint4)
        (visible waypoint10 waypoint7)
        (visible waypoint1 waypoint8)
        (visible waypoint4 waypoint9)
        (visible waypoint5 waypoint7)
        (visible waypoint4 waypoint8)
        (visible waypoint10 waypoint1)
        (visible waypoint9 waypoint4)
        (visible waypoint0 waypoint3)
        (visible waypoint5 waypoint1)
        (visible waypoint7 waypoint5)
        (visible waypoint5 waypoint2)
        (visible waypoint1 waypoint10)
        (visible waypoint7 waypoint3)
        (visible waypoint6 waypoint1)
        (visible waypoint9 waypoint3)
        (visible waypoint2 waypoint4)
        (visible waypoint6 waypoint2)
        (visible waypoint4 waypoint10)
        (visible waypoint10 waypoint8)
        (visible waypoint1 waypoint4)
        (visible waypoint6 waypoint9)
        (visible waypoint3 waypoint6)
        (visible waypoint8 waypoint0)
        (visible waypoint1 waypoint5)
        (visible waypoint8 waypoint1)
        (visible waypoint2 waypoint5)
        (visible waypoint9 waypoint6)
        (visible waypoint1 waypoint3)
        (visible waypoint5 waypoint10)
        (visible waypoint0 waypoint7)
        (visible waypoint4 waypoint5)
        (visible waypoint3 waypoint7)
        (visible waypoint10 waypoint4)
        (visible waypoint5 waypoint4)
        (visible waypoint3 waypoint0)
        (visible waypoint6 waypoint10)
        (visible waypoint8 waypoint9)
        (visible waypoint0 waypoint1)
        (visible waypoint7 waypoint0)
        (visible waypoint9 waypoint7)
        (visible waypoint0 waypoint2)
        (visible waypoint3 waypoint1)
        (visible waypoint1 waypoint6)
        (visible waypoint2 waypoint6)
        (visible waypoint6 waypoint4)
        (visible waypoint7 waypoint1)
        (visible waypoint10 waypoint5)
        (visible waypoint4 waypoint6)
        (visible waypoint10 waypoint3)
        (visible waypoint8 waypoint10)
        (at_soil_sample waypoint7)
        (at_soil_sample waypoint10)
        (at_soil_sample waypoint8)
        (at_soil_sample waypoint2)
        (at_rock_sample waypoint1)
        (at_rock_sample waypoint2)
        (at_rock_sample waypoint10)
        (at_rock_sample waypoint9)
        (at_rock_sample waypoint8)
        (at_lander general waypoint9)
        (channel_free general)
        (at rover0 waypoint5)
        (at rover1 waypoint3)
        (at rover3 waypoint1)
        (at rover2 waypoint5)
        (available rover2)
        (available rover1)
        (available rover0)
        (available rover3)
        (store_of rover0store rover0)
        (store_of rover2store rover2)
        (store_of rover1store rover1)
        (store_of rover3store rover3)
        (empty rover1store)
        (empty rover3store)
        (empty rover0store)
        (empty rover2store)
        (equipped_for_soil_analysis rover2)
        (equipped_for_soil_analysis rover0)
        (equipped_for_imaging rover1)
        (equipped_for_imaging rover0)
        (equipped_for_imaging rover3)
        (can_traverse rover1 waypoint5 waypoint6)
        (can_traverse rover0 waypoint4 waypoint2)
        (can_traverse rover1 waypoint6 waypoint2)
        (can_traverse rover0 waypoint9 waypoint4)
        (can_traverse rover0 waypoint4 waypoint9)
        (can_traverse rover2 waypoint0 waypoint1)
        (can_traverse rover0 waypoint4 waypoint8)
        (can_traverse rover1 waypoint8 waypoint1)
        (can_traverse rover0 waypoint4 waypoint10)
        (can_traverse rover3 waypoint9 waypoint4)
        (can_traverse rover0 waypoint1 waypoint4)
        (can_traverse rover3 waypoint4 waypoint9)
        (can_traverse rover1 waypoint6 waypoint10)
        (can_traverse rover3 waypoint4 waypoint8)
        (can_traverse rover3 waypoint2 waypoint4)
        (can_traverse rover2 waypoint3 waypoint9)
        (can_traverse rover0 waypoint4 waypoint5)
        (can_traverse rover2 waypoint1 waypoint0)
        (can_traverse rover0 waypoint10 waypoint4)
        (can_traverse rover1 waypoint3 waypoint9)
        (can_traverse rover1 waypoint6 waypoint5)
        (can_traverse rover1 waypoint1 waypoint0)
        (can_traverse rover3 waypoint7 waypoint0)
        (can_traverse rover2 waypoint4 waypoint2)
        (can_traverse rover3 waypoint4 waypoint5)
        (can_traverse rover3 waypoint3 waypoint1)
        (can_traverse rover0 waypoint8 waypoint4)
        (can_traverse rover0 waypoint4 waypoint0)
        (can_traverse rover2 waypoint2 waypoint4)
        (can_traverse rover0 waypoint4 waypoint1)
        (can_traverse rover1 waypoint6 waypoint1)
        (can_traverse rover3 waypoint8 waypoint4)
        (can_traverse rover2 waypoint8 waypoint9)
        (can_traverse rover2 waypoint9 waypoint6)
        (can_traverse rover3 waypoint4 waypoint1)
        (can_traverse rover3 waypoint4 waypoint2)
        (can_traverse rover2 waypoint1 waypoint6)
        (can_traverse rover0 waypoint2 waypoint4)
        (can_traverse rover2 waypoint7 waypoint1)
        (can_traverse rover3 waypoint1 waypoint4)
        (can_traverse rover1 waypoint1 waypoint6)
        (can_traverse rover1 waypoint7 waypoint1)
        (can_traverse rover1 waypoint4 waypoint6)
        (can_traverse rover3 waypoint1 waypoint3)
        (can_traverse rover1 waypoint10 waypoint6)
        (can_traverse rover2 waypoint6 waypoint9)
        (can_traverse rover2 waypoint9 waypoint3)
        (can_traverse rover0 waypoint0 waypoint3)
        (can_traverse rover1 waypoint9 waypoint3)
        (can_traverse rover3 waypoint4 waypoint0)
        (can_traverse rover2 waypoint6 waypoint4)
        (can_traverse rover0 waypoint6 waypoint1)
        (can_traverse rover1 waypoint0 waypoint1)
        (can_traverse rover2 waypoint6 waypoint5)
        (can_traverse rover3 waypoint1 waypoint10)
        (can_traverse rover2 waypoint4 waypoint6)
        (can_traverse rover0 waypoint0 waypoint7)
        (can_traverse rover3 waypoint10 waypoint1)
        (can_traverse rover1 waypoint2 waypoint6)
        (can_traverse rover2 waypoint1 waypoint7)
        (can_traverse rover2 waypoint9 waypoint8)
        (can_traverse rover2 waypoint5 waypoint6)
        (can_traverse rover0 waypoint5 waypoint4)
        (can_traverse rover3 waypoint6 waypoint4)
        (can_traverse rover1 waypoint1 waypoint8)
        (can_traverse rover0 waypoint0 waypoint4)
        (can_traverse rover3 waypoint4 waypoint6)
        (can_traverse rover3 waypoint0 waypoint4)
        (can_traverse rover2 waypoint6 waypoint10)
        (can_traverse rover1 waypoint3 waypoint6)
        (can_traverse rover1 waypoint6 waypoint4)
        (can_traverse rover2 waypoint10 waypoint6)
        (can_traverse rover0 waypoint3 waypoint0)
        (can_traverse rover0 waypoint7 waypoint0)
        (can_traverse rover1 waypoint6 waypoint3)
        (can_traverse rover3 waypoint0 waypoint7)
        (can_traverse rover1 waypoint1 waypoint7)
        (can_traverse rover0 waypoint1 waypoint6)
        (can_traverse rover2 waypoint6 waypoint1)
        (can_traverse rover3 waypoint5 waypoint4)
        (equipped_for_rock_analysis rover3)
        (on_board camera1 rover0)
        (on_board camera3 rover1)
        (on_board camera2 rover1)
        (on_board camera0 rover3)
        (calibration_target camera2 objective4)
        (calibration_target camera1 objective4)
        (calibration_target camera0 objective2)
        (calibration_target camera3 objective3)
        (supports camera1 high_res)
        (supports camera3 low_res)
        (supports camera2 low_res)
        (supports camera3 high_res)
        (supports camera2 high_res)
        (supports camera1 colour)
        (supports camera0 low_res)
        (supports camera3 colour)
        (supports camera1 low_res)
        (visible_from objective0 waypoint1)
        (visible_from objective0 waypoint2)
        (visible_from objective4 waypoint7)
        (visible_from objective4 waypoint0)
        (visible_from objective1 waypoint7)
        (visible_from objective0 waypoint9)
        (visible_from objective1 waypoint0)
        (visible_from objective4 waypoint1)
        (visible_from objective0 waypoint8)
        (visible_from objective4 waypoint2)
        (visible_from objective3 waypoint0)
        (visible_from objective1 waypoint1)
        (visible_from objective3 waypoint1)
        (visible_from objective3 waypoint2)
        (visible_from objective1 waypoint2)
        (visible_from objective0 waypoint10)
        (visible_from objective2 waypoint0)
        (visible_from objective4 waypoint9)
        (visible_from objective4 waypoint8)
        (visible_from objective1 waypoint9)
        (visible_from objective1 waypoint8)
        (visible_from objective2 waypoint1)
        (visible_from objective0 waypoint4)
        (visible_from objective2 waypoint2)
        (visible_from objective0 waypoint5)
        (visible_from objective4 waypoint4)
        (visible_from objective0 waypoint3)
        (visible_from objective1 waypoint4)
        (visible_from objective3 waypoint4)
        (visible_from objective4 waypoint5)
        (visible_from objective0 waypoint7)
        (visible_from objective0 waypoint6)
        (visible_from objective1 waypoint5)
        (visible_from objective4 waypoint3)
        (visible_from objective1 waypoint3)
        (visible_from objective3 waypoint3)
        (visible_from objective4 waypoint6)
        (visible_from objective0 waypoint0)
        (visible_from objective1 waypoint6)
        (calibrated camera3 rover1)
        (have_soil_analysis rover0 waypoint4)
        (have_soil_analysis rover2 waypoint5)
        (have_soil_analysis rover0 waypoint0)
        (communicated_soil_data waypoint4)
        (communicated_soil_data waypoint0)
        (communicated_soil_data waypoint5)
        (have_image rover0 objective1 low_res)
        (have_image rover1 objective1 low_res)
        (have_image rover0 objective1 high_res)
        (have_image rover1 objective2 low_res)
        (have_image rover1 objective2 high_res)
        (have_image rover0 objective4 high_res)
        (have_image rover0 objective2 colour)
        (communicated_image_data objective1 low_res)
        (communicated_image_data objective4 high_res)
    )

    (:goal
        (and (visible waypoint3 waypoint9) (visible waypoint0 waypoint8) (visible waypoint2 waypoint0) (visible waypoint6 waypoint5) (visible waypoint1 waypoint7) (visible waypoint7 waypoint9) (visible waypoint3 waypoint8) (visible waypoint1 waypoint0) (visible waypoint6 waypoint3) (visible waypoint8 waypoint4) (visible waypoint9 waypoint8) (visible waypoint4 waypoint0) (visible waypoint10 waypoint6) (visible waypoint2 waypoint1) (visible waypoint3 waypoint10) (visible waypoint5 waypoint6) (visible waypoint7 waypoint10) (visible waypoint1 waypoint2) (visible waypoint4 waypoint1) (visible waypoint4 waypoint2) (visible waypoint8 waypoint3) (visible waypoint0 waypoint4) (visible waypoint10 waypoint7) (visible waypoint1 waypoint8) (visible waypoint4 waypoint9) (visible waypoint5 waypoint7) (visible waypoint4 waypoint8) (visible waypoint10 waypoint1) (visible waypoint9 waypoint4) (visible waypoint0 waypoint3) (visible waypoint5 waypoint1) (visible waypoint7 waypoint5) (visible waypoint5 waypoint2) (visible waypoint1 waypoint10) (visible waypoint7 waypoint3) (visible waypoint6 waypoint1) (visible waypoint9 waypoint3) (visible waypoint2 waypoint4) (visible waypoint6 waypoint2) (visible waypoint4 waypoint10) (visible waypoint10 waypoint8) (visible waypoint1 waypoint4) (visible waypoint6 waypoint9) (visible waypoint3 waypoint6) (visible waypoint8 waypoint0) (visible waypoint1 waypoint5) (visible waypoint8 waypoint1) (visible waypoint2 waypoint5) (visible waypoint9 waypoint6) (visible waypoint1 waypoint3) (visible waypoint5 waypoint10) (visible waypoint0 waypoint7) (visible waypoint4 waypoint5) (visible waypoint3 waypoint7) (visible waypoint10 waypoint4) (visible waypoint5 waypoint4) (visible waypoint3 waypoint0) (visible waypoint6 waypoint10) (visible waypoint8 waypoint9) (visible waypoint0 waypoint1) (visible waypoint7 waypoint0) (visible waypoint9 waypoint7) (visible waypoint0 waypoint2) (visible waypoint3 waypoint1) (visible waypoint1 waypoint6) (visible waypoint2 waypoint6) (visible waypoint6 waypoint4) (visible waypoint7 waypoint1) (visible waypoint10 waypoint5) (visible waypoint4 waypoint6) (visible waypoint10 waypoint3) (visible waypoint8 waypoint10) (at_soil_sample waypoint7) (at_soil_sample waypoint10) (at_soil_sample waypoint8) (at_soil_sample waypoint2) (at_rock_sample waypoint1) (at_rock_sample waypoint2) (at_rock_sample waypoint10) (at_rock_sample waypoint9) (at_rock_sample waypoint8) (at_lander general waypoint9) (channel_free general) (at rover0 waypoint5) (at rover3 waypoint1) (at rover2 waypoint5) (at rover1 waypoint3) (available rover2) (available rover1) (available rover0) (available rover3) (store_of rover3store rover3) (store_of rover0store rover0) (store_of rover2store rover2) (store_of rover1store rover1) (empty rover1store) (empty rover3store) (empty rover0store) (empty rover2store) (equipped_for_soil_analysis rover2) (equipped_for_soil_analysis rover0) (equipped_for_imaging rover1) (equipped_for_imaging rover0) (equipped_for_imaging rover3) (can_traverse rover1 waypoint5 waypoint6) (can_traverse rover0 waypoint4 waypoint2) (can_traverse rover1 waypoint6 waypoint2) (can_traverse rover0 waypoint9 waypoint4) (can_traverse rover0 waypoint4 waypoint9) (can_traverse rover2 waypoint0 waypoint1) (can_traverse rover0 waypoint4 waypoint8) (can_traverse rover1 waypoint8 waypoint1) (can_traverse rover0 waypoint4 waypoint10) (can_traverse rover0 waypoint1 waypoint4) (can_traverse rover3 waypoint9 waypoint4) (can_traverse rover1 waypoint6 waypoint10) (can_traverse rover3 waypoint4 waypoint9) (can_traverse rover3 waypoint4 waypoint8) (can_traverse rover3 waypoint2 waypoint4) (can_traverse rover2 waypoint3 waypoint9) (can_traverse rover0 waypoint4 waypoint5) (can_traverse rover2 waypoint1 waypoint0) (can_traverse rover0 waypoint10 waypoint4) (can_traverse rover1 waypoint3 waypoint9) (can_traverse rover1 waypoint6 waypoint5) (can_traverse rover1 waypoint1 waypoint0) (can_traverse rover3 waypoint7 waypoint0) (can_traverse rover2 waypoint4 waypoint2) (can_traverse rover3 waypoint4 waypoint5) (can_traverse rover3 waypoint3 waypoint1) (can_traverse rover0 waypoint8 waypoint4) (can_traverse rover0 waypoint4 waypoint0) (can_traverse rover2 waypoint2 waypoint4) (can_traverse rover0 waypoint4 waypoint1) (can_traverse rover1 waypoint6 waypoint1) (can_traverse rover3 waypoint8 waypoint4) (can_traverse rover2 waypoint8 waypoint9) (can_traverse rover2 waypoint9 waypoint6) (can_traverse rover3 waypoint4 waypoint1) (can_traverse rover3 waypoint4 waypoint2) (can_traverse rover2 waypoint1 waypoint6) (can_traverse rover0 waypoint2 waypoint4) (can_traverse rover2 waypoint7 waypoint1) (can_traverse rover3 waypoint1 waypoint4) (can_traverse rover1 waypoint1 waypoint6) (can_traverse rover1 waypoint7 waypoint1) (can_traverse rover1 waypoint4 waypoint6) (can_traverse rover3 waypoint1 waypoint3) (can_traverse rover1 waypoint10 waypoint6) (can_traverse rover2 waypoint6 waypoint9) (can_traverse rover2 waypoint9 waypoint3) (can_traverse rover0 waypoint0 waypoint3) (can_traverse rover1 waypoint9 waypoint3) (can_traverse rover3 waypoint4 waypoint0) (can_traverse rover2 waypoint6 waypoint4) (can_traverse rover0 waypoint6 waypoint1) (can_traverse rover1 waypoint0 waypoint1) (can_traverse rover2 waypoint6 waypoint5) (can_traverse rover3 waypoint1 waypoint10) (can_traverse rover2 waypoint4 waypoint6) (can_traverse rover0 waypoint0 waypoint7) (can_traverse rover3 waypoint10 waypoint1) (can_traverse rover1 waypoint2 waypoint6) (can_traverse rover2 waypoint1 waypoint7) (can_traverse rover2 waypoint9 waypoint8) (can_traverse rover2 waypoint5 waypoint6) (can_traverse rover0 waypoint5 waypoint4) (can_traverse rover3 waypoint6 waypoint4) (can_traverse rover1 waypoint1 waypoint8) (can_traverse rover0 waypoint0 waypoint4) (can_traverse rover3 waypoint4 waypoint6) (can_traverse rover3 waypoint0 waypoint4) (can_traverse rover2 waypoint6 waypoint10) (can_traverse rover1 waypoint3 waypoint6) (can_traverse rover1 waypoint6 waypoint4) (can_traverse rover2 waypoint10 waypoint6) (can_traverse rover0 waypoint3 waypoint0) (can_traverse rover0 waypoint7 waypoint0) (can_traverse rover1 waypoint6 waypoint3) (can_traverse rover3 waypoint0 waypoint7) (can_traverse rover1 waypoint1 waypoint7) (can_traverse rover0 waypoint1 waypoint6) (can_traverse rover2 waypoint6 waypoint1) (can_traverse rover3 waypoint5 waypoint4) (equipped_for_rock_analysis rover3) (on_board camera1 rover0) (on_board camera3 rover1) (on_board camera2 rover1) (on_board camera0 rover3) (calibration_target camera2 objective4) (calibration_target camera1 objective4) (calibration_target camera0 objective2) (calibration_target camera3 objective3) (supports camera1 high_res) (supports camera3 low_res) (supports camera2 low_res) (supports camera3 high_res) (supports camera2 high_res) (supports camera1 colour) (supports camera0 low_res) (supports camera3 colour) (supports camera1 low_res) (visible_from objective0 waypoint1) (visible_from objective4 waypoint6) (visible_from objective0 waypoint2) (visible_from objective4 waypoint7) (visible_from objective4 waypoint0) (visible_from objective1 waypoint7) (visible_from objective0 waypoint9) (visible_from objective1 waypoint0) (visible_from objective4 waypoint1) (visible_from objective0 waypoint8) (visible_from objective3 waypoint0) (visible_from objective4 waypoint2) (visible_from objective1 waypoint1) (visible_from objective3 waypoint1) (visible_from objective3 waypoint2) (visible_from objective1 waypoint2) (visible_from objective0 waypoint10) (visible_from objective2 waypoint0) (visible_from objective4 waypoint9) (visible_from objective4 waypoint8) (visible_from objective1 waypoint9) (visible_from objective1 waypoint8) (visible_from objective2 waypoint1) (visible_from objective0 waypoint4) (visible_from objective2 waypoint2) (visible_from objective0 waypoint5) (visible_from objective4 waypoint4) (visible_from objective0 waypoint3) (visible_from objective1 waypoint4) (visible_from objective3 waypoint4) (visible_from objective4 waypoint5) (visible_from objective0 waypoint6) (visible_from objective1 waypoint5) (visible_from objective4 waypoint3) (visible_from objective1 waypoint3) (visible_from objective3 waypoint3) (visible_from objective0 waypoint7) (visible_from objective0 waypoint0) (visible_from objective1 waypoint6) (calibrated camera3 rover1) (have_soil_analysis rover0 waypoint4) (have_soil_analysis rover2 waypoint5) (have_soil_analysis rover0 waypoint0) (communicated_soil_data waypoint4) (communicated_soil_data waypoint0) (communicated_soil_data waypoint5) (have_image rover0 objective1 low_res) (have_image rover1 objective1 low_res) (have_image rover0 objective1 high_res) (have_image rover1 objective2 low_res) (have_image rover1 objective2 high_res) (have_image rover0 objective4 high_res) (have_image rover0 objective2 colour) (communicated_image_data objective2 low_res) (communicated_image_data objective1 low_res) (communicated_image_data objective4 high_res))
    )

    
    
    
)
