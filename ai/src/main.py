#!/usr/bin/env python3

##
## EPITECH PROJECT, 2023
## main.py
## File description:
## main
##

from http import client
from typing import Dict
import sys
import socket
import enum
from ai.src.args import retrieve_args
from ai.src.commands import *
from ai.src.connection import *
from ai.src.algorithm import *
from enum import Enum
from dataclasses import dataclass
import traceback

@dataclass
class AI:
    elevation: list[list]
    sock: socket
    inout: list
    commands: list
    level: int
    missing: list
    teamname: str
    look_path: str
    available_slots: int
    state: int
    port: int
    broadcast_direction: str
    need_to_go: int
    waiting_for_players: int
    missing_resource: str
    research: int
    obj_find: int
    set_objects_done: int
    is_incanting: int
    needed_food: int
    inventory: Dict[str, int]
    is_fork_ok: int
    asker: bool
    nb_players_begin: int
    counting: bool
    fork_countdown: int
    objects_are_set : bool
    fork_counter: int
    players_ready: int
    ready: int
    inv_count: int
    nb_players: int
    player_forking: bool
    left_counter: int
    waiting_look_ans: bool
    level_up_counter: int
    wait_inv: bool
    look_count: int
    go_to_update: bool

inventory = {
    "food": 0,
    "linemate": 0,
    "deraumere": 0,
    "sibur": 0,
    "mendiane": 0,
    "phiras": 0,
    "thystame": 0
}

def init_elevation():
    res = [
        {"nb_players": 1, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
        {"nb_players": 2, "linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
        {"nb_players": 2, "linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
        {"nb_players": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
        {"nb_players": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
        {"nb_players": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
        {"nb_players": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
    ]
    return res


if __name__ == '__main__':
    try:
        elevation = init_elevation()
        port, teamname, machine = retrieve_args(sys.argv)
        sock = create_connection(port, machine)
        inout = [sock]
        send_team_name(sock, teamname)
        map_size = 0
        available_slots = -1
        receive_client_num(sock, available_slots, map_size)
        commands = []
        level = 1
        is_fork_ok = False
        ai = AI(elevation, sock, inout, commands, level, [], teamname, "", available_slots, 0, port, "", 0, 0, "", 1, 0, 0, 0, 0, inventory, is_fork_ok, False, 0, True, 0, False, 0, 0, 0, 0, 0, False, 0, False, 0, False, 10, False)
        ia(ai)
    except Exception as message:
        tb = traceback.format_exc()
        print(f"Error: {str(message)}\n{tb}")
        if 'sock' in locals() and sock.fileno() != -1:
            sock.close()
        sys.exit(84)
