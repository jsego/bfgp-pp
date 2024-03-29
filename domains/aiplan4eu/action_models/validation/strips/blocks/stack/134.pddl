
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
        (clear h)
        (clear j)
        (clear f)
        (clear g)
        (ontable e)
        (ontable k)
        (ontable n)
        (ontable c)
        (on d i)
        (on a d)
        (on j k)
        (on b e)
        (on g c)
        (on l b)
        (on i n)
        (on f l)
        (on h a)
        (holding m)
    )

    (:goal
        (and (clear m) (clear h) (clear j) (clear g) (ontable e) (ontable k) (ontable n) (ontable c) (on d i) (on a d) (on j k) (on g c) (on b e) (on l b) (on i n) (on f l) (on m f) (on h a) (handempty ))
    )

    
    
    
)

