
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
        (clear f)
        (clear c)
        (ontable d)
        (ontable f)
        (ontable a)
        (ontable c)
        (on e a)
        (on b d)
        (handempty )
    )

    (:goal
        (and (clear e) (clear b) (clear f) (ontable d) (ontable f) (ontable a) (on e a) (on b d) (holding c))
    )

    
    
    
)

