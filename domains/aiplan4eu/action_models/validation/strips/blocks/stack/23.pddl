
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
        (clear j)
        (clear d)
        (clear c)
        (ontable i)
        (ontable d)
        (ontable c)
        (on h b)
        (on j e)
        (on a g)
        (on b a)
        (on g i)
        (on e h)
        (holding f)
    )

    (:goal
        (and (clear d) (clear f) (clear c) (ontable i) (ontable d) (ontable c) (on a g) (on j e) (on h b) (on b a) (on f j) (on g i) (on e h) (handempty ))
    )

    
    
    
)
