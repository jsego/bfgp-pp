
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
        (clear b)
        (clear c)
        (clear d)
        (ontable d)
        (ontable g)
        (ontable e)
        (ontable b)
        (on f e)
        (on c f)
        (on a g)
        (handempty )
    )

    (:goal
        (and (clear a) (clear d) (clear c) (ontable d) (ontable g) (ontable e) (on f e) (on c f) (on a g) (holding b))
    )

    
    
    
)
