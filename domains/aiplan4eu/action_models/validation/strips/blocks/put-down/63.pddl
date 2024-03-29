
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
        (clear i)
        (clear f)
        (ontable g)
        (ontable k)
        (ontable c)
        (on i c)
        (on j e)
        (on f a)
        (on d j)
        (on e k)
        (on h g)
        (on l d)
        (on a h)
        (holding b)
    )

    (:goal
        (and (clear l) (clear i) (clear b) (clear f) (ontable g) (ontable b) (ontable k) (ontable c) (on i c) (on j e) (on f a) (on d j) (on e k) (on h g) (on l d) (on a h) (handempty ))
    )

    
    
    
)

