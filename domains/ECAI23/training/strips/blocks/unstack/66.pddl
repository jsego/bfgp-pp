
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
        (clear g)
        (clear e)
        (clear b)
        (ontable d)
        (ontable g)
        (ontable e)
        (ontable b)
        (on a f)
        (on f c)
        (on c d)
        (handempty )
    )

    (:goal
        (and (clear b) (clear g) (clear e) (clear f) (ontable d) (ontable g) (ontable e) (ontable b) (on f c) (on c d) (holding a))
    )

    
    
    
)
