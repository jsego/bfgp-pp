
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-11-0)
    (:domain BLOCKS)

    (:objects
        a b c d e f g h i j k - object
    )

    (:init
        (clear h)
        (clear j)
        (clear e)
        (clear g)
        (ontable d)
        (ontable c)
        (ontable i)
        (ontable e)
        (on k a)
        (on f i)
        (on g c)
        (on j d)
        (on h k)
        (on a f)
        (holding b)
    )

    (:goal
        (and (clear b) (clear j) (clear e) (clear g) (ontable e) (ontable i) (ontable d) (ontable c) (on k a) (on f i) (on b h) (on g c) (on j d) (on h k) (on a f) (handempty ))
    )

    
    
    
)
