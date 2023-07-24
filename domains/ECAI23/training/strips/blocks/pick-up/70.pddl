
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-8-0)
    (:domain BLOCKS)

    (:objects
        a b c d e f g h - object
    )

    (:init
        (clear a)
        (clear d)
        (clear b)
        (clear c)
        (ontable e)
        (ontable b)
        (ontable f)
        (ontable c)
        (on a g)
        (on g e)
        (on h f)
        (on d h)
        (handempty )
    )

    (:goal
        (and (clear a) (clear d) (clear b) (ontable e) (ontable b) (ontable f) (on a g) (on g e) (on h f) (on d h) (holding c))
    )

    
    
    
)
