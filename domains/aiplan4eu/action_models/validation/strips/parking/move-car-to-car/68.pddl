
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem parking)
    (:domain parking)

    (:objects
        car_00 car_01 car_02 car_03 car_04 car_05 car_06 car_07 car_08 car_09 car_10 car_11 car_12 car_13 car_14 car_15 car_16 car_17 - car
        curb_0 curb_1 curb_2 curb_3 curb_4 curb_5 curb_6 curb_7 curb_8 curb_9 - curb
    )

    (:init
        (= (total-cost ) 0.0)
        (at-curb car_09)
        (at-curb car_07)
        (at-curb car_15)
        (at-curb car_01)
        (at-curb car_13)
        (at-curb car_14)
        (at-curb car_06)
        (at-curb car_03)
        (at-curb car_16)
        (at-curb car_05)
        (at-curb-num car_14 curb_2)
        (at-curb-num car_03 curb_8)
        (at-curb-num car_13 curb_9)
        (at-curb-num car_07 curb_0)
        (at-curb-num car_09 curb_6)
        (at-curb-num car_05 curb_3)
        (at-curb-num car_15 curb_5)
        (at-curb-num car_16 curb_7)
        (at-curb-num car_06 curb_1)
        (at-curb-num car_01 curb_4)
        (behind-car car_12 car_12)
        (behind-car car_08 car_08)
        (behind-car car_17 car_16)
        (behind-car car_00 car_05)
        (behind-car car_10 car_07)
        (behind-car car_04 car_04)
        (behind-car car_02 car_02)
        (behind-car car_11 car_03)
        (car-clear car_09)
        (car-clear car_15)
        (car-clear car_01)
        (car-clear car_13)
        (car-clear car_14)
        (car-clear car_10)
        (car-clear car_00)
        (car-clear car_17)
        (car-clear car_06)
        (car-clear car_11)
    )

    (:goal
        (and (at-curb car_09) (at-curb car_07) (at-curb car_15) (at-curb car_01) (at-curb car_13) (at-curb car_14) (at-curb car_06) (at-curb car_03) (at-curb car_16) (at-curb car_05) (at-curb-num car_14 curb_2) (at-curb-num car_03 curb_8) (at-curb-num car_13 curb_9) (at-curb-num car_07 curb_0) (at-curb-num car_09 curb_6) (at-curb-num car_05 curb_3) (at-curb-num car_15 curb_5) (at-curb-num car_16 curb_7) (at-curb-num car_06 curb_1) (at-curb-num car_01 curb_4) (behind-car car_12 car_12) (behind-car car_08 car_08) (behind-car car_17 car_16) (behind-car car_10 car_06) (behind-car car_00 car_05) (behind-car car_04 car_04) (behind-car car_02 car_02) (behind-car car_11 car_03) (car-clear car_09) (car-clear car_07) (car-clear car_15) (car-clear car_01) (car-clear car_13) (car-clear car_14) (car-clear car_10) (car-clear car_00) (car-clear car_17) (car-clear car_11))
    )

    
    
    (:metric minimize (total-cost ))
)

