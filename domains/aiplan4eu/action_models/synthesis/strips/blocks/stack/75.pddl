
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
        (clear a)
        (clear c)
        (ontable e)
        (ontable b)
        (ontable h)
        (on g e)
        (on a g)
        (on d h)
        (on c b)
        (holding f)
    )

    (:goal
        (and (clear d) (clear f) (clear c) (ontable e) (ontable b) (ontable h) (on g e) (on a g) (on f a) (on d h) (on c b) (handempty ))
    )

    
    
    
)

