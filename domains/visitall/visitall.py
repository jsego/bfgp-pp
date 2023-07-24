#!/usr/bin/env python
# coding: utf-8

import sys
import argparse


def get_domain() -> str:
	return """(define (domain visitall)
  (:requirements :typing :strips :negative-preconditions)
  (:types row column - object)
  (:predicates
    (at_row ?r - row)
    (at_column ?c - column)
    (connected_rows ?r1 ?r2 - row)
    (connected_columns ?c1 ?c2 - column)
    (visited ?r - row ?c - column))\n
  (:action up
    :parameters (?from ?to - row)
    :precondition (and (connected_rows ?from ?to)(at_row ?from)(not (at_row ?to)))
    :effect (and (at_row ?to)(not (at_row ?from))))\n
  (:action down
    :parameters (?from ?to - row)
    :precondition (and (connected_rows ?to ?from)(at_row ?from)(not (at_row ?to)))
    :effect (and (at_row ?to)(not (at_row ?from))))\n
  (:action left
    :parameters (?from ?to - column)
    :precondition (and (connected_columns ?to ?from)(at_column ?from)(not (at_column ?to)))
    :effect (and (at_column ?to)(not (at_column ?from))))\n
  (:action right
    :parameters (?from ?to - column)
    :precondition (and (connected_columns ?from ?to)(at_column ?from)(not (at_column ?to)))
    :effect (and (at_column ?to)(not (at_column ?from))))\n
  (:action visit
    :parameters (?r - row ?c - column)
    :precondition (and (at_row ?r)(at_column ?c)(not (visited ?r ?c)) )
    :effect (and (visited ?r ?c))))\n
"""


def get_objects(size: int) -> str:
	rows = [f"r{idx}" for idx in range(1, size+1)]
	cols = [f"c{idx}" for idx in range(1, size+1)]
	return f"{' '.join(rows)} - row\n    {' '.join(cols)} - column"


def get_instance(size: int) -> str:
	conn_rows = [f"(connected_rows r{i} r{i+1})\n" for i in range(1, size)]
	conn_cols = [f"(connected_columns c{i} c{i+1})\n" for i in range(1, size)]
	visited = [f"(visited r{i} c{j})\n" for i in range(1, size+1) for j in range(1, size+1)]
	return f"""(define (problem visitall_{size})
  (:domain visitall)
  (:objects 
    {get_objects(size)})
  (:init
    (at_row r1)
    (at_column c1)
    {'    '.join(conn_rows)}    {'    '.join(conn_cols)}  )
  (:goal (and
    {'    '.join(visited)}  )))
"""


def main():
	parser = argparse.ArgumentParser(description="Visitall PDDL generator")
	parser.add_argument("-f", "--from_nth", type=int, required=True)
	parser.add_argument("-t", "--to_nth", type=int, required=True)
	parser.add_argument("-s", "--step", type=int, nargs='?', default=1, required=False)
	parser.add_argument("-o", "--out_folder", type=str, required=True)
	args = parser.parse_args()

	from_nth = args.from_nth
	to_nth = args.to_nth
	step = args.step
	out_folder = args.out_folder

	if step < 1 or to_nth < from_nth:
		sys.exit(-2)

	# DOMAIN
	with open(f"{out_folder}/domain.pddl", "w") as f_dom:
		f_dom.write(get_domain())

	# INSTANCES
	for i in range(from_nth, to_nth+1, step):
		with open(f"{out_folder}/p{i+1-from_nth:02}.pddl", "w") as f_ins:
			f_ins.write(get_instance(size=i))

	sys.exit(0)


if __name__ == "__main__":
	main()
