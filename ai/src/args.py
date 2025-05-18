##
## EPITECH PROJECT, 2023
## cehck_args.py
## File description:
## check_args
##

import sys
from .utils import usage

def get_args(arguments, flag):
    try:
        return arguments[arguments.index(flag) + 1]
    except (ValueError, IndexError):
        if flag == "-h":
            return "localhost"
        print(f"Could not find or parse argument following {flag}")
        sys.exit(84)

def check_args(ac, av):
    if ac == 2 and av[1] == "-help":
        usage()
        exit(0)
    if ac != 7 and ac != 6 and ac != 5:
        raise ValueError("Invalid number of arguments")
    for i in range(1, ac, 2):
        if av[i] not in ["-p", "-n", "-h"]:
            raise ValueError(f"Invalid option: {av[i]}")
        if av[i] == "-p" and not av[i + 1].isdigit():
            raise ValueError("Port number should be a number")
        if av[i] == "-n" and not av[i + 1]:
            raise ValueError("Name should not be empty")
        if av[i] == "-h" and not av[i + 1]:
            pass

def retrieve_args(argv):
    check_args(len(argv), argv)
    port = int(get_args(argv, "-p"))
    name = get_args(argv, "-n")
    machine = get_args(argv, "-h")
    return port, name, machine