
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-13-0)
    (:domain BLOCKS)

    (:objects
        a b c d e f g h i j k l m - object
    )

    (:init
        (clear a)
        (clear e)
        (clear g)
        (clear l)
        (ontable e)
        (ontable f)
        (ontable m)
        (ontable k)
        (on i c)
        (on b k)
        (on c d)
        (on d f)
        (on a m)
        (on g i)
        (on l j)
        (on j b)
        (holding h)
    )

    (:goal
        (and (clear a) (clear h) (clear e) (clear g) (clear l) (ontable m) (ontable h) (ontable e) (ontable f) (ontable k) (on i c) (on b k) (on j b) (on d f) (on a m) (on g i) (on l j) (on c d) (handempty ))
    )

    
    
    
)

