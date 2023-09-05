import sys
import numpy as np
import argparse


def main():
	parser = argparse.ArgumentParser(description="Sorting Generator")
	parser.add_argument("-m", "--mode", type=str, choices=["synthesis", "validation"], required=True)
	parser.add_argument("-f", "--from_size", type=int, required=True)
	parser.add_argument("-t", "--to_size", type=int, required=True)
	parser.add_argument("-s", "--step", type=int, nargs='?', default=1, required=False)
	parser.add_argument("-o", "--out_folder", type=str, required=True)
	args = parser.parse_args()

	mode = args.mode
	from_size = args.from_size
	to_size = args.to_size
	step = args.step
	out_folder = args.out_folder

	if step < 1 or to_size < from_size:
		sys.exit(-2)

	# DOMAIN
	str_domain = "[DOMAIN]: SORTING\n\n"
	str_domain += "[FUNCTIONS]:\n"
	str_domain += "vector(?o:object)\n"

	str_domain += "\n[ACTIONS]:\n"
	str_domain += "[ACTION]: swap(?x:object,?y:object)\n"
	str_domain += "[TYPE]: memory\n"
	str_domain += "[PRECONDITIONS]:\n"
	str_domain += "[EFFECTS]:\n"
	str_domain += "(vector(?x)=vector(?y))\n"
	str_domain += "(vector(?y)=vector(?x))\n"

	f_domain = open(out_folder + "domain.txt", "w")
	f_domain.write(str_domain)
	f_domain.close()

	# INSTANCES
	problem_id = 1
	seed = problem_id
	i = from_size

	# synthesis by default
	max_val = 100 if mode == "synthesis" else 1000000000

	while i <= to_size:
		# Computing
		np.random.seed(seed)  # new id for each problem
		v = np.random.randint(max_val, size=i)

		# Problem name
		str_problem = "[INSTANCE]: sorting-" + str(i) + "\n"		
		str_problem += "[DOMAIN]: SORTING\n"

		# Objects
		str_problem += "\n[OBJECTS]:\n"
		for j in range(i):
			str_problem += "p" + str(j) + ":object\n"

		# Initial state
		str_problem += "\n[INIT]:\n"
		for j in range(i):
			str_problem += "(vector(p" + str(j) + ")=" + str(v[j]) + ")\n"

		# Goal condition
		str_problem += "\n[GOAL]:\n"
		v = np.sort(v)
		for j in range(i):
			str_problem += "(vector(p" + str(j) + ")=" + str(v[j]) + ")\n"

		# print( str_problem )
		f_problem = open(f"{out_folder}/{problem_id}.txt", "w")
		f_problem.write(str_problem)
		f_problem.close()

		i += step
		problem_id += 1
		seed += 1

	sys.exit(0)


if __name__ == "__main__":
	main()
