(define (problem corridor_2)
  (:domain corridor)
  (:objects l1 l2 l3 l4 - object )
  (:init (at l1)
    (goal_at l3)
    (adjacent l1 l2)    
(adjacent l2 l3)    
(adjacent l3 l4))
  (:goal (and (at l3))))
