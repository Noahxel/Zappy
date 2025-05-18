#!/usr/bin/env python3

##
## EPITECH PROJECT, 2023
## commands.py
## File description:
## Commands actions for IA.
##

from enum import Enum

class Commands(Enum):
    FORWARD = "Forward\n"
    RIGHT = "Right\n"
    LEFT = "Left\n"
    LEFT2 = "Left\n"
    LOOK1 = "Look\n"
    LOOK2 = "Look2\n"
    LOOK3 = "Look\n"
    LOOK4 = "Look\n"
    INVENTORY = "Inventory\n"
    BROADCAST = "Broadcast {}\n"
    CONNECT = "Connect_nbr\n"
    FORK = "Fork\n"
    EJECT = "Eject\n"
    TAKE = "Take {}\n"
    SET = "Set {}\n"
    INCANTATION = "Incantation\n"

class Ressource(Enum):
    FOOD = "food"
    LINEMATE = "linemate"
    DERAUMERE = "deraumere"
    SIBUR = "sibur"
    MENDIANE = "mendiane"
    PHIRAS = "phiras"
    THYSTAME = "thystame"

    @classmethod
    def get_index(cls, member):
        return list(cls).index(member)

def remove_command(args):
    args.commands.pop(0)
    if len(args.commands) >= 10 and args.commands[:10].count(Commands.INCANTATION.value) < 2:
        if args.commands[9] == Commands.LOOK2.value:
            print(f"SENDING from remove: LOOK2")
            args.sock.sendall(Commands.LOOK1.value.encode("utf-8"))
        else:
            print(f"SENDING from remove: {args.commands[9]}")
            args.sock.sendall(args.commands[9].encode("utf-8"))

def send_command(command, args, parameter=None):
    if parameter:
        command_string = command.value.format(parameter)
    else:
        command_string = command.value
    print(f"APPEND: {command_string}")
    args.commands.append(command_string)
    if command == Commands.INCANTATION:
        args.commands.append(command_string)
    if (len(args.commands) <= 10):
        print(f"SENDING: {command_string}")
        try:
            if (command == Commands.LOOK2):
                args.sock.sendall(Commands.LOOK1.value.encode("utf-8"))
            else:
                args.sock.sendall(command_string.encode("utf-8"))
        except BrokenPipeError:
            print("BrokenPipeError: connection to server lost")

