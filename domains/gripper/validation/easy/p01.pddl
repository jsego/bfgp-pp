(define (problem gripper-2)
(:domain gripper-strips)
(:objects ball1 ball2 - ball)
(:init
   (at-robby rooma)
   (free left)
   (free right)
   (at ball1 rooma)
   (at ball2 rooma)
)
(:goal (and
   (at ball1 roomb)
   (at ball2 roomb)
)))
