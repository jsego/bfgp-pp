(define (problem visitall_5)
  (:domain visitall)
  (:objects r1 r2 r3 r4 r5 r6 - row c1 c2 c3 c4 c5 c6 - column)
  (:init (at_row r1)(at_column c1)(visited r1 c1)
    (adjacent_rows r1 r2)    
(adjacent_rows r2 r3)    
(adjacent_rows r3 r4)    
(adjacent_rows r4 r5)    
(adjacent_rows r5 r6)
    (adjacent_columns c1 c2)    
(adjacent_columns c2 c3)    
(adjacent_columns c3 c4)    
(adjacent_columns c4 c5)    
(adjacent_columns c5 c6))
  (:goal (and 
    (visited r1 c1)
    (visited r1 c2)
    (visited r1 c3)
    (visited r1 c4)
    (visited r1 c5)
    (visited r1 c6)
    (visited r2 c1)
    (visited r2 c2)
    (visited r2 c3)
    (visited r2 c4)
    (visited r2 c5)
    (visited r2 c6)
    (visited r3 c1)
    (visited r3 c2)
    (visited r3 c3)
    (visited r3 c4)
    (visited r3 c5)
    (visited r3 c6)
    (visited r4 c1)
    (visited r4 c2)
    (visited r4 c3)
    (visited r4 c4)
    (visited r4 c5)
    (visited r4 c6)
    (visited r5 c1)
    (visited r5 c2)
    (visited r5 c3)
    (visited r5 c4)
    (visited r5 c5)
    (visited r5 c6)
    (visited r6 c1)
    (visited r6 c2)
    (visited r6 c3)
    (visited r6 c4)
    (visited r6 c5)
    (visited r6 c6))))
