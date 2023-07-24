
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
        (clear d)
        (clear h)
        (clear j)
        (ontable i)
        (ontable e)
        (ontable f)
        (ontable h)
        (on b a)
        (on g i)
        (on c f)
        (on d c)
        (on a g)
        (on j e)
        (handempty )
    )

    (:goal
        (and (clear j) (clear d) (clear b) (ontable e) (ontable i) (ontable f) (on b a) (on g i) (on c f) (on d c) (on a g) (on j e) (holding h))
    )

    
    
    
)
