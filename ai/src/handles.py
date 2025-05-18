##
## EPITECH PROJECT, 2023
## handles.py
## File description:
## handle functions.
##

from .commands import *
from .utils import findRessource, getMissingRessource, isIncantationPossible
from .algorithm import *
import subprocess
import random
import re

lerandenY = [Commands.FORWARD, Commands.LEFT, Commands.RIGHT]

look_pattern = [
    'current_cell',
    'Forward Left Forward',
    'Forward',
    'Forward Right Forward',

    'Forward Forward Left Forward Forward',
    'Forward Forward Left Forward',
    'Forward Forward',
    'Forward Forward Right Forward',
    'Forward Forward Right Forward Forward',

    'Forward Forward Forward Left Forward Forward Forward',
    'Forward Forward Forward Left Forward Forward',
    'Forward Forward Forward Left Forward',
    'Forward Forward Forward',
    'Forward Forward Forward Right Forward',
    'Forward Forward Forward Right Forward Forward',
    'Forward Forward Forward Right Forward Forward Forward',

    'Forward Forward Forward Forward Left Forward Forward Forward Forward',
    'Forward Forward Forward Forward Left Forward Forward Forward',
    'Forward Forward Forward Forward Left Forward Forward',
    'Forward Forward Forward Forward Left Forward',
    'Forward Forward Forward Forward',
    'Forward Forward Forward Forward Right Forward',
    'Forward Forward Forward Forward Right Forward Forward',
    'Forward Forward Forward Forward Right Forward Forward Forward',
    'Forward Forward Forward Forward Right Forward Forward Forward Forward',

    'Forward Forward Forward Forward Forward Left Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Left Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Left Forward Forward Forward',
    'Forward Forward Forward Forward Forward Left Forward Forward',
    'Forward Forward Forward Forward Forward Left Forward',
    'Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Right Forward',
    'Forward Forward Forward Forward Forward Right Forward Forward',
    'Forward Forward Forward Forward Forward Right Forward Forward Forward',
    'Forward Forward Forward Forward Forward Right Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Right Forward Forward Forward Forward Forward',

    'Forward Forward Forward Forward Forward Forward Left Forward Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Left Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Left Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Left Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Left Forward Forward',
    'Forward Forward Forward Forward Forward Forward Left Forward',
    'Forward Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Right Forward',
    'Forward Forward Forward Forward Forward Forward Right Forward Forward',
    'Forward Forward Forward Forward Forward Forward Right Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Right Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Right Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Right Forward Forward Forward Forward Forward Forward',

    'Forward Forward Forward Forward Forward Forward Forward Left Forward Forward Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Left Forward Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Left Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Left Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Left Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Left Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Left Forward',
    'Forward Forward Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Right Forward',
    'Forward Forward Forward Forward Forward Forward Forward Right Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Right Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Right Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Right Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Right Forward Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Right Forward Forward Forward Forward Forward Forward Forward',

    'Forward Forward Forward Forward Forward Forward Forward Forward Left Forward Forward Forward Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Left Forward Forward Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Left Forward Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Left Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Left Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Left Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Left Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Left Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Right Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Right Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Right Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Right Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Right Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Right Forward Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Right Forward Forward Forward Forward Forward Forward Forward',
    'Forward Forward Forward Forward Forward Forward Forward Forward Right Forward Forward Forward Forward Forward Forward Forward Forward',

]

def parse_look_path(path, ai, ress):
    if path != "current_cell":
        temp = path.split(" ")
        for i in range(0, len(temp)):
            for command in Commands:
                if temp[i] in command:
                    send_command(command, ai)
    send_command(Commands.TAKE, ai, ress)

def get_ennemy_number(ai, ret) :
    player_nb = findRessource("player", ret).count(0)
    ennemy_nb = player_nb - (findRessource(ai.teamname, ret).count(0))
    return ennemy_nb

def handle_look1(buf, ai):
    count = 0
    temp = buf.replace("[", "")
    temp = temp.replace("]", "")
    ret = temp.split(",")
    pos = findRessource("food", ret)
    if get_ennemy_number(ai, ret) > 0 and ai.missing[0] > 3 * 126:
        send_command(Commands.EJECT, ai)
        return;
    count += len(pos)
    if (ai.missing[0] < 4 * 126 and len(pos) > 0):
        parse_look_path(update_look_path(ai, "food", buf), ai, "food")
    else:
        for i in range(1, len(ai.missing)):
            pos = findRessource(list(Ressource)[i].value, ret)
            count += len(pos)
            if ai.missing[i] > 0 and len(pos) > 0:
                parse_look_path(update_look_path(ai, list(Ressource)[i].value, buf), ai, list(Ressource)[i].value)
                break
    return count

