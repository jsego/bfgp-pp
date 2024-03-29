
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
        (clear j)
        (clear b)
        (ontable d)
        (ontable c)
        (on i f)
        (on e g)
        (on k i)
        (on b h)
        (on f e)
        (on g c)
        (on j d)
        (on h k)
        (holding a)
    )

    (:goal
        (and (clear j) (clear b) (clear a) (ontable d) (ontable a) (ontable c) (on i f) (on e g) (on k i) (on b h) (on f e) (on g c) (on j d) (on h k) (handempty ))
    )

    
    
    
)

