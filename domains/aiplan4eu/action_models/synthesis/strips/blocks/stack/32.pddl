
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-5-0)
    (:domain BLOCKS)

    (:objects
        a b c d e - object
    )

    (:init
        (clear b)
        (clear a)
        (ontable a)
        (ontable c)
        (on d c)
        (on b d)
        (holding e)
    )

    (:goal
        (and (clear e) (clear a) (ontable a) (ontable c) (on e b) (on d c) (on b d) (handempty ))
    )

    
    
    
)

