
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
        (clear d)
        (clear b)
        (clear c)
        (ontable e)
        (ontable d)
        (ontable c)
        (on b e)
        (holding a)
    )

    (:goal
        (and (clear b) (clear a) (clear c) (ontable d) (ontable e) (ontable c) (on a d) (on b e) (handempty ))
    )

    
    
    
)

