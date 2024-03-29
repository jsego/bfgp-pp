(define (problem visitall_2)
  (:domain visitall)
  (:objects r1 r2 r3 - row c1 c2 c3 - column)
  (:init (at_row r1)(at_column c1)(visited r1 c1)
    (adjacent_rows r1 r2)    
(adjacent_rows r2 r3)
    (adjacent_columns c1 c2)    
(adjacent_columns c2 c3))
  (:goal (and 
    (visited r1 c1)
    (visited r1 c2)
    (visited r1 c3)
    (visited r2 c1)
    (visited r2 c2)
    (visited r2 c3)
    (visited r3 c1)
    (visited r3 c2)
    (visited r3 c3))))
