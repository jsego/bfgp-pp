
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
        (clear b)
        (ontable e)
        (ontable c)
        (on g e)
        (on a g)
        (on h f)
        (on f a)
        (on b c)
        (on d h)
        (handempty )
    )

    (:goal
        (and (clear b) (clear h) (ontable e) (ontable c) (on g e) (on a g) (on h f) (on f a) (on b c) (holding d))
    )

    
    
    
)

