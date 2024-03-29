
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-10-0)
    (:domain BLOCKS)

    (:objects
        a b c d e f g h i j - object
    )

    (:init
        (clear f)
        (clear c)
        (ontable i)
        (ontable f)
        (on c e)
        (on d i)
        (on a d)
        (on g h)
        (on b g)
        (on e j)
        (on j b)
        (on h a)
        (handempty )
    )

    (:goal
        (and (clear c) (ontable i) (on c e) (on d i) (on a d) (on b g) (on g h) (on e j) (on j b) (on h a) (holding f))
    )

    
    
    
)

