(define (problem gripper_4)
  (:domain Gripper)
  (:objects b1 b2 b3 b4 b5 - ball)
  (:init (at b1 rooma)
    (at b2 rooma)
    (at b3 rooma)
    (at b4 rooma)
    (at b5 rooma)
    (at_robby rooma)
    (free left)
    (free right))
  (:goal (and (at b1 roomb)
    (at b2 roomb)
    (at b3 roomb)
    (at b4 roomb)
    (at b5 roomb))))