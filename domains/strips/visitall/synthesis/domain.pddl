(define (domain visitall)
  (:requirements :typing :strips :negative-preconditions)
  (:types row column - object)
  (:predicates
    (at_row ?r - row)
    (at_column ?c - column)
    (connected_rows ?r1 ?r2 - row)
    (connected_columns ?c1 ?c2 - column)
    (visited ?r - row ?c - column))

  (:action up
    :parameters (?from ?to - row)
    :precondition (and (connected_rows ?from ?to)(at_row ?from)(not (at_row ?to)))
    :effect (and (at_row ?to)(not (at_row ?from))))

  (:action down
    :parameters (?from ?to - row)
    :precondition (and (connected_rows ?to ?from)(at_row ?from)(not (at_row ?to)))
    :effect (and (at_row ?to)(not (at_row ?from))))

  (:action left
    :parameters (?from ?to - column)
    :precondition (and (connected_columns ?to ?from)(at_column ?from)(not (at_column ?to)))
    :effect (and (at_column ?to)(not (at_column ?from))))

  (:action right
    :parameters (?from ?to - column)
    :precondition (and (connected_columns ?from ?to)(at_column ?from)(not (at_column ?to)))
    :effect (and (at_column ?to)(not (at_column ?from))))

  (:action visit
    :parameters (?r - row ?c - column)
    :precondition (and (at_row ?r)(at_column ?c)(not (visited ?r ?c)) )
    :effect (and (visited ?r ?c))))

