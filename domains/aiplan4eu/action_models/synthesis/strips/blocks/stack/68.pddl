
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
        (clear b)
        (clear a)
        (ontable g)
        (ontable e)
        (on a g)
        (on b c)
        (on f e)
        (on c f)
        (holding d)
    )

    (:goal
        (and (clear d) (clear a) (ontable g) (ontable e) (on a g) (on d b) (on b c) (on f e) (on c f) (handempty ))
    )

    
    
    
)
