
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Instance file automatically generated by the Tarski FSTRIPS writer
;;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (problem transport-two-cities-sequential-15nodes-1000size-3degree-100mindistance-3trucks-5packages-2014seed)
    (:domain transport)

    (:objects
        capacity-0 capacity-1 capacity-2 capacity-3 capacity-4 - capacity-number
        city-1-loc-1 city-1-loc-10 city-1-loc-11 city-1-loc-12 city-1-loc-13 city-1-loc-14 city-1-loc-15 city-1-loc-2 city-1-loc-3 city-1-loc-4 city-1-loc-5 city-1-loc-6 city-1-loc-7 city-1-loc-8 city-1-loc-9 city-2-loc-1 city-2-loc-10 city-2-loc-11 city-2-loc-12 city-2-loc-13 city-2-loc-14 city-2-loc-15 city-2-loc-2 city-2-loc-3 city-2-loc-4 city-2-loc-5 city-2-loc-6 city-2-loc-7 city-2-loc-8 city-2-loc-9 - location
        package-1 package-2 package-3 package-4 package-5 - package
        truck-1 truck-2 truck-3 - vehicle
    )

    (:init
        (= (total-cost ) 0.0)
        (= (road-length city-1-loc-5 city-1-loc-2) 30.0)
        (= (road-length city-1-loc-2 city-1-loc-5) 30.0)
        (= (road-length city-1-loc-6 city-1-loc-2) 11.0)
        (= (road-length city-1-loc-2 city-1-loc-6) 11.0)
        (= (road-length city-1-loc-6 city-1-loc-5) 20.0)
        (= (road-length city-1-loc-5 city-1-loc-6) 20.0)
        (= (road-length city-1-loc-7 city-1-loc-1) 13.0)
        (= (road-length city-1-loc-1 city-1-loc-7) 13.0)
        (= (road-length city-1-loc-9 city-1-loc-1) 28.0)
        (= (road-length city-1-loc-1 city-1-loc-9) 28.0)
        (= (road-length city-1-loc-9 city-1-loc-3) 29.0)
        (= (road-length city-1-loc-3 city-1-loc-9) 29.0)
        (= (road-length city-1-loc-10 city-1-loc-5) 15.0)
        (= (road-length city-1-loc-5 city-1-loc-10) 15.0)
        (= (road-length city-1-loc-10 city-1-loc-7) 25.0)
        (= (road-length city-1-loc-7 city-1-loc-10) 25.0)
        (= (road-length city-1-loc-10 city-1-loc-9) 26.0)
        (= (road-length city-1-loc-9 city-1-loc-10) 26.0)
        (= (road-length city-1-loc-11 city-1-loc-2) 15.0)
        (= (road-length city-1-loc-2 city-1-loc-11) 15.0)
        (= (road-length city-1-loc-11 city-1-loc-6) 25.0)
        (= (road-length city-1-loc-6 city-1-loc-11) 25.0)
        (= (road-length city-1-loc-12 city-1-loc-1) 22.0)
        (= (road-length city-1-loc-1 city-1-loc-12) 22.0)
        (= (road-length city-1-loc-12 city-1-loc-7) 22.0)
        (= (road-length city-1-loc-7 city-1-loc-12) 22.0)
        (= (road-length city-1-loc-13 city-1-loc-4) 20.0)
        (= (road-length city-1-loc-4 city-1-loc-13) 20.0)
        (= (road-length city-1-loc-13 city-1-loc-5) 28.0)
        (= (road-length city-1-loc-5 city-1-loc-13) 28.0)
        (= (road-length city-1-loc-13 city-1-loc-8) 28.0)
        (= (road-length city-1-loc-8 city-1-loc-13) 28.0)
        (= (road-length city-1-loc-14 city-1-loc-3) 14.0)
        (= (road-length city-1-loc-3 city-1-loc-14) 14.0)
        (= (road-length city-1-loc-14 city-1-loc-9) 18.0)
        (= (road-length city-1-loc-9 city-1-loc-14) 18.0)
        (= (road-length city-1-loc-15 city-1-loc-2) 19.0)
        (= (road-length city-1-loc-2 city-1-loc-15) 19.0)
        (= (road-length city-1-loc-15 city-1-loc-5) 31.0)
        (= (road-length city-1-loc-5 city-1-loc-15) 31.0)
        (= (road-length city-1-loc-15 city-1-loc-6) 23.0)
        (= (road-length city-1-loc-6 city-1-loc-15) 23.0)
        (= (road-length city-1-loc-15 city-1-loc-11) 24.0)
        (= (road-length city-1-loc-11 city-1-loc-15) 24.0)
        (= (road-length city-2-loc-3 city-2-loc-1) 23.0)
        (= (road-length city-2-loc-1 city-2-loc-3) 23.0)
        (= (road-length city-2-loc-4 city-2-loc-3) 29.0)
        (= (road-length city-2-loc-3 city-2-loc-4) 29.0)
        (= (road-length city-2-loc-8 city-2-loc-6) 22.0)
        (= (road-length city-2-loc-6 city-2-loc-8) 22.0)
        (= (road-length city-2-loc-9 city-2-loc-2) 19.0)
        (= (road-length city-2-loc-2 city-2-loc-9) 19.0)
        (= (road-length city-2-loc-9 city-2-loc-7) 16.0)
        (= (road-length city-2-loc-7 city-2-loc-9) 16.0)
        (= (road-length city-2-loc-10 city-2-loc-2) 30.0)
        (= (road-length city-2-loc-2 city-2-loc-10) 30.0)
        (= (road-length city-2-loc-10 city-2-loc-7) 29.0)
        (= (road-length city-2-loc-7 city-2-loc-10) 29.0)
        (= (road-length city-2-loc-10 city-2-loc-9) 19.0)
        (= (road-length city-2-loc-9 city-2-loc-10) 19.0)
        (= (road-length city-2-loc-11 city-2-loc-6) 17.0)
        (= (road-length city-2-loc-6 city-2-loc-11) 17.0)
        (= (road-length city-2-loc-11 city-2-loc-7) 25.0)
        (= (road-length city-2-loc-7 city-2-loc-11) 25.0)
        (= (road-length city-2-loc-11 city-2-loc-8) 27.0)
        (= (road-length city-2-loc-8 city-2-loc-11) 27.0)
        (= (road-length city-2-loc-12 city-2-loc-2) 13.0)
        (= (road-length city-2-loc-2 city-2-loc-12) 13.0)
        (= (road-length city-2-loc-12 city-2-loc-7) 27.0)
        (= (road-length city-2-loc-7 city-2-loc-12) 27.0)
        (= (road-length city-2-loc-12 city-2-loc-9) 12.0)
        (= (road-length city-2-loc-9 city-2-loc-12) 12.0)
        (= (road-length city-2-loc-12 city-2-loc-10) 18.0)
        (= (road-length city-2-loc-10 city-2-loc-12) 18.0)
        (= (road-length city-2-loc-13 city-2-loc-1) 26.0)
        (= (road-length city-2-loc-1 city-2-loc-13) 26.0)
        (= (road-length city-2-loc-13 city-2-loc-3) 29.0)
        (= (road-length city-2-loc-3 city-2-loc-13) 29.0)
        (= (road-length city-2-loc-13 city-2-loc-5) 26.0)
        (= (road-length city-2-loc-5 city-2-loc-13) 26.0)
        (= (road-length city-2-loc-13 city-2-loc-7) 28.0)
        (= (road-length city-2-loc-7 city-2-loc-13) 28.0)
        (= (road-length city-2-loc-14 city-2-loc-6) 15.0)
        (= (road-length city-2-loc-6 city-2-loc-14) 15.0)
        (= (road-length city-2-loc-14 city-2-loc-8) 13.0)
        (= (road-length city-2-loc-8 city-2-loc-14) 13.0)
        (= (road-length city-2-loc-14 city-2-loc-11) 15.0)
        (= (road-length city-2-loc-11 city-2-loc-14) 15.0)
        (= (road-length city-2-loc-15 city-2-loc-2) 20.0)
        (= (road-length city-2-loc-2 city-2-loc-15) 20.0)
        (= (road-length city-2-loc-15 city-2-loc-4) 18.0)
        (= (road-length city-2-loc-4 city-2-loc-15) 18.0)
        (= (road-length city-1-loc-3 city-2-loc-5) 127.0)
        (= (road-length city-2-loc-5 city-1-loc-3) 127.0)
        (capacity-predecessor capacity-0 capacity-1)
        (capacity-predecessor capacity-2 capacity-3)
        (capacity-predecessor capacity-1 capacity-2)
        (capacity-predecessor capacity-3 capacity-4)
        (road city-2-loc-5 city-1-loc-3)
        (road city-1-loc-5 city-1-loc-2)
        (road city-2-loc-11 city-2-loc-7)
        (road city-2-loc-13 city-2-loc-5)
        (road city-2-loc-9 city-2-loc-12)
        (road city-2-loc-14 city-2-loc-6)
        (road city-2-loc-3 city-2-loc-1)
        (road city-2-loc-8 city-2-loc-11)
        (road city-1-loc-10 city-1-loc-5)
        (road city-2-loc-4 city-2-loc-15)
        (road city-1-loc-3 city-2-loc-5)
        (road city-1-loc-7 city-1-loc-1)
        (road city-2-loc-11 city-2-loc-14)
        (road city-1-loc-5 city-1-loc-6)
        (road city-2-loc-11 city-2-loc-8)
        (road city-2-loc-9 city-2-loc-2)
        (road city-2-loc-2 city-2-loc-12)
        (road city-2-loc-14 city-2-loc-11)
        (road city-2-loc-12 city-2-loc-9)
        (road city-2-loc-2 city-2-loc-9)
        (road city-1-loc-7 city-1-loc-12)
        (road city-2-loc-15 city-2-loc-4)
        (road city-2-loc-13 city-2-loc-3)
        (road city-2-loc-3 city-2-loc-4)
        (road city-1-loc-2 city-1-loc-15)
        (road city-2-loc-7 city-2-loc-10)
        (road city-1-loc-11 city-1-loc-15)
        (road city-2-loc-12 city-2-loc-2)
        (road city-2-loc-2 city-2-loc-15)
        (road city-1-loc-5 city-1-loc-10)
        (road city-2-loc-13 city-2-loc-1)
        (road city-2-loc-13 city-2-loc-7)
        (road city-1-loc-14 city-1-loc-9)
        (road city-2-loc-10 city-2-loc-12)
        (road city-2-loc-6 city-2-loc-11)
        (road city-1-loc-14 city-1-loc-3)
        (road city-2-loc-1 city-2-loc-13)
        (road city-2-loc-5 city-2-loc-13)
        (road city-1-loc-9 city-1-loc-14)
        (road city-2-loc-10 city-2-loc-9)
        (road city-1-loc-6 city-1-loc-15)
        (road city-1-loc-13 city-1-loc-5)
        (road city-1-loc-15 city-1-loc-2)
        (road city-1-loc-3 city-1-loc-14)
        (road city-1-loc-9 city-1-loc-3)
        (road city-2-loc-4 city-2-loc-3)
        (road city-1-loc-3 city-1-loc-9)
        (road city-1-loc-5 city-1-loc-15)
        (road city-1-loc-13 city-1-loc-8)
        (road city-2-loc-8 city-2-loc-14)
        (road city-2-loc-10 city-2-loc-2)
        (road city-1-loc-15 city-1-loc-11)
        (road city-1-loc-11 city-1-loc-2)
        (road city-1-loc-5 city-1-loc-13)
        (road city-2-loc-3 city-2-loc-13)
        (road city-1-loc-15 city-1-loc-5)
        (road city-1-loc-1 city-1-loc-7)
        (road city-1-loc-12 city-1-loc-7)
        (road city-2-loc-11 city-2-loc-6)
        (road city-1-loc-2 city-1-loc-11)
        (road city-2-loc-9 city-2-loc-10)
        (road city-2-loc-14 city-2-loc-8)
        (road city-2-loc-9 city-2-loc-7)
        (road city-2-loc-15 city-2-loc-2)
        (road city-1-loc-15 city-1-loc-6)
        (road city-1-loc-2 city-1-loc-5)
        (road city-1-loc-6 city-1-loc-2)
        (road city-1-loc-2 city-1-loc-6)
        (road city-1-loc-13 city-1-loc-4)
        (road city-1-loc-11 city-1-loc-6)
        (road city-1-loc-7 city-1-loc-10)
        (road city-2-loc-7 city-2-loc-12)
        (road city-2-loc-12 city-2-loc-10)
        (road city-2-loc-2 city-2-loc-10)
        (road city-2-loc-12 city-2-loc-7)
        (road city-1-loc-6 city-1-loc-11)
        (road city-1-loc-8 city-1-loc-13)
        (road city-1-loc-10 city-1-loc-7)
        (road city-1-loc-9 city-1-loc-10)
        (road city-2-loc-7 city-2-loc-13)
        (road city-2-loc-7 city-2-loc-11)
        (road city-2-loc-7 city-2-loc-9)
        (road city-1-loc-6 city-1-loc-5)
        (road city-1-loc-1 city-1-loc-9)
        (road city-2-loc-6 city-2-loc-14)
        (road city-1-loc-12 city-1-loc-1)
        (road city-2-loc-6 city-2-loc-8)
        (road city-2-loc-1 city-2-loc-3)
        (road city-1-loc-4 city-1-loc-13)
        (road city-1-loc-1 city-1-loc-12)
        (road city-1-loc-9 city-1-loc-1)
        (road city-2-loc-8 city-2-loc-6)
        (road city-2-loc-10 city-2-loc-7)
        (road city-1-loc-10 city-1-loc-9)
        (at package-4 city-1-loc-8)
        (at truck-1 city-2-loc-4)
        (at truck-3 city-2-loc-9)
        (at package-2 city-1-loc-11)
        (at package-5 city-1-loc-11)
        (at package-3 city-1-loc-12)
        (at package-1 city-1-loc-9)
        (at truck-2 city-2-loc-15)
        (capacity truck-3 capacity-3)
        (capacity truck-2 capacity-4)
        (capacity truck-1 capacity-3)
    )

    (:goal
        (and (capacity-predecessor capacity-0 capacity-1) (capacity-predecessor capacity-2 capacity-3) (capacity-predecessor capacity-1 capacity-2) (capacity-predecessor capacity-3 capacity-4) (road city-2-loc-5 city-1-loc-3) (road city-1-loc-5 city-1-loc-2) (road city-2-loc-11 city-2-loc-7) (road city-2-loc-13 city-2-loc-5) (road city-2-loc-9 city-2-loc-12) (road city-2-loc-14 city-2-loc-6) (road city-2-loc-3 city-2-loc-1) (road city-2-loc-8 city-2-loc-11) (road city-1-loc-10 city-1-loc-5) (road city-2-loc-4 city-2-loc-15) (road city-1-loc-3 city-2-loc-5) (road city-1-loc-7 city-1-loc-1) (road city-2-loc-11 city-2-loc-14) (road city-1-loc-5 city-1-loc-6) (road city-2-loc-11 city-2-loc-8) (road city-2-loc-9 city-2-loc-2) (road city-2-loc-2 city-2-loc-12) (road city-2-loc-14 city-2-loc-11) (road city-2-loc-12 city-2-loc-9) (road city-1-loc-7 city-1-loc-12) (road city-2-loc-2 city-2-loc-9) (road city-2-loc-15 city-2-loc-4) (road city-2-loc-13 city-2-loc-3) (road city-2-loc-3 city-2-loc-4) (road city-1-loc-2 city-1-loc-15) (road city-2-loc-7 city-2-loc-10) (road city-1-loc-11 city-1-loc-15) (road city-2-loc-12 city-2-loc-2) (road city-2-loc-2 city-2-loc-15) (road city-1-loc-5 city-1-loc-10) (road city-2-loc-13 city-2-loc-1) (road city-2-loc-13 city-2-loc-7) (road city-1-loc-14 city-1-loc-9) (road city-2-loc-10 city-2-loc-12) (road city-2-loc-6 city-2-loc-11) (road city-1-loc-14 city-1-loc-3) (road city-2-loc-1 city-2-loc-13) (road city-2-loc-5 city-2-loc-13) (road city-1-loc-9 city-1-loc-14) (road city-2-loc-10 city-2-loc-9) (road city-1-loc-6 city-1-loc-15) (road city-1-loc-13 city-1-loc-5) (road city-1-loc-15 city-1-loc-2) (road city-1-loc-3 city-1-loc-14) (road city-1-loc-9 city-1-loc-3) (road city-2-loc-4 city-2-loc-3) (road city-1-loc-3 city-1-loc-9) (road city-1-loc-5 city-1-loc-15) (road city-1-loc-13 city-1-loc-8) (road city-2-loc-8 city-2-loc-14) (road city-2-loc-10 city-2-loc-2) (road city-1-loc-15 city-1-loc-11) (road city-1-loc-11 city-1-loc-2) (road city-1-loc-5 city-1-loc-13) (road city-2-loc-3 city-2-loc-13) (road city-1-loc-15 city-1-loc-5) (road city-1-loc-1 city-1-loc-7) (road city-1-loc-12 city-1-loc-7) (road city-2-loc-11 city-2-loc-6) (road city-1-loc-2 city-1-loc-11) (road city-2-loc-9 city-2-loc-10) (road city-2-loc-14 city-2-loc-8) (road city-2-loc-9 city-2-loc-7) (road city-2-loc-15 city-2-loc-2) (road city-1-loc-15 city-1-loc-6) (road city-1-loc-2 city-1-loc-5) (road city-1-loc-6 city-1-loc-2) (road city-1-loc-2 city-1-loc-6) (road city-1-loc-13 city-1-loc-4) (road city-1-loc-11 city-1-loc-6) (road city-1-loc-7 city-1-loc-10) (road city-2-loc-7 city-2-loc-12) (road city-2-loc-12 city-2-loc-10) (road city-2-loc-2 city-2-loc-10) (road city-2-loc-12 city-2-loc-7) (road city-1-loc-6 city-1-loc-11) (road city-1-loc-8 city-1-loc-13) (road city-1-loc-10 city-1-loc-7) (road city-1-loc-9 city-1-loc-10) (road city-2-loc-7 city-2-loc-13) (road city-2-loc-7 city-2-loc-11) (road city-2-loc-7 city-2-loc-9) (road city-1-loc-6 city-1-loc-5) (road city-1-loc-1 city-1-loc-9) (road city-2-loc-6 city-2-loc-14) (road city-1-loc-12 city-1-loc-1) (road city-2-loc-6 city-2-loc-8) (road city-2-loc-1 city-2-loc-3) (road city-1-loc-4 city-1-loc-13) (road city-1-loc-1 city-1-loc-12) (road city-1-loc-9 city-1-loc-1) (road city-2-loc-8 city-2-loc-6) (road city-2-loc-10 city-2-loc-7) (road city-1-loc-10 city-1-loc-9) (at package-4 city-1-loc-8) (at truck-1 city-2-loc-4) (at package-2 city-1-loc-11) (at package-5 city-1-loc-11) (at truck-3 city-2-loc-7) (at package-3 city-1-loc-12) (at package-1 city-1-loc-9) (at truck-2 city-2-loc-15) (capacity truck-3 capacity-3) (capacity truck-2 capacity-4) (capacity truck-1 capacity-3))
    )

    
    
    (:metric minimize (total-cost ))
)

