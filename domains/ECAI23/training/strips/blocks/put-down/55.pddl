
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-7-0)
    (:domain BLOCKS)

    (:objects
        a b c d e f g - object
    )

    (:init
        (clear a)
        (clear d)
        (clear e)
        (ontable g)
        (ontable e)
        (ontable b)
        (on a f)
        (on d b)
        (on f g)
        (holding c)
    )

    (:goal
        (and (clear a) (clear d) (clear e) (clear c) (ontable g) (ontable e) (ontable b) (ontable c) (on a f) (on d b) (on f g) (handempty ))
    )

    
    
    
)
