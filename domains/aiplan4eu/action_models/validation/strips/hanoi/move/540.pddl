
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem hanoi-8)
    (:domain hanoi)

    (:objects
        d1 d2 d3 d4 d5 d6 d7 d8 peg1 peg2 peg3 - object
    )

    (:init
        (smaller d8 d6)
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
        (smaller d8 d5)
        (smaller d6 d3)
        (smaller peg3 d6)
        (smaller d8 d2)
        (smaller peg1 d8)
        (smaller d3 d1)
        (smaller d7 d6)
        (smaller peg1 d7)
        (smaller d6 d1)
        (smaller peg2 d8)
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
        (smaller d8 d7)
        (smaller peg1 d3)
        (smaller d3 d2)
        (smaller d5 d4)
        (smaller d6 d2)
        (smaller d5 d3)
        (smaller peg2 d4)
        (smaller d5 d1)
        (smaller peg1 d1)
        (smaller peg2 d3)
        (smaller peg3 d8)
        (smaller peg3 d7)
        (smaller peg1 d6)
        (smaller d4 d4)
        (smaller d7 d7)
        (smaller peg2 d1)
        (smaller d4 d3)
        (smaller d8 d4)
        (smaller d2 d2)
        (smaller peg1 d5)
        (smaller peg2 d6)
        (smaller d8 d3)
        (smaller d5 d5)
        (smaller d4 d1)
        (smaller d8 d1)
        (smaller d5 d2)
        (smaller peg1 d2)
        (smaller peg2 d5)
        (clear d4)
        (clear d7)
        (clear d1)
        (on d1 d2)
        (on d7 d8)
        (on d4 d5)
        (on d8 peg3)
        (on d3 peg2)
        (on d2 d3)
        (on d6 peg1)
        (on d5 d6)
    )

    (:goal
        (and (smaller d8 d6) (smaller peg3 d4) (smaller d7 d4) (smaller peg3 d3) (smaller d7 d3) (smaller peg2 d2) (smaller d6 d4) (smaller d4 d2) (smaller d3 d3) (smaller peg3 d1) (smaller d7 d1) (smaller d8 d5) (smaller d6 d3) (smaller peg3 d6) (smaller d8 d2) (smaller peg1 d8) (smaller d3 d1) (smaller d7 d6) (smaller peg1 d7) (smaller d6 d1) (smaller peg2 d8) (smaller peg2 d7) (smaller peg3 d5) (smaller d6 d6) (smaller peg3 d2) (smaller d7 d5) (smaller d1 d1) (smaller d7 d2) (smaller d6 d5) (smaller peg1 d4) (smaller d2 d1) (smaller d8 d7) (smaller peg1 d3) (smaller d3 d2) (smaller d5 d4) (smaller d6 d2) (smaller d5 d3) (smaller peg2 d4) (smaller d5 d1) (smaller peg1 d1) (smaller peg2 d3) (smaller peg3 d8) (smaller peg3 d7) (smaller peg1 d6) (smaller d4 d4) (smaller d7 d7) (smaller peg2 d1) (smaller d4 d3) (smaller d8 d4) (smaller d2 d2) (smaller peg1 d5) (smaller peg2 d6) (smaller d8 d3) (smaller d5 d5) (smaller d4 d1) (smaller d8 d1) (smaller d5 d2) (smaller peg1 d2) (smaller peg2 d5) (clear d5) (clear d4) (clear d1) (on d1 d2) (on d7 d8) (on d4 d7) (on d8 peg3) (on d3 peg2) (on d2 d3) (on d6 peg1) (on d5 d6))
    )

    
    
    
)

