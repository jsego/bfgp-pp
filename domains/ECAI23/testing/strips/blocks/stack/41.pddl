
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
        (clear a)
        (clear b)
        (clear k)
        (clear f)
        (ontable c)
        (ontable k)
        (ontable d)
        (ontable h)
        (on e g)
        (on j d)
        (on b h)
        (on g c)
        (on f e)
        (on a j)
        (holding i)
    )

    (:goal
        (and (clear a) (clear b) (clear k) (clear i) (ontable k) (ontable d) (ontable h) (ontable c) (on e g) (on i f) (on j d) (on b h) (on g c) (on f e) (on a j) (handempty ))
    )

    
    
    
)
