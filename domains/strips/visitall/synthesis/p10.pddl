(define (problem visitall_11)
  (:domain visitall)
  (:objects 
    r1 r2 r3 r4 r5 r6 r7 r8 r9 r10 r11 - row
    c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 - column)
  (:init
    (at_row r1)
    (at_column c1)
    (connected_rows r1 r2)
    (connected_rows r2 r3)
    (connected_rows r3 r4)
    (connected_rows r4 r5)
    (connected_rows r5 r6)
    (connected_rows r6 r7)
    (connected_rows r7 r8)
    (connected_rows r8 r9)
    (connected_rows r9 r10)
    (connected_rows r10 r11)
    (connected_columns c1 c2)
    (connected_columns c2 c3)
    (connected_columns c3 c4)
    (connected_columns c4 c5)
    (connected_columns c5 c6)
    (connected_columns c6 c7)
    (connected_columns c7 c8)
    (connected_columns c8 c9)
    (connected_columns c9 c10)
    (connected_columns c10 c11)
  )
  (:goal (and
    (visited r1 c1)
    (visited r1 c2)
    (visited r1 c3)
    (visited r1 c4)
    (visited r1 c5)
    (visited r1 c6)
    (visited r1 c7)
    (visited r1 c8)
    (visited r1 c9)
    (visited r1 c10)
    (visited r1 c11)
    (visited r2 c1)
    (visited r2 c2)
    (visited r2 c3)
    (visited r2 c4)
    (visited r2 c5)
    (visited r2 c6)
    (visited r2 c7)
    (visited r2 c8)
    (visited r2 c9)
    (visited r2 c10)
    (visited r2 c11)
    (visited r3 c1)
    (visited r3 c2)
    (visited r3 c3)
    (visited r3 c4)
    (visited r3 c5)
    (visited r3 c6)
    (visited r3 c7)
    (visited r3 c8)
    (visited r3 c9)
    (visited r3 c10)
    (visited r3 c11)
    (visited r4 c1)
    (visited r4 c2)
    (visited r4 c3)
    (visited r4 c4)
    (visited r4 c5)
    (visited r4 c6)
    (visited r4 c7)
    (visited r4 c8)
    (visited r4 c9)
    (visited r4 c10)
    (visited r4 c11)
    (visited r5 c1)
    (visited r5 c2)
    (visited r5 c3)
    (visited r5 c4)
    (visited r5 c5)
    (visited r5 c6)
    (visited r5 c7)
    (visited r5 c8)
    (visited r5 c9)
    (visited r5 c10)
    (visited r5 c11)
    (visited r6 c1)
    (visited r6 c2)
    (visited r6 c3)
    (visited r6 c4)
    (visited r6 c5)
    (visited r6 c6)
    (visited r6 c7)
    (visited r6 c8)
    (visited r6 c9)
    (visited r6 c10)
    (visited r6 c11)
    (visited r7 c1)
    (visited r7 c2)
    (visited r7 c3)
    (visited r7 c4)
    (visited r7 c5)
    (visited r7 c6)
    (visited r7 c7)
    (visited r7 c8)
    (visited r7 c9)
    (visited r7 c10)
    (visited r7 c11)
    (visited r8 c1)
    (visited r8 c2)
    (visited r8 c3)
    (visited r8 c4)
    (visited r8 c5)
    (visited r8 c6)
    (visited r8 c7)
    (visited r8 c8)
    (visited r8 c9)
    (visited r8 c10)
    (visited r8 c11)
    (visited r9 c1)
    (visited r9 c2)
    (visited r9 c3)
    (visited r9 c4)
    (visited r9 c5)
    (visited r9 c6)
    (visited r9 c7)
    (visited r9 c8)
    (visited r9 c9)
    (visited r9 c10)
    (visited r9 c11)
    (visited r10 c1)
    (visited r10 c2)
    (visited r10 c3)
    (visited r10 c4)
    (visited r10 c5)
    (visited r10 c6)
    (visited r10 c7)
    (visited r10 c8)
    (visited r10 c9)
    (visited r10 c10)
    (visited r10 c11)
    (visited r11 c1)
    (visited r11 c2)
    (visited r11 c3)
    (visited r11 c4)
    (visited r11 c5)
    (visited r11 c6)
    (visited r11 c7)
    (visited r11 c8)
    (visited r11 c9)
    (visited r11 c10)
    (visited r11 c11)
  )))