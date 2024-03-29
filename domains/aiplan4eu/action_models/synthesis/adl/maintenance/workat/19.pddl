
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem maintenance-scheduling-1-3-10-10-2-1)
    (:domain maintenance-scheduling-domain)

    (:objects
        ber fra ham - airport
        d1 d10 d11 d2 d3 d4 d5 d6 d7 d8 d9 - day
        ap1 ap10 ap2 ap3 ap4 ap5 ap6 ap7 ap8 ap9 - plane
    )

    (:init
        (today d10)
        (today d5)
        (today d1)
        (today d6)
        (today d9)
        (today d8)
        (at ap4 d2 ham)
        (at ap9 d3 fra)
        (at ap10 d4 ham)
        (at ap4 d7 fra)
        (at ap5 d3 ham)
        (at ap2 d9 ham)
        (at ap6 d5 fra)
        (at ap3 d6 fra)
        (at ap3 d4 ber)
        (at ap6 d6 fra)
        (at ap1 d2 ham)
        (at ap8 d4 ham)
        (at ap7 d7 ham)
        (at ap7 d7 fra)
        (at ap8 d5 fra)
        (at ap1 d10 fra)
        (at ap10 d5 ham)
        (at ap2 d5 ber)
        (at ap5 d7 ber)
        (at ap9 d5 fra)
        (done ap5)
        (done ap3)
        (done ap7)
    )

    (:goal
        (and (today d10) (today d5) (today d1) (today d6) (today d8) (at ap4 d2 ham) (at ap9 d3 fra) (at ap10 d4 ham) (at ap9 d5 fra) (at ap4 d7 fra) (at ap5 d3 ham) (at ap2 d9 ham) (at ap6 d5 fra) (at ap3 d6 fra) (at ap3 d4 ber) (at ap6 d6 fra) (at ap1 d2 ham) (at ap8 d4 ham) (at ap7 d7 ham) (at ap8 d5 fra) (at ap1 d10 fra) (at ap10 d5 ham) (at ap2 d5 ber) (at ap5 d7 ber) (at ap7 d7 fra) (done ap5) (done ap3) (done ap7))
    )

    
    
    
)

