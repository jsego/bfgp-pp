
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
        (clear b)
        (clear c)
        (clear e)
        (clear g)
        (ontable h)
        (ontable j)
        (ontable i)
        (ontable f)
        (ontable g)
        (on c j)
        (on d i)
        (on b f)
        (on e h)
        (holding a)
    )

    (:goal
        (and (clear b) (clear a) (clear c) (clear e) (clear g) (ontable h) (ontable j) (ontable i) (ontable f) (ontable g) (on c j) (on d i) (on b f) (on a d) (on e h) (handempty ))
    )

    
    
    
)

