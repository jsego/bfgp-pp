
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-6-0)
    (:domain BLOCKS)

    (:objects
        a b c d e f - object
    )

    (:init
        (clear e)
        (clear b)
        (clear a)
        (ontable d)
        (ontable b)
        (ontable c)
        (on a c)
        (on f d)
        (on e f)
        (handempty )
    )

    (:goal
        (and (clear e) (clear b) (clear c) (ontable d) (ontable b) (ontable c) (on f d) (on e f) (holding a))
    )

    
    
    
)
