
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
        (clear d)
        (ontable d)
        (ontable a)
        (on b a)
        (on e b)
        (holding c)
    )

    (:goal
        (and (clear d) (clear c) (ontable d) (ontable a) (on b a) (on c e) (on e b) (handempty ))
    )

    
    
    
)

