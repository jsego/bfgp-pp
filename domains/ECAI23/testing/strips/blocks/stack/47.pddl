
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
        (clear d)
        (ontable a)
        (ontable c)
        (on k i)
        (on e g)
        (on i f)
        (on d b)
        (on h k)
        (on g c)
        (on b h)
        (on f e)
        (holding j)
    )

    (:goal
        (and (clear a) (clear j) (ontable a) (ontable c) (on k i) (on e g) (on i f) (on d b) (on h k) (on j d) (on g c) (on b h) (on f e) (handempty ))
    )

    
    
    
)
