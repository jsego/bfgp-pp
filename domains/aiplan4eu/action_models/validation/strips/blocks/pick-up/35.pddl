
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-11-0)
    (:domain BLOCKS)

    (:objects
        a b c d e f g h i j k - object
    )

    (:init
        (clear b)
        (clear a)
        (clear i)
        (clear f)
        (clear k)
        (ontable d)
        (ontable h)
        (ontable c)
        (ontable i)
        (ontable k)
        (on e g)
        (on b h)
        (on f e)
        (on g c)
        (on a j)
        (on j d)
        (handempty )
    )

    (:goal
        (and (clear b) (clear a) (clear f) (clear k) (ontable d) (ontable c) (ontable h) (ontable k) (on e g) (on b h) (on f e) (on g c) (on a j) (on j d) (holding i))
    )

    
    
    
)

