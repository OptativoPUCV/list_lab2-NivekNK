#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) 
{
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    return new;
}

List * createList() 
{
    List * new = (List *)malloc(sizeof(List));
    new->head = NULL;
    new->tail = NULL;
    new->current = NULL;

    return new;
}

void * firstList(List * list) 
{
    if (list->head && list->head->data)
    {
        list->current = list->head;
        return (void*)list->current->data;
    }

    return NULL;
}

void * nextList(List * list) 
{
    if (list->current) 
    { 
      if (list->current->next && list->current->next->data)
      {
          list->current = list->current->next;
          return (void*)list->current->data;
      }
    }

    return NULL;
}

void * lastList(List * list) 
{
    if (list->tail && list->tail->data)
    {
        list->current = list->tail;
        return (void*)list->current->data;
    }

    return NULL;
}

void * prevList(List * list) 
{
    if (list->current) 
    { 
      if (list->current->prev && list->current->prev->data)
      {
          list->current = list->current->prev;
          return (void*)list->current->data;
      }
    }

    return NULL;
}

void pushFront(List * list, const void * data) 
{
    Node *node = createNode(data);

    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
}

void pushBack(List * list, const void * data) 
{
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) 
{
    Node *node = createNode(data);

    node->prev = list->current;

    if (list->current == list->tail)
    {
        list->tail->prev = list->current;
        list->tail = node;
    }
    else
    {
        node->next = list->current->next;
        list->current->next->prev = node;
    }
    list->current->next = node;
}

void * popFront(List * list) 
{
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) 
{
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
    void *data = (void*)list->current->data;
    Node *aux = createNode(list->current->next->data);

    if (list->current == list->head)
    {
        list->current = list->head->next;
        aux = list->head->next->next;
        list->head->next = aux;
        //aux->next = list->head->next->next;
        //aux->prev = NULL;
        //list->head = aux;
    }
    else
    {
        aux->next = list->current->next->next;
        aux->prev = list->current->prev;
        list->current = aux;
    }
    //list->current = aux;

    return data;
}

void cleanList(List * list) 
{
    while (list->head != NULL) {
        popFront(list);
    }
}