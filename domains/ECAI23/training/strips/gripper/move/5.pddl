
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem strips-gripper-x-1)
    (:domain gripper-strips)

    (:objects
        ball1 ball2 ball3 ball4 left right rooma roomb - object
    )

    (:init
        (room rooma)
        (room roomb)
        (ball ball4)
        (ball ball2)
        (ball ball1)
        (ball ball3)
        (at-robby rooma)
        (at ball2 rooma)
        (at ball1 rooma)
        (gripper left)
        (gripper right)
        (carry ball4 right)
        (carry ball3 left)
    )

    (:goal
        (and (room rooma) (room roomb) (ball ball3) (ball ball4) (ball ball2) (ball ball1) (at-robby roomb) (at ball1 rooma) (at ball2 rooma) (gripper left) (gripper right) (carry ball4 right) (carry ball3 left))
    )

    
    
    
)
