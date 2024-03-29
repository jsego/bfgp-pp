
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
        (clear b)
        (clear a)
        (clear j)
        (clear g)
        (clear l)
        (clear k)
        (ontable c)
        (ontable j)
        (ontable h)
        (ontable f)
        (ontable g)
        (ontable k)
        (on i c)
        (on b d)
        (on d i)
        (on l f)
        (on a h)
        (holding e)
    )

    (:goal
        (and (clear b) (clear a) (clear j) (clear e) (clear g) (clear l) (ontable h) (ontable j) (ontable c) (ontable f) (ontable g) (ontable k) (on i c) (on b d) (on d i) (on e k) (on l f) (on a h) (handempty ))
    )

    
    
    
)

