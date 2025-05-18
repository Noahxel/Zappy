##
## EPITECH PROJECT, 2023
## tests_check_args.py
## File description:
## test_check_args
##

import pytest
from unittest.mock import call
from src import args
import sys

def test_get_args_valid_case():
    arguments = ["-p", "8080", "-n", "team", "-h", "localhost"]
    flag = "-p"
    result = args.get_args(arguments, flag)
    assert result == "8080"

def test_check_args_valid_case():
    av = ["zappy_ai", "-p", "8080", "-n", "team", "-h", "localhost"]
    ac = len(av)
    args.check_args(ac, av)

def test_retrieve_args_valid_case():
    argv = ["zappy_ai", "-p", "8080", "-n", "team", "-h", "localhost"]
    port, name, machine = args.retrieve_args(argv)
    assert port == 8080
    assert name == "team"
    assert machine == "localhost"
