
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem briefcase-o3)
    (:domain briefcase)

    (:objects
        l0 l1 l2 l3 - location
        o0 o1 o2 - portable
    )

    (:init
        (at o2 l0)
        (at o0 l0)
        (at o1 l0)
        (is-at l0)
        (in o2)
        (in o1)
    )

    (:goal
        (and (at o0 l0) (at o1 l0) (at o2 l0) (is-at l0) (in o2))
    )

    
    
    
)

