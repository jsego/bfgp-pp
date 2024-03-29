
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem BLOCKS-13-0)
    (:domain BLOCKS)

    (:objects
        a b c d e f g h i j k l m - object
    )

    (:init
        (clear d)
        (clear m)
        (clear b)
        (clear j)
        (clear i)
        (ontable m)
        (ontable b)
        (ontable f)
        (ontable g)
        (ontable k)
        (on i g)
        (on l k)
        (on d f)
        (on j a)
        (on e h)
        (on a e)
        (on h l)
        (holding c)
    )

    (:goal
        (and (clear b) (clear m) (clear c) (clear j) (clear i) (ontable m) (ontable b) (ontable f) (ontable g) (ontable k) (on i g) (on l k) (on c d) (on d f) (on j a) (on e h) (on a e) (on h l) (handempty ))
    )

    
    
    
)

