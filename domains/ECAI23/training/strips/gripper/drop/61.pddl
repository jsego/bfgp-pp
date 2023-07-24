
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem strips-gripper-x-3)
    (:domain gripper-strips)

    (:objects
        ball1 ball2 ball3 ball4 ball5 ball6 ball7 ball8 left right rooma roomb - object
    )

    (:init
        (room rooma)
        (room roomb)
        (ball ball8)
        (ball ball3)
        (ball ball4)
        (ball ball5)
        (ball ball1)
        (ball ball2)
        (ball ball7)
        (ball ball6)
        (at-robby roomb)
        (at ball1 roomb)
        (at ball6 roomb)
        (at ball4 roomb)
        (at ball3 roomb)
        (at ball5 roomb)
        (at ball2 roomb)
        (gripper left)
        (gripper right)
        (carry ball8 right)
        (carry ball7 left)
    )

    (:goal
        (and (room rooma) (room roomb) (ball ball8) (ball ball3) (ball ball6) (ball ball5) (ball ball1) (ball ball2) (ball ball7) (ball ball4) (at-robby roomb) (free left) (at ball1 roomb) (at ball6 roomb) (at ball4 roomb) (at ball7 roomb) (at ball3 roomb) (at ball5 roomb) (at ball2 roomb) (gripper left) (gripper right) (carry ball8 right))
    )

    
    
    
)
