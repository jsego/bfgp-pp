
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
        (clear d)
        (clear g)
        (clear e)
        (ontable i)
        (ontable b)
        (ontable c)
        (on k a)
        (on f i)
        (on d c)
        (on j b)
        (on g h)
        (on e j)
        (on h k)
        (on a f)
        (handempty )
    )

    (:goal
        (and (clear j) (clear g) (clear d) (ontable i) (ontable b) (ontable c) (on h k) (on k a) (on f i) (on d c) (on g h) (on j b) (on a f) (holding e))
    )

    
    
    
)

