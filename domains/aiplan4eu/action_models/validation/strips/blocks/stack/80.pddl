
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
        (clear i)
        (clear e)
        (clear l)
        (ontable g)
        (ontable d)
        (ontable b)
        (on i c)
        (on f a)
        (on k f)
        (on e k)
        (on h g)
        (on l d)
        (on a h)
        (on c b)
        (holding j)
    )

    (:goal
        (and (clear l) (clear i) (clear j) (ontable g) (ontable d) (ontable b) (on i c) (on j e) (on f a) (on k f) (on e k) (on h g) (on l d) (on a h) (on c b) (handempty ))
    )

    
    
    
)

