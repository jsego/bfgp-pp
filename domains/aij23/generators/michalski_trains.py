import sys
import argparse
from pddl_translator import translate_pddl_to_ram


def get_cars_per_train():
    return [4, 3, 3, 4, 3, 2, 3, 2, 4, 2]


def get_car(train_id: int, car_id: int):
    return f"c{car_id}_t{train_id}"


def get_cars():
    return [get_car(idx+1, c+1) for idx, n_cars in enumerate(get_cars_per_train()) for c in range(n_cars)]


def get_shapes():
    return ["ellipse", "hexagon", "rectangle", "u_shaped", "triangle", "circle"]


def get_inumbers():
    return [f"n{i}" for i in range(1, 4)]


def get_trains():
    return [f"t{i}" for i in range(1, 11)]


def get_objects():
    return ("\n    " + " ".join(get_cars()) + " - car\n    " +
            " ".join(get_trains()) + " - train\n    " +
            " ".join(get_shapes()) + " - shape\n    " +
            " ".join(get_inumbers()) + " - inumber")


def get_init():
    offset = "\n    "
    str_init = ""
    cpt = get_cars_per_train()

    # has car
    for t in range(1, 11):
        for c in range(cpt[t-1]):
            str_init += offset + f"(has_car t{t} {get_car(t, c+1)})"

    # short
    short = [21, 22, 51, 93, 82, 12, 32, 72, 43, 41, 94, 91, 53, 23, 42, 14, 71, 44, 62, 101, 31]
    for s in short:
        str_init += offset + f"(short {get_car(s//10, s%10)})"

    # closed
    closed = [12, 52, 32, 33, 43, 23, 53, 61, 81]
    for c in closed:
        str_init += offset + f"(closed {get_car(c//10, c%10)})"

    # long
    long_c = [52, 73, 13, 33, 92, 102, 61, 11, 81]
    for lc in long_c:
        str_init += offset + f"(long {get_car(lc//10, lc%10)})"

    # open
    open_c = [21, 22, 13, 51, 93, 82, 72, 11, 41, 94, 91, 42, 14, 71, 44, 62, 101, 102, 31]
    for o in open_c:
        str_init += offset + f"(open {get_car(o//10, o%10)})"

    # car shape
    shapes = get_shapes()  # ellipse, hexagon, rectangle, u_shaped, triangle, circle
    c_shapes = [(43, 0), (71, 2), (22, 3), (41, 3), (51, 2), (72, 3), (42, 2), (61, 2), (62, 2), (23, 2), (53, 2),
                (73, 2), (91, 3), (92, 2), (93, 2), (102, 2), (52, 2), (31, 2), (32, 1), (44, 2), (11, 2), (13, 2),
                (101, 3), (94, 3), (21, 3), (81, 2), (82, 3), (14, 2), (33, 2), (12, 2)]
    for c in c_shapes:
        str_init += offset + f"(c_shape {get_car(c[0]//10, c[0]%10)} {shapes[c[1]]})"

    # load
    loads = [(93, 2, 1), (81, 2, 1), (102, 2, 2), (23, 5, 2), (42, 4, 1), (32, 4, 1), (33, 4, 1), (92, 2, 1),
             (101, 2, 1), (51, 4, 1), (93, 5, 1), (91, 5, 1), (22, 2, 1), (53, 5, 1), (31, 5, 1), (11, 2, 3),
             (41, 4, 1), (12, 4, 1), (62, 4, 1), (72, 4, 1), (43, 2, 1), (71, 5, 1), (14, 5, 1), (61, 5, 3), (82, 5, 1),
             (13, 1, 1), (44, 2, 1), (21, 4, 1), (52, 2, 1)]
    for lo in loads:
        str_init += offset + f"(load {get_car(lo[0]//10, lo[0]%10)} {shapes[lo[1]]} n{lo[2]})"

    # wheels
    wheels = [(72, 2), (102, 2), (31, 2), (44, 2), (11, 2), (14, 2), (91, 2), (12, 2), (32, 2), (71, 2), (51, 2),
              (94, 2), (21, 2), (82, 2), (101, 2), (42, 2), (61, 2), (52, 3), (23, 2), (73, 2), (13, 3), (62, 2),
              (53, 2), (22, 2), (81, 3), (33, 3), (41, 2), (43, 2), (93, 2), (92, 2)]
    for w in wheels:
        str_init += offset + f"(wheels {get_car(w[0]//10, w[0]%10)} n{w[1]})"

    # in front 1 (train <- car)
    for t in range(1, 11):
        str_init += offset + f"(in_front_1 t{t} {get_car(t, 1)})"

    # in front n (car <- car)
    for t in range(1, 11):
        for c in range(1, cpt[t-1]):
            str_init += offset + f"(in_front_n {get_car(t, c)} {get_car(t, c+1)})"

    str_init += offset + f"(double {get_car(4, 2)})"
    str_init += offset + f"(double {get_car(7, 1)})"
    str_init += offset + f"(double {get_car(5, 1)})"
    str_init += offset + f"(jagged {get_car(9, 2)})"
    str_init += offset + f"(jagged {get_car(7, 3)})"
    str_init += offset + f"(greater n3 n2)"
    str_init += offset + f"(greater n2 n1)"
    str_init += offset + f"(greater n3 n1)"
    return str_init


def get_goals():
    return "".join([f"\n    (eastbound t{t})" for t in range(1, 6)] +
                   [f"\n    (westbound t{t})" for t in range(6, 11)])


def generate_problem(name: str):
    return f"(define (problem {name})\n" \
           f"  (:domain michalski_trains)\n" \
           f"  (:objects {get_objects()})\n" \
           f"  (:init {get_init()})\n" \
           f"  (:goal (and {get_goals()})))\n"


def generate_domain():
    return """(define (domain michalski_trains)
 (:requirements :strips :typing :negative-preconditions)
 (:types train car shape inumber)
 (:predicates 
    (eastbound ?t - train)
    (westbound ?t - train)
    (has_car ?t - train ?c - car)
    (open ?c - car)
    (closed ?c - car)
    (short ?c - car)
    (long ?c - car)
    (double ?c - car)
    (jagged ?c - car)
    (c_shape ?c - car ?s - shape)
    (in_front_1 ?t - train ?c - car)
    (in_front_n ?c1 ?c2 - car)
    (load ?c - car ?s - shape ?n - inumber)
    (wheels ?c - car ?n - inumber)
    (greater ?n1 ?n2 - inumber))
 
 (:action set_eastbound
    :parameters (?t - train)
    :precondition (and (not (eastbound ?t))(not (westbound ?t)))
    :effect (and (eastbound ?t)))
    
 (:action set_westbound
    :parameters (?t - train)
    :precondition (and (not (eastbound ?t))(not (westbound ?t)))
    :effect (and (westbound ?t)))) 
"""


def main():
    parser = argparse.ArgumentParser(description="Michalski Trains generator")
    parser.add_argument("-o", "--out_folder", type=str, required=True)
    args = parser.parse_args()

    out_folder = args.out_folder

    # DOMAIN
    domain_name = f"{out_folder}/domain.pddl"
    str_domain = generate_domain()
    with open(domain_name, "w") as f_domain:
        f_domain.write(str_domain)

    # INSTANCES
    str_problem = generate_problem("michalski_trains_10")
    inst_name = f"{out_folder}/1.pddl"
    with open(inst_name, "w") as f_problem:
        f_problem.write(str_problem)
    translate_pddl_to_ram(domain_file=domain_name, instance_file=inst_name, output_dir=out_folder, pddl_action="", id=1)

    sys.exit(0)


if __name__ == "__main__":
    main()
