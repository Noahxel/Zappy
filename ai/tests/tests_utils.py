##
## EPITECH PROJECT, 2023
## tests_ia.py
## File description:
## test_ia
##

import pytest
from unittest.mock import Mock
from src.utils import *

def test_findRessource():
    ret = ["food", "linemate", "linemate", "sibur", "mendiane", "linemate"]
    assert findRessource("food", ret) == [0]
    assert findRessource("linemate", ret) == [1, 2, 5]
    assert findRessource("sibur", ret) == [3]
    assert findRessource("mendiane", ret) == [4]

def test_isIncantationPossible():
    missing1 = [0, 0, 0, 0]
    missing2 = [0, 1, 0, 0]
    assert isIncantationPossible(missing1) == True
    assert isIncantationPossible(missing2) == False
