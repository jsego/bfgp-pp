(define (problem corridor_9)
  (:domain corridor)
  (:objects l1 l2 l3 l4 l5 l6 l7 l8 l9 l10 l11 - object )
  (:init (at l8)
    (goal_at l10)
    (adjacent l1 l2)    
(adjacent l2 l3)    
(adjacent l3 l4)    
(adjacent l4 l5)    
(adjacent l5 l6)    
(adjacent l6 l7)    
(adjacent l7 l8)    
(adjacent l8 l9)    
(adjacent l9 l10)    
(adjacent l10 l11))
  (:goal (and (at l10))))