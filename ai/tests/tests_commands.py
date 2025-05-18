##
## EPITECH PROJECT, 2023
## tests_commands.py
## File description:
## test commands.
##

import pytest
from unittest.mock import call, Mock
from src import commands

@pytest.fixture
def mock_args():
    return Mock(commands=[])

def test_send_command_without_parameter(mock_args):
    command = commands.Commands.FORWARD
    commands.send_command(command, mock_args)
    assert mock_args.commands == ['Forward\n']
    assert mock_args.sock.sendall.call_args == call('Forward\n'.encode("utf-8"))

def test_send_command_with_parameter(mock_args):
    command = commands.Commands.BROADCAST
    parameter = "Hello, world!"
    commands.send_command(command, mock_args, parameter)
    assert mock_args.commands == ['Broadcast Hello, world!\n']
    assert mock_args.sock.sendall.call_args == call('Broadcast Hello, world!\n'.encode("utf-8"))
