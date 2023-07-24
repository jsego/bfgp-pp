
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
        (clear d)
        (clear e)
        (clear c)
        (ontable e)
        (ontable b)
        (ontable f)
        (on a g)
        (on g b)
        (on c a)
        (on d f)
        (holding h)
    )

    (:goal
        (and (clear d) (clear e) (clear h) (ontable e) (ontable b) (ontable f) (on a g) (on h c) (on c a) (on g b) (on d f) (handempty ))
    )

    
    
    
)
