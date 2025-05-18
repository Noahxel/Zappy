/*
** EPITECH PROJECT, 2023
** queue_management.c
** File description:
** queue_management
*/

#include <stdlib.h>
#include <stdio.h>

#include "command.h"
#include "tools.h"

command_t get_head(queue_t * const queue)
{
    if (queue->size == 0)
        return (command_t){
            NULL, NULL, NULL, 0
            };
    return queue->head->command;
}

void enqueue(queue_t * const queue, const command_t command)
{
    node_t *new_node = malloc(sizeof(node_t));
    CERROR(new_node == NULL, "malloc");
    new_node->command = command;
    new_node->next = NULL;

    if (queue->size == 0) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
    queue->size++;
}

void dequeue(queue_t * const queue)
{
    if (queue->size == 0)
        return;
    node_t* old_head = queue->head;
    command_t command = old_head->command;
    if (command.arg)
        free(command.arg);
    queue->head = old_head->next;
    if (!queue->head)
        queue->tail = NULL;
    free(old_head);
    queue->size--;
}

void free_queue(queue_t * const queue)
{
    while (queue->size != 0)
        dequeue(queue);
}
