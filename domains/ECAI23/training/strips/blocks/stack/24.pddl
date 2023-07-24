
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
        (clear a)
        (clear d)
        (clear b)
        (ontable a)
        (ontable d)
        (ontable c)
        (on b c)
        (holding e)
    )

    (:goal
        (and (clear a) (clear d) (clear e) (ontable a) (ontable d) (ontable c) (on e b) (on b c) (handempty ))
    )

    
    
    
)
