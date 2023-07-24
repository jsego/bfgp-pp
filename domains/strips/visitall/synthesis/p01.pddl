(define (problem visitall_2)
  (:domain visitall)
  (:objects 
    r1 r2 - row
    c1 c2 - column)
  (:init
    (at_row r1)
    (at_column c1)
    (connected_rows r1 r2)
    (connected_columns c1 c2)
  )
  (:goal (and
    (visited r1 c1)
    (visited r1 c2)
    (visited r2 c1)
    (visited r2 c2)
  )))
