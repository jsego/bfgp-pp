
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-4-0)
    (:domain BLOCKS)

    (:objects
        a b c d - object
    )

    (:init
        (clear d)
        (clear b)
        (clear a)
        (ontable d)
        (ontable a)
        (ontable c)
        (handempty )
        (on b c)
    )

    (:goal
        (and (clear d) (clear b) (ontable d) (ontable c) (holding a) (on b c))
    )

    
    
    
)

