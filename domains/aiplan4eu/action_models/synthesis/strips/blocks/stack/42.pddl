
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
        (clear a)
        (clear c)
        (clear e)
        (ontable d)
        (ontable e)
        (ontable f)
        (ontable a)
        (on c f)
        (holding b)
    )

    (:goal
        (and (clear d) (clear b) (clear c) (clear e) (ontable e) (ontable d) (ontable f) (ontable a) (on b a) (on c f) (handempty ))
    )

    
    
    
)

