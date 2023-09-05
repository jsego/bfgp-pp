(define (domain corridor)
 (:requirements :strips :negative-preconditions)
 (:predicates 
    (at ?l)
    (adjacent ?l1 ?l2)
    (goal_at ?l))
 
 (:action move_right
    :parameters (?from ?to)
    :precondition (and (adjacent ?from ?to) (at ?from) (not (at ?to)))
    :effect (and (not (at ?from)) (at ?to)))
    
 (:action move_left
    :parameters (?from ?to)
    :precondition (and (adjacent ?to ?from) (at ?from) (not (at ?to)))
    :effect (and (not (at ?from)) (at ?to))))
 
