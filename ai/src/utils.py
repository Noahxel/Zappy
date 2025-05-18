##
## EPITECH PROJECT, 2023
## utils.py
## File description:
## utils
##

from .commands import *
import re

def findRessource(ress, ret):
    res = []
    for i, str in enumerate(ret):
        if ress in str:
            res.append(i)
    return res

def usage():
    print("USAGE: ./zappy_ai -p port -n name -h machine\n"
    "\tport\tis the port number\n"
    "\tname\tis the name of the team\n"
    "\tmachine\tis the name of the machine; localhost by default")

def getMissingRessource(ai, buf):
    inv = int(re.search(r'\d+', buf).group())
    res = []
    res[0] = inv[0]
    for i in range(1, len(inv)):
        if ai.elevation[ai.level - 1][i] - inv[i] < 0:
            res[i] = 0
        else:
            res[i] = ai.elevation[ai.level - 1][i] - inv[i]
    return res

def isIncantationPossible(missing):
    for i in range(1, len(missing)):
        if missing[i] > 0:
            return False
    return True
