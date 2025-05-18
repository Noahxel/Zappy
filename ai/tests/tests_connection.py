##
## EPITECH PROJECT, 2023
## tests_connection.py
## File description:
## test connection.
##

import pytest
from unittest.mock import Mock
from src import connection

def test_send_team_name():
    sock = Mock()
    sock.recv.return_value = b"WELCOME"
    sock.sendall = Mock()
    name = "team"
    connection.send_team_name(sock, name)
    assert sock.recv.call_count == 1
    assert sock.sendall.call_args[0][0] == (name + "\n").encode('utf-8')

def test_send_team_name_invalid_response():
    sock = Mock()
    sock.recv.return_value = b"INVALID"
    name = "team"
    with pytest.raises(ValueError) as e:
        connection.send_team_name(sock, name)
    assert str(e.value) == "Expected 'WELCOME', received: 'INVALID'"
