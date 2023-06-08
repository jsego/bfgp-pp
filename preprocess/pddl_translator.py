import argparse
from tarski.io import PDDLReader
from tarski.syntax.formulas import is_atom


def translate_domain(tarski_problem, file_name, applied_pddl_action=""):
	str_out = "[DOMAIN]: " + tarski_problem.domain_name + "\n\n"
	str_out += "[TYPES]:\n"
	for t in tarski_problem.language.sorts:
		if not str(t.name) in ["Real", "Integer", "Natural", "number", "object"]:
			if len(tarski_problem.language.sorts) > 1:
				str_out += str(t.name) + ":" + str(tarski_problem.language.immediate_parent[t].name) + "\n"

	str_out += "\n"
	str_out += "[FUNCTIONS]:\n"
	counter = 0
	for p in tarski_problem.language.predicates:
		if not str(p.name) in ["=", "!=", "<", "<=", ">", ">="]:
			str_out += str(p.name)+"("

			str_aux = ""
			for a in p.sort:
				str_aux += "?x" + str(counter) + ":" + a.name + ","
				counter = counter + 1
			str_aux += ")\n"
			str_out += str_aux.replace(",)", ")")

	if applied_pddl_action != "":
		for act_name in list(tarski_problem.actions):
			action = tarski_problem.get_action(act_name)
			str_out += "action_"+act_name.lower() + "("

			str_aux = ""
			for p in action.parameters:
				str_aux += str(p) + ":" + p.sort.name + ","

			str_aux += ")\n"
			str_out += str_aux.replace(",)", ")")

	else:
		str_out += "\n[ACTIONS]:"
		for act_name in list(tarski_problem.actions):
			action = tarski_problem.get_action(act_name)
			str_out += "\n"
			str_out += "[ACTION]: " + act_name + "("

			str_aux = ""
			for p in action.parameters:
				str_aux += str(p) + ":" + p.sort.name + ","

			str_aux += ")\n"
			str_out += str_aux.replace(",)", ")")

			str_out += "[TYPE]: memory\n"

			str_out += "[PRECONDITIONS]:\n"
			if type(action.precondition).__name__ == "CompoundFormula":
				for p in action.precondition.subformulas:
					if type(p).__name__ == "CompoundFormula":  # NegatedAtom
						str_out += "(" + str(p.subformulas[0]) + "=0)\n"
					else:
						str_out += "(" + str(p)+"=1)\n"
			elif type(action.precondition).__name__ == "Atom":
				str_out += "(" + str(action.precondition) + "=1)\n"

			str_out += "[EFFECTS]:\n"
			for p in action.effects:
				if type(p).__name__ == "DelEffect":
					str_out += "(" + str(p.atom) + "=0)\n"
				elif type(p).__name__ == "AddEffect":
					str_out += "(" + str(p.atom) + "=1)\n"

	with open(file_name, "w") as f_domain:
		f_domain.write(str_out.replace("-", "_"))


def translate_problem(tarski_problem, file_name, applied_pddl_action=""):
	str_out = "[INSTANCE]: " + tarski_problem.name + "\n"
	str_out += "[DOMAIN]: " + tarski_problem.domain_name + "\n"

	str_out += "\n"
	str_out += "[OBJECTS]:\n"
	for o in tarski_problem.language.constants():
		str_out += str(o) + ":" + str(o.sort.name) + "\n"

	str_out += "\n"
	str_out += "[INIT]:\n"
	if applied_pddl_action != "":
		applied_action = applied_pddl_action[1:-1].lower().split()
		action_label, action_args = f"action_{applied_action[0]}", ','.join(applied_action[1::])
		str_out += f"({action_label}({action_args})=1)\n"

	for a in tarski_problem.init.as_atoms():
		if not is_atom(a):
			continue
		str_out += "(" + str(a)+"=1)\n"

	str_out += "\n"
	str_out += "[GOAL]:\n"
	if type(tarski_problem.goal).__name__ == "CompoundFormula":
		for p in tarski_problem.goal.subformulas:
			str_out += "(" + str(p) + "=1)\n"
	if type(tarski_problem.goal).__name__ == "Atom":
		str_out += "(" + str(tarski_problem.goal) + "=1)\n"

	with open(file_name, "w") as f_domain:
		f_domain.write(str_out.replace("-", "_"))


def translate_pddl_to_ram(domain_file: str, instance_file: str, output_dir: str, pddl_action: str = "", id: int = 0):
	reader = PDDLReader(raise_on_error=True)
	reader.parse_domain(domain_file)
	problem = reader.parse_instance(instance_file)

	output_problem_name = ("problem" if id == 0 else f"{id}")
	translate_domain(problem, f"{output_dir}/domain.txt", applied_pddl_action=pddl_action)
	translate_problem(problem, f"{output_dir}/{output_problem_name}.txt", applied_pddl_action=pddl_action)


def main():
	parser = argparse.ArgumentParser(description='Translate PDDL domain and instance to a Learning Action Model Problem')
	parser.add_argument("-d", "--domain", type=str, required=True)
	parser.add_argument("-i", "--instance", type=str, required=True)
	parser.add_argument("-o", "--outdir", type=str, required=True)
	parser.add_argument("-a", "--action", type=str, default="")
	parser.add_argument("-id","--instance_id", type=int, default=0)
	args = parser.parse_args()

	translate_pddl_to_ram(domain_file=args.domain,
						  instance_file=args.instance,
						  output_dir=args.outdir,
						  pddl_action=args.action,
						  id=args.instance_id)


if __name__ == "__main__":
	main()
