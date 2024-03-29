
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
        (clear d)
        (clear e)
        (clear j)
        (clear h)
        (ontable j)
        (ontable i)
        (ontable e)
        (ontable f)
        (on a g)
        (on h b)
        (on b a)
        (on d c)
        (on g i)
        (on c f)
        (handempty )
    )

    (:goal
        (and (clear d) (clear h) (clear j) (ontable j) (ontable i) (ontable f) (on h b) (on a g) (on b a) (on d c) (on g i) (on c f) (holding e))
    )

    
    
    
)

