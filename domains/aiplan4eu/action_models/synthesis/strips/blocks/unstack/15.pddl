
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-5-0)
    (:domain BLOCKS)

    (:objects
        a b c d e - object
    )

    (:init
        (clear e)
        (clear c)
        (ontable d)
        (ontable a)
        (on b a)
        (on c d)
        (on e b)
        (handempty )
    )

    (:goal
        (and (clear b) (clear c) (ontable d) (ontable a) (on b a) (on c d) (holding e))
    )

    
    
    
)

