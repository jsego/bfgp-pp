
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
        (clear a)
        (clear l)
        (clear h)
        (clear j)
        (ontable a)
        (ontable f)
        (ontable j)
        (ontable c)
        (on h f)
        (on e b)
        (on l g)
        (on b d)
        (on i c)
        (on g k)
        (on k e)
        (on d i)
        (handempty )
    )

    (:goal
        (and (clear a) (clear g) (clear h) (clear j) (ontable a) (ontable f) (ontable j) (ontable c) (on h f) (on e b) (on b d) (on i c) (on g k) (on k e) (on d i) (holding l))
    )

    
    
    
)
