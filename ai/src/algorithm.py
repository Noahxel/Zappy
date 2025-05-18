#!/usr/bin/env python3

##
## EPITECH PROJECT, 2023
## ai_algorithm.py
## File description:
## IA
##

import random
import select
import re
from .commands import *
from .handles import handle_response
import subprocess
import time

def have_resources_for_lvl_up(ai):
    next_level_requirements = ai.elevation[ai.level]
    for index, item in enumerate(list(ai.inventory.keys())[1:], start=1):
        if ai.inventory[item] < next_level_requirements[index-1]:
            return False
    return True

def first_missing_resource_for_lvl_up(ai):
    next_level_requirements = ai.elevation[ai.level-1]
    for item in list(ai.inventory.keys())[1:]:
        if item in next_level_requirements and ai.inventory[item] < next_level_requirements[item]:
            return item
    return None

def set_required_objects(ai):
    next_level_requirements = ai.elevation[ai.level-1]
    for item in list(ai.inventory.keys())[1:]:
        for _ in range(next_level_requirements[item]):
            send_command(Commands.SET, ai, item)

def go_to_broadcast(ai):
    if Commands.FORWARD.value in ai.commands or Commands.LEFT.value in ai.commands or Commands.RIGHT.value in ai.commands:
        ai.broadcast_direction = ""
        send_command(Commands.BROADCAST, ai, f"{ai.teamname} level_up ok")
        return
    if ai.broadcast_direction == "actual position" and ai.ready == 0:
        send_command(Commands.BROADCAST, ai, f"{ai.teamname} ready")
        ai.ready = 1
    elif ai.broadcast_direction == "top":
        send_command(Commands.FORWARD, ai)
    elif ai.broadcast_direction == "top left":
        send_command(Commands.FORWARD, ai)
        send_command(Commands.LEFT, ai)
        send_command(Commands.FORWARD, ai)
    elif ai.broadcast_direction == "left":
        send_command(Commands.LEFT, ai)
        send_command(Commands.FORWARD, ai)
    elif ai.broadcast_direction == "down left":
        send_command(Commands.LEFT, ai)
        send_command(Commands.FORWARD, ai)
        send_command(Commands.LEFT, ai)
        send_command(Commands.FORWARD, ai)
    elif ai.broadcast_direction == "down":
        send_command(Commands.LEFT, ai)
        send_command(Commands.LEFT, ai)
        send_command(Commands.FORWARD, ai)
    elif ai.broadcast_direction == "down right":
        send_command(Commands.RIGHT, ai)
        send_command(Commands.FORWARD, ai)
        send_command(Commands.RIGHT, ai)
        send_command(Commands.FORWARD, ai)
    elif ai.broadcast_direction == "right":
        send_command(Commands.RIGHT, ai)
        send_command(Commands.FORWARD, ai)
    elif ai.broadcast_direction == "top right":
        send_command(Commands.FORWARD, ai)
        send_command(Commands.RIGHT, ai)
        send_command(Commands.FORWARD, ai)
    ai.broadcast_direction = ""
    send_command(Commands.BROADCAST, ai, f"{ai.teamname} level_up ok")

def parse_direction(ai, direction):
    if direction == 0:
        ai.broadcast_direction = "actual position"
    if direction == 1:
        ai.broadcast_direction = "top"
    if direction == 2:
        ai.broadcast_direction = "top left"
    if direction == 3:
        ai.broadcast_direction = "left"
    if direction == 4:
        ai.broadcast_direction = "down left"
    if direction == 5:
        ai.broadcast_direction = "down"
    if direction == 6:
        ai.broadcast_direction = "down right"
    if direction == 7:
        ai.broadcast_direction = "right"
    if direction == 8:
        ai.broadcast_direction = "top right"

def parse_message(ai, message):
    if "incantation" in message and ai.waiting_for_players == 1:
        return
    if "incantation" in message and ai.waiting_for_players != 1 and ai.ready == 0:
        match = re.search(ai.teamname + r" incantation (\d+)", message)
        if match:
            incantation_level = int(match.group(1))
            if ai.level == incantation_level or (ai.level + 1 == incantation_level and ai.is_incanting == 1):
                ai.need_to_go = 1
                ai.research = 0
    if "level_up" in message and ai.waiting_for_players == 1 and ai.players_ready < ai.nb_players and ai.level_up_counter < (ai.nb_players - ai.players_ready):
        ai.level_up_counter += 1
    if "level_up" in message and ai.waiting_for_players == 1 and ai.players_ready < ai.nb_players and ai.level_up_counter == (ai.nb_players - ai.players_ready):
        send_command(Commands.BROADCAST, ai, f"{ai.teamname} incantation {ai.level}")
        ai.level_up_counter = 0
    if "ready" in message and ai.waiting_for_players == 1:
        ai.players_ready += 1

def parse_broadcast(ai, buf):
    direction = int(buf[8])
    message = buf.split(", ")
    message = message[1]
    if f"level_up ok" in buf and ai.waiting_for_players == 0:
        return
    if f"ready ok" in buf and ai.waiting_for_players == 0:
        return
    parse_direction(ai, direction)
    parse_message(ai, message)
    if ai.need_to_go == 1 and ai.ready != 1:
        go_to_broadcast(ai)

