
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-10-0)
    (:domain BLOCKS)

    (:objects
        a b c d e f g h i j - object
    )

    (:init
        (clear b)
        (clear c)
        (clear g)
        (clear e)
        (clear j)
        (ontable c)
        (ontable e)
        (ontable f)
        (ontable j)
        (ontable i)
        (on g h)
        (on h a)
        (on a d)
        (on b f)
        (on d i)
        (handempty )
    )

    (:goal
        (and (clear b) (clear c) (clear g) (clear e) (ontable c) (ontable e) (ontable f) (ontable i) (on g h) (on h a) (on a d) (on b f) (on d i) (holding j))
    )

    
    
    
)
