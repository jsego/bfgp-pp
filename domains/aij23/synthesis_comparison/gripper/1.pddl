(define (problem gripper_1)
  (:domain Gripper)
  (:objects b1 b2 - ball)
  (:init (at b1 rooma)
    (at b2 rooma)
    (at_robby rooma)
    (free left)
    (free right))
  (:goal (and (at b1 roomb)
    (at b2 roomb))))
