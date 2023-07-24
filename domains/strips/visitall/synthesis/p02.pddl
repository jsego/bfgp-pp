(define (problem visitall_3)
  (:domain visitall)
  (:objects 
    r1 r2 r3 - row
    c1 c2 c3 - column)
  (:init
    (at_row r1)
    (at_column c1)
    (connected_rows r1 r2)
    (connected_rows r2 r3)
    (connected_columns c1 c2)
    (connected_columns c2 c3)
  )
  (:goal (and
    (visited r1 c1)
    (visited r1 c2)
    (visited r1 c3)
    (visited r2 c1)
    (visited r2 c2)
    (visited r2 c3)
    (visited r3 c1)
    (visited r3 c2)
    (visited r3 c3)
  )))
