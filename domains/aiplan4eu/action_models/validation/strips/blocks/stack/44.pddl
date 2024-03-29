
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
        (clear k)
        (clear a)
        (ontable c)
        (ontable d)
        (ontable b)
        (on i f)
        (on e g)
        (on k i)
        (on f e)
        (on g c)
        (on a j)
        (on j d)
        (holding h)
    )

    (:goal
        (and (clear b) (clear a) (clear h) (ontable d) (ontable b) (ontable c) (on i f) (on e g) (on k i) (on f e) (on g c) (on a j) (on j d) (on h k) (handempty ))
    )

    
    
    
)