def algorithm(ai):
    if ai.left_counter == 25 and ai.asker == True and ai.is_fork_ok == False:
        ai.asker = False
        ai.is_fork_ok = True
        ai.player_forking = True
        if ai.nb_players_begin > 5:
            nb_forks = 0
        else:
            nb_forks = (6 - ai.nb_players_begin - 1)
        ai.nb_players = ai.nb_players_begin + nb_forks
        send_command(Commands.BROADCAST, ai, ai.teamname + " fork is ok, " + str(ai.nb_players))
        if nb_forks > 0:
            for _ in range(0, nb_forks):
                send_command(Commands.FORK, ai)

    if ai.level != 8 and ai.research == 1 and ai.is_incanting == 0 and ai.ready != 1:
        ai.missing_resource = first_missing_resource_for_lvl_up(ai)
        if ai.missing_resource is None:
            if ai.waiting_for_players == 0 and ai.need_to_go == 0:
                if (ai.look_count == 0 and ai.wait_inv == False):
                    print("Wait for player for incanting i have all the resources")
                    send_command(Commands.BROADCAST, ai, f"{ai.teamname} incantation {ai.level}")
                    ai.waiting_for_players = 1
                    ai.look_count = 10
                    ai.go_to_update = False
                elif ai.wait_inv == False:
                    ai.go_to_update = True
                    send_command(Commands.LOOK2, ai)
                    ai.wait_inv = True
            if ai.waiting_for_players == 1 and ai.players_ready == ai.nb_players and ai.is_incanting != 1 and ai.player_forking == True:
                ai.commands = ai.commands[:10]
                ai.level_up_counter = 0
                set_required_objects(ai)
                send_command(Commands.INCANTATION, ai)
                ai.is_incanting = 1
                ai.obj_find = 0
        elif ai.missing_resource != None and ai.obj_find == 0 and ai.player_forking == True:
            send_command(Commands.LOOK1, ai)
            ai.research = 0
    #print(f"player forking : {ai.player_forking} need togo : {ai.need_to_go} waiting : {ai.waiting_look_ans}")
    if (ai.player_forking == False and ai.need_to_go == 0 and ai.waiting_look_ans == False):
        send_command(Commands.LOOK2, ai)
        print("WAITIINNNGGG TRUEEEEEE")
        ai.waiting_look_ans = True

def ia(ai):
    send_command(Commands.CONNECT, ai)
    while True:
        if ai.fork_counter == (6 - ai.nb_players_begin - 1) and ai.fork_counter > 0:
            command = ["./zappy_ai", "-p", str(ai.port), "-n", ai.teamname]
            subprocess.Popen(command)
            ai.fork_counter = -1
            print("WAITING FOR 3 SECONDS...\n\n\n\n\n")
            time.sleep(3)
        infds, outfds, errfds = select.select(ai.inout, ai.inout, [])
        if len(infds) != 0:
            temp = ai.sock.recv(1024).decode("utf-8")
            if len(temp) <= 0:
                exit()
            if '\n' in temp:
                temp = temp.split("\n")
            for buf in temp:
                if len(buf) != 0:
                    if buf == "dead":
                        exit()
                    if "Elevation underway" in buf and Commands.INCANTATION.value not in ai.commands:
                        ai.is_incanting = 1
                        continue
                    if "Current level" in buf and Commands.INCANTATION.value not in ai.commands:
                        ai.level += 1
                        print("LEVEL UP ! = ", ai.level)
                        ai.research = 1
                        ai.waiting_for_players = 0
                        ai.is_incanting = 0
                        ai.players_ready = 0
                        ai.obj_find = 0
                        ai.ready = 0
                        ai.need_to_go = 0
                        if (ai.player_forking == False):
                            for i in range(0, 4):
                                rand = random.randint(0, 2)
                                if (rand == 0):
                                    send_command(Commands.FORWARD, ai)
                                elif rand == 1:
                                    send_command(Commands.LEFT, ai)
                                elif rand == 2:
                                    send_command(Commands.RIGHT, ai)
                        continue
                    if "message" in buf and ai.teamname in buf:
                        print("RECEIVED BROADCAST = ", buf)
                        if "incantation" in buf or "level_up" in buf or "ready" in buf and ai.ready != 1:
                            parse_broadcast(ai, buf)
                        elif "fork" in buf:
                            buf = buf.split(", ")
                            message = buf[1]
                            if message == ai.teamname + " is fork ok ?":
                                if ai.is_fork_ok == True:
                                    send_command(Commands.BROADCAST, ai, ai.teamname + " fork is ok, " + str(ai.nb_players))
                                elif ai.is_fork_ok == False:
                                    send_command(Commands.BROADCAST, ai, ai.teamname + " fork is not ok")
                            if ai.teamname in message and "fork is ok" in message:
                                ai.is_fork_ok = True
                                ai.nb_players = int(buf[2])
                            elif message == ai.teamname + " fork is not ok" and ai.is_fork_ok == False:
                                ai.nb_players_begin += 1
                                ai.is_fork_ok = False
                    elif len(ai.commands) != 0 and "message" not in buf:
                        if ai.asker == True:
                            ai.fork_countdown += 1
                        print(f"RECEIVE: From {ai.commands[0][:-1]} = {buf}")
                        handle_response(buf, ai)
        algorithm(ai)
