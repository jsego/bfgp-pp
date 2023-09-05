(define (domain Gripper)
   (:requirements :typing :strips)
   (:types room gripper ball - object)
   (:constants left right - gripper rooma roomb - room)
   (:predicates
       (at_robby ?r - room)
       (at ?b - ball ?r - room)
       (free ?g - gripper)
       (carry ?b - ball ?g - gripper))

   (:action move
       :parameters (?from - room ?to - room)
       :precondition (and (at_robby ?from))
       :effect (and (at_robby ?to)
                    (not (at_robby ?from))))

   (:action pick
       :parameters (?b - ball ?r - room ?g - gripper)
       :precondition (and (at ?b ?r)
                          (at_robby ?r)
                          (free ?g))
       :effect (and (carry ?b ?g)
                    (not (at ?b ?r))
                    (not (free ?g))))

   (:action drop
       :parameters (?b - ball ?r - room ?g - gripper)
       :precondition (and (carry ?b ?g)
                          (at_robby ?r))
       :effect (and (at ?b ?r)
                    (free ?g)
                    (not (carry ?b ?g)))))
