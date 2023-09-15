
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
        (clear b)
        (clear c)
        (clear e)
        (clear l)
        (ontable h)
        (ontable e)
        (ontable l)
        (ontable n)
        (on d m)
        (on b j)
        (on i n)
        (on k g)
        (on m a)
        (on c k)
        (on a h)
        (on g d)
        (on j i)
        (holding f)
    )

    (:goal
        (and (clear c) (clear e) (clear f) (clear l) (ontable l) (ontable e) (ontable n) (ontable h) (on f b) (on d m) (on b j) (on k g) (on m a) (on g d) (on c k) (on a h) (on i n) (on j i) (handempty ))
    )

    
    
    
)
