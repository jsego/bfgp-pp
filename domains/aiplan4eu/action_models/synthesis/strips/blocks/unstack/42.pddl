
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
        (clear d)
        (clear b)
        (clear c)
        (clear e)
        (ontable e)
        (ontable d)
        (ontable f)
        (ontable a)
        (on b a)
        (on c f)
        (handempty )
    )

    (:goal
        (and (clear d) (clear b) (clear e) (clear f) (ontable d) (ontable e) (ontable f) (ontable a) (on b a) (holding c))
    )

    
    
    
)