def update_look_path(ai, object_to_search, buf):
    print(f"research : {ai.research} need to go : {ai.need_to_go}")
    if (ai.research == 1 and ai.player_forking == True and ai.go_to_update == False) or ai.need_to_go == 1:
        return
    my_list = buf.split(",")
    found = False
    if "food" in my_list[0]:
        for _ in range(0, my_list[0].count("food")):
            send_command(Commands.TAKE, ai, Ressource.FOOD.value)
    for i, node in enumerate(my_list):
        if object_to_search in node:
            found = True
            movement = look_pattern[i].split(" ")
            while len(movement) > 0 and ai.obj_find == 0:
                if movement[0] == 'Forward':
                    send_command(Commands.FORWARD, ai)
                    movement.pop(0)
                elif movement[0] == 'Left':
                    send_command(Commands.LEFT, ai)
                    movement.pop(0)
                elif movement[0] == 'Right':
                    send_command(Commands.RIGHT, ai)
                    movement.pop(0)
                elif i == 0 and object_to_search in node:
                    send_command(Commands.TAKE, ai, f"{object_to_search}")
                    send_command(Commands.INVENTORY, ai)
                    ai.obj_find = 1
            break
    if not found:
        cmd = random.choice(lerandenY)
        send_command(cmd, ai)
    ai.research = 1

def update_inventory(ai, buf):
    buf = buf.strip("[]\n")
    items_counts = buf.split(", ")
    for item_count in items_counts:
        item, count = item_count.rsplit(" ", 1)
        if count.isdigit():
            ai.inventory[item] = int(count)
        else:
            print(f"Invalid count for item '{item}': '{count}'")
    print(ai.inventory)

def handle_response(buf, ai):
    match ai.commands[0]:
        case Commands.LEFT2.value:
            ai.left_counter += 1
        case Commands.INVENTORY.value:
            update_inventory(ai, buf)
            ai.obj_find = 0
        case Commands.LOOK1.value:
            if ai.need_to_go == 0:
                print("object to search: ", ai.missing_resource)
                update_look_path(ai, ai.missing_resource, buf)
        case Commands.LOOK2.value:
            ai.waiting_look_ans = False
            if (ai.player_forking == True):
                ai.wait_inv = False
                ai.look_count -= 1
            print("WAITIIIING FALSE")
            update_look_path(ai, "food", buf)
        case Commands.INCANTATION.value:
            if buf == "Elevation underway":
                ai.is_incanting = 1
                print("Frozen for 300 units of time")
            if buf == "Current level: " + str(ai.level + 1):
                ai.level += 1
                ai.is_incanting = 0
                ai.waiting_for_players = 0
                ai.players_ready = 0
                ai.need_to_go = 0
                ai.ready = 0
                ai.research = 1
                ai.level_up_counter = 0
                print("Level up !  " + str(ai.level - 1) + " -> " + str(ai.level))
            if buf == "ko":
                print("KO: INCANTATION FROM LVL " + str(ai.level) + " TO LVL " + str(ai.level + 1) + " FAILED !")
                ai.is_incanting = 0
                ai.research = 1
        case Commands.CONNECT.value:
            ai.available_slots = int(buf)
            print("UPDATE available_slots:", ai.available_slots)
            if ai.available_slots == 0 and ai.is_fork_ok == False:
                send_command(Commands.BROADCAST, ai, ai.teamname +  " is fork ok ?")
                ai.asker = True
                for _ in range (0, 25):
                    send_command(Commands.LEFT2, ai)
            elif ai.available_slots != 0:
                command = ["./zappy_ai", "-p", str(ai.port), "-n", ai.teamname]
                subprocess.Popen(command)
                print("SUBPROCESS NEW IA PLAYER OF TEAM:", ai.teamname, str(ai.port))
        case Commands.FORK.value:
            if "ok" in buf:
                ai.fork_counter += 1
        case Commands.FORWARD.value:
            if (ai.player_forking == True):
                ai.inv_count += 1
                if (ai.inv_count >= 4):
                    send_command(Commands.LOOK2, ai)
                    ai.inv_count = 0
    remove_command(ai)
