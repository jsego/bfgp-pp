
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-12-0)
    (:domain BLOCKS)

    (:objects
        a b c d e f g h i j k l - object
    )

    (:init
        (clear l)
        (clear f)
        (ontable l)
        (ontable c)
        (on i c)
        (on a g)
        (on k e)
        (on f h)
        (on b d)
        (on d i)
        (on g k)
        (on e b)
        (on h a)
        (holding j)
    )

    (:goal
        (and (clear l) (clear j) (ontable l) (ontable c) (on i c) (on a g) (on k e) (on f h) (on b d) (on d i) (on g k) (on e b) (on j f) (on h a) (handempty ))
    )

    
    
    
)

