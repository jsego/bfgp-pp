
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
        (clear c)
        (clear j)
        (clear g)
        (ontable d)
        (ontable b)
        (ontable f)
        (ontable k)
        (on i f)
        (on l k)
        (on m i)
        (on c m)
        (on j a)
        (on e h)
        (on g b)
        (on a e)
        (on h l)
        (handempty )
    )

    (:goal
        (and (clear j) (clear g) (clear c) (ontable b) (ontable f) (ontable k) (on i f) (on l k) (on m i) (on a e) (on j a) (on e h) (on g b) (on c m) (on h l) (holding d))
    )

    
    
    
)

