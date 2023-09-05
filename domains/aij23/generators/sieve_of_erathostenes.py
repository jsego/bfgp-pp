import sys
import argparse


def main():
    parser = argparse.ArgumentParser(description="Sieve of Erathostenes generator")
    parser.add_argument("-f", "--from_nth", type=int, required=True)
    parser.add_argument("-t", "--to_nth", type=int, required=True)
    parser.add_argument("-s", "--step", type=int, nargs='?', default=1, required=False)
    parser.add_argument("-o", "--out_folder", type=str, required=True)
    args = parser.parse_args()

    from_nth = args.from_nth
    to_nth = args.to_nth
    step = args.step
    out_folder = args.out_folder

    if step < 1 or to_nth < from_nth or from_nth < 2:
        sys.exit(-2)

    # DOMAIN
    str_domain = "[DOMAIN]: SIEVE-OF-ERATOSTHENES\n\n"
    str_domain += "[FUNCTIONS]:\n"
    str_domain += "vector(?o:object)\n"

    str_domain += "\n[ACTIONS]:\n"
    str_domain += "[ACTION]: set_no_prime(?x:object)\n"
    str_domain += "[TYPE]: memory\n"
    str_domain += "[PRECONDITIONS]:\n"
    str_domain += "[EFFECTS]:\n"
    str_domain += "(vector(?x)=0)\n"

    with open(f"{out_folder}/domain.txt", "w") as f_domain:
        f_domain.write(str_domain)

    # INSTANCES
    problem_id = 1
    for i in range(from_nth, to_nth + 1, step):
        # Problem name
        str_problem = f"[INSTANCE]: sieve_{problem_id}\n"
        str_problem += "[DOMAIN]: SIEVE-OF-ERATOSTHENES\n"

        # Objects
        str_problem += "\n[OBJECTS]:\n"
        for i_id in range(i+1):
            str_problem += f"p{i_id}:object\n"

        # Initial state
        str_problem += "\n[INIT]:\n"
        for i_id in range(i+1):
            str_problem += f"(vector(p{i_id})=1)\n"

        # Compute Sieve
        v = [1 for _ in range(i+1)]
        for j in range(2, i+1):
            if v[j] == 0:
                continue
            k = j+j
            while k < i+1:
                v[k] = 0
                k += j

        # Goal condition
        str_problem += "\n[GOAL]:\n"
        for i_id in range(i+1):
            str_problem += f"(vector(p{i_id})={v[i_id]})\n"

        with open(f"{out_folder}/{problem_id}.txt", "w") as f_problem:
            f_problem.write(str_problem)

        problem_id += 1

    sys.exit(0)


if __name__ == "__main__":
    main()
