
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-14-0)
    (:domain BLOCKS)

    (:objects
        a b c d e f g h i j k l m n - object
    )

    (:init
        (clear a)
        (clear h)
        (clear f)
        (clear g)
        (ontable e)
        (ontable n)
        (ontable f)
        (ontable a)
        (on h m)
        (on k c)
        (on m k)
        (on d i)
        (on c l)
        (on g d)
        (on l b)
        (on b e)
        (on i n)
        (holding j)
    )

    (:goal
        (and (clear a) (clear h) (clear j) (clear f) (clear g) (ontable a) (ontable j) (ontable e) (ontable f) (ontable n) (on h m) (on k c) (on m k) (on i n) (on d i) (on c l) (on l b) (on b e) (on g d) (handempty ))
    )

    
    
    
)

