
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
        (clear f)
        (clear h)
        (clear j)
        (ontable j)
        (ontable f)
        (ontable c)
        (on i c)
        (on a g)
        (on k e)
        (on b d)
        (on d i)
        (on g k)
        (on e b)
        (on h a)
        (holding l)
    )

    (:goal
        (and (clear l) (clear f) (clear h) (ontable j) (ontable f) (ontable c) (on i c) (on a g) (on k e) (on b d) (on d i) (on g k) (on e b) (on l j) (on h a) (handempty ))
    )

    
    
    
)

