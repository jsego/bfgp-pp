
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
        (clear h)
        (clear c)
        (clear e)
        (clear g)
        (ontable b)
        (ontable h)
        (ontable c)
        (ontable e)
        (ontable f)
        (on g b)
        (on d f)
        (holding a)
    )

    (:goal
        (and (clear d) (clear a) (clear c) (clear h) (clear e) (ontable b) (ontable c) (ontable h) (ontable e) (ontable f) (on a g) (on g b) (on d f) (handempty ))
    )

    
    
    
)

