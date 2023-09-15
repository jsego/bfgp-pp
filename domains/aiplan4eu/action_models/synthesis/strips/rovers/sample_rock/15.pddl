
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem roverprob2435)
    (:domain Rover)

    (:objects
        camera0 camera1 camera2 - camera
        general - lander
        colour high_res low_res - mode
        objective0 objective1 objective2 - objective
        rover0 rover1 - rover
        rover0store rover1store - store
        waypoint0 waypoint1 waypoint2 waypoint3 - waypoint
    )

    (:init
        (visible waypoint1 waypoint2)
        (visible waypoint3 waypoint2)
        (visible waypoint0 waypoint3)
        (visible waypoint0 waypoint1)
        (visible waypoint2 waypoint3)
        (visible waypoint2 waypoint1)
        (visible waypoint1 waypoint3)
        (visible waypoint3 waypoint1)
        (visible waypoint0 waypoint2)
        (visible waypoint1 waypoint0)
        (visible waypoint3 waypoint0)
        (visible waypoint2 waypoint0)
        (at_rock_sample waypoint1)
        (at_soil_sample waypoint3)
        (at_lander general waypoint3)
        (channel_free general)
        (at rover1 waypoint2)
        (at rover0 waypoint1)
        (available rover0)
        (available rover1)
        (store_of rover1store rover1)
        (store_of rover0store rover0)
        (empty rover0store)
        (equipped_for_rock_analysis rover0)
        (equipped_for_imaging rover0)
        (equipped_for_imaging rover1)
        (can_traverse rover1 waypoint1 waypoint3)
        (can_traverse rover1 waypoint3 waypoint1)
        (can_traverse rover0 waypoint0 waypoint3)
        (can_traverse rover0 waypoint0 waypoint1)
        (can_traverse rover0 waypoint1 waypoint0)
        (can_traverse rover1 waypoint1 waypoint2)
        (can_traverse rover1 waypoint1 waypoint0)
        (can_traverse rover1 waypoint2 waypoint1)
        (can_traverse rover0 waypoint3 waypoint0)
        (can_traverse rover1 waypoint0 waypoint1)
        (equipped_for_soil_analysis rover1)
        (on_board camera0 rover1)
        (on_board camera2 rover0)
        (on_board camera1 rover1)
        (calibration_target camera1 objective1)
        (calibration_target camera0 objective1)
        (calibration_target camera2 objective1)
        (supports camera0 high_res)
        (supports camera2 low_res)
        (supports camera1 colour)
        (supports camera0 low_res)
        (supports camera1 high_res)
        (supports camera2 high_res)
        (supports camera2 colour)
        (visible_from objective2 waypoint2)
        (visible_from objective0 waypoint3)
        (visible_from objective1 waypoint0)
        (visible_from objective2 waypoint1)
        (visible_from objective1 waypoint2)
        (visible_from objective0 waypoint0)
        (visible_from objective1 waypoint1)
        (visible_from objective0 waypoint2)
        (visible_from objective2 waypoint0)
        (visible_from objective0 waypoint1)
        (have_image rover0 objective0 colour)
        (have_image rover0 objective2 high_res)
        (have_image rover1 objective0 high_res)
        (communicated_image_data objective2 high_res)
        (communicated_image_data objective0 colour)
        (communicated_image_data objective0 high_res)
        (full rover1store)
        (have_soil_analysis rover1 waypoint1)
        (have_soil_analysis rover1 waypoint2)
        (communicated_soil_data waypoint1)
        (communicated_soil_data waypoint2)
        (have_rock_analysis rover0 waypoint0)
        (communicated_rock_data waypoint0)
    )

    (:goal
        (and (visible waypoint1 waypoint2) (visible waypoint3 waypoint2) (visible waypoint0 waypoint3) (visible waypoint0 waypoint1) (visible waypoint2 waypoint3) (visible waypoint2 waypoint1) (visible waypoint1 waypoint3) (visible waypoint3 waypoint1) (visible waypoint0 waypoint2) (visible waypoint1 waypoint0) (visible waypoint3 waypoint0) (visible waypoint2 waypoint0) (at_soil_sample waypoint3) (at_lander general waypoint3) (channel_free general) (at rover1 waypoint2) (at rover0 waypoint1) (available rover0) (available rover1) (store_of rover1store rover1) (store_of rover0store rover0) (equipped_for_rock_analysis rover0) (equipped_for_imaging rover0) (equipped_for_imaging rover1) (can_traverse rover1 waypoint1 waypoint3) (can_traverse rover1 waypoint3 waypoint1) (can_traverse rover0 waypoint0 waypoint3) (can_traverse rover0 waypoint0 waypoint1) (can_traverse rover0 waypoint1 waypoint0) (can_traverse rover1 waypoint1 waypoint2) (can_traverse rover1 waypoint1 waypoint0) (can_traverse rover1 waypoint2 waypoint1) (can_traverse rover0 waypoint3 waypoint0) (can_traverse rover1 waypoint0 waypoint1) (equipped_for_soil_analysis rover1) (on_board camera0 rover1) (on_board camera1 rover1) (on_board camera2 rover0) (calibration_target camera1 objective1) (calibration_target camera0 objective1) (calibration_target camera2 objective1) (supports camera0 high_res) (supports camera2 low_res) (supports camera1 colour) (supports camera0 low_res) (supports camera1 high_res) (supports camera2 high_res) (supports camera2 colour) (visible_from objective2 waypoint2) (visible_from objective0 waypoint3) (visible_from objective1 waypoint0) (visible_from objective2 waypoint1) (visible_from objective1 waypoint2) (visible_from objective0 waypoint0) (visible_from objective1 waypoint1) (visible_from objective0 waypoint2) (visible_from objective2 waypoint0) (visible_from objective0 waypoint1) (have_image rover0 objective0 colour) (have_image rover0 objective2 high_res) (have_image rover1 objective0 high_res) (communicated_image_data objective2 high_res) (communicated_image_data objective0 high_res) (communicated_image_data objective0 colour) (full rover1store) (full rover0store) (have_soil_analysis rover1 waypoint1) (have_soil_analysis rover1 waypoint2) (communicated_soil_data waypoint1) (communicated_soil_data waypoint2) (have_rock_analysis rover0 waypoint0) (have_rock_analysis rover0 waypoint1) (communicated_rock_data waypoint0))
    )

    
    
    
)
