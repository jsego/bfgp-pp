
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
        (clear c)
        (clear b)
        (clear f)
        (clear h)
        (ontable e)
        (ontable b)
        (ontable f)
        (ontable h)
        (on c a)
        (on g e)
        (on a g)
        (holding d)
    )

    (:goal
        (and (clear d) (clear b) (clear c) (clear f) (ontable e) (ontable b) (ontable f) (ontable h) (on c a) (on g e) (on a g) (on d h) (handempty ))
    )

    
    
    
)

