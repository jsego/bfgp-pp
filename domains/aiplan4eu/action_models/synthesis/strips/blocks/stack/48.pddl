
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-6-0)
    (:domain BLOCKS)

    (:objects
        a b c d e f - object
    )

    (:init
        (clear a)
        (clear c)
        (ontable d)
        (ontable c)
        (on a e)
        (on f d)
        (on e f)
        (holding b)
    )

    (:goal
        (and (clear b) (clear c) (ontable d) (ontable c) (on b a) (on a e) (on f d) (on e f) (handempty ))
    )

    
    
    
)

