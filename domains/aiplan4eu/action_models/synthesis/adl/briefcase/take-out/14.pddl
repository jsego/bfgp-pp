
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem briefcase-o2)
    (:domain briefcase)

    (:objects
        l0 l1 l2 - location
        o0 o1 - portable
    )

    (:init
        (at o0 l0)
        (at o1 l0)
        (is-at l0)
        (in o0)
    )

    (:goal
        (and (at o0 l0) (at o1 l0) (is-at l0))
    )

    
    
    
)

