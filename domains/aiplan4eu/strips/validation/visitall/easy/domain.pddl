(define (domain visitall)
 (:requirements :strips :typing :negative-preconditions)
 (:types row column)
 (:predicates 
    (visited ?r - row ?c - column)
    (at_row ?r - row)
    (at_column ?c - column)
    (adjacent_rows ?r1 ?r2 - row)
    (adjacent_columns ?c1 ?c2 - column))
     
 (:action move_up
    :parameters (?from ?to - row ?c - column)
    :precondition (and (adjacent_rows ?from ?to) (at_row ?from) (not (at_row ?to))(at_column ?c))
    :effect (and (not (at_row ?from)) (at_row ?to)(visited ?to ?c)))
    
 (:action move_down
    :parameters (?from ?to - row ?c - column)
    :precondition (and (adjacent_rows ?to ?from) (at_row ?from) (not (at_row ?to))(at_column ?c))
    :effect (and (not (at_row ?from)) (at_row ?to)(visited ?to ?c)))

 (:action move_right
    :parameters (?from ?to - column ?r - row)
    :precondition (and (adjacent_columns ?from ?to) (at_column ?from) (not (at_column ?to))(at_row ?r))
    :effect (and (not (at_column ?from)) (at_column ?to)(visited ?r ?to)))
    
 (:action move_left
    :parameters (?from ?to - column ?r - row)
    :precondition (and (adjacent_columns ?to ?from) (at_column ?from) (not (at_column ?to))(at_row ?r))
    :effect (and (not (at_column ?from)) (at_column ?to)(visited ?r ?to))))
 
