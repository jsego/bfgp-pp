
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
        (clear b)
        (clear m)
        (clear c)
        (clear i)
        (clear f)
        (ontable m)
        (ontable b)
        (ontable f)
        (ontable g)
        (ontable k)
        (on c j)
        (on i g)
        (on l k)
        (on j a)
        (on e h)
        (on a e)
        (on h l)
        (holding d)
    )

    (:goal
        (and (clear m) (clear b) (clear d) (clear c) (clear i) (ontable m) (ontable b) (ontable f) (ontable g) (ontable k) (on c j) (on i g) (on l k) (on d f) (on j a) (on e h) (on a e) (on h l) (handempty ))
    )

    
    
    
)

