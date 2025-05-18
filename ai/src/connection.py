##
## EPITECH PROJECT, 2023
## connection.py
## File description:
## connection
##

import socket
import sys

def create_connection(port, machine):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.connect((machine, port))
    except Exception as e:
        print(f"Could not connect to {machine} on port {port}: {e}")
        sys.exit(84)
    return s

def send_team_name(sock, name):
    data = sock.recv(1024).decode('utf-8')
    if data.strip() != "WELCOME":
        raise ValueError("Expected 'WELCOME', received: '{}'".format(data))
    sock.sendall((name + "\n").encode('utf-8'))

def receive_client_num(sock, slots, map):
    data = sock.recv(1024).decode('utf-8')
    splitted = data.split("\n")
    if (len(splitted) > 1):
        for i in range(0, len(splitted)):
            if splitted[i].count(" ") > 0 and len(splitted[i].split(" ")) == 2:
                map = receive_map_size(sock, splitted[i])
            elif splitted[i].isdigit():
                slots = int(splitted[i].strip())
    if map == 0:
        if slots == 0:
            slots = int(data.strip())
        data = sock.recv(1024).decode('utf-8')
        if data.count('\n') > 0:
            temp = data.split('\n')
            for i in range(0, len(temp)):
                if temp[i].count(" ") == 1 and temp[i].split(" ")[0].isdigit() == True:
                    map = receive_map_size(sock, temp[i])
        else:
            map = receive_map_size(sock, data)
    else:
        print("No data received")

def receive_map_size(sock, data):
    parts = data.split()
    if len(parts) != 2:
        raise ValueError("Expected format 'int int' : map size, received: '{}'".format(data))
    if all(part.isdigit() for part in parts):
        response_tuple = tuple(int(part) for part in parts)
        print(f"map_size = {response_tuple}\n", end="")
        return response_tuple
