
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem hanoi-7)
    (:domain hanoi)

    (:objects
        d1 d2 d3 d4 d5 d6 d7 peg1 peg2 peg3 - object
    )

    (:init
        (smaller peg3 d4)
        (smaller d7 d4)
        (smaller peg3 d3)
        (smaller d7 d3)
        (smaller peg2 d2)
        (smaller d6 d4)
        (smaller d4 d2)
        (smaller d3 d3)
        (smaller peg3 d1)
        (smaller d7 d1)
        (smaller d6 d3)
        (smaller peg3 d6)
        (smaller d3 d1)
        (smaller d7 d6)
        (smaller peg1 d7)
        (smaller d6 d1)
        (smaller peg2 d7)
        (smaller peg3 d5)
        (smaller d6 d6)
        (smaller peg3 d2)
        (smaller d7 d5)
        (smaller d1 d1)
        (smaller d7 d2)
        (smaller d6 d5)
        (smaller peg1 d4)
        (smaller d2 d1)
        (smaller peg1 d3)
        (smaller d3 d2)
        (smaller d5 d4)
        (smaller d6 d2)
        (smaller d5 d3)
        (smaller peg2 d4)
        (smaller d5 d1)
        (smaller peg1 d1)
        (smaller peg2 d3)
        (smaller peg3 d7)
        (smaller peg1 d6)
        (smaller d4 d4)
        (smaller peg2 d1)
        (smaller d4 d3)
        (smaller d2 d2)
        (smaller peg1 d5)
        (smaller peg2 d6)
        (smaller d5 d5)
        (smaller d4 d1)
        (smaller d5 d2)
        (smaller peg1 d2)
        (smaller peg2 d5)
        (clear d7)
        (clear peg1)
        (clear peg3)
        (on d4 d4)
        (on d2 d2)
        (on d7 peg2)
        (on d6 d6)
        (on d5 d5)
        (on d3 d3)
        (on d1 d1)
    )

    (:goal
        (and (smaller peg3 d4) (smaller d7 d4) (smaller peg3 d3) (smaller d7 d3) (smaller peg2 d2) (smaller d6 d4) (smaller d4 d2) (smaller d3 d3) (smaller peg3 d1) (smaller d7 d1) (smaller d6 d3) (smaller peg3 d6) (smaller d3 d1) (smaller d7 d6) (smaller peg1 d7) (smaller d6 d1) (smaller peg2 d7) (smaller peg3 d5) (smaller d6 d6) (smaller peg3 d2) (smaller d7 d5) (smaller d1 d1) (smaller d7 d2) (smaller d6 d5) (smaller peg1 d4) (smaller d2 d1) (smaller peg1 d3) (smaller d3 d2) (smaller d5 d4) (smaller d6 d2) (smaller d5 d3) (smaller peg2 d4) (smaller d5 d1) (smaller peg1 d1) (smaller peg2 d3) (smaller peg3 d7) (smaller peg1 d6) (smaller d4 d4) (smaller peg2 d1) (smaller d4 d3) (smaller d2 d2) (smaller peg1 d5) (smaller peg2 d6) (smaller d5 d5) (smaller d4 d1) (smaller d5 d2) (smaller peg1 d2) (smaller peg2 d5) (clear peg2) (clear peg3) (clear d7) (on d4 d4) (on d2 d2) (on d6 d6) (on d5 d5) (on d3 d3) (on d7 peg1) (on d1 d1))
    )

    
    
    
)
