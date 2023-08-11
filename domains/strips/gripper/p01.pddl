(define (problem gripper-1)
(:domain gripper-strips)
(:objects ball1 - ball)
(:init
   (at-robby rooma)
   (free left)
   (free right)
   (at ball1 rooma)
)
(:goal (and
   (at ball1 roomb)
)))
