/*
*  Rockstar's Queue
*      This Queue is used for thead interaction.
*      Thread A should be limited to the function AddToQueue and thread B to the functions RemoveFirstInQueue and GetFirstInQueue
*      No need for mutual exclusion by design.
*
*  This source code is offered for use in the public domain. You may
*  use, modify or distribute it freely.
*
*  This code is distributed in the hope that it will be useful but
*  WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
*  DISCLAIMED. This includes but is not limited to warranties of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
*/
#pragma once

#pragma pack(push, 1)
struct Queue
{
    int *queue;
    int head;
    int tail;
    int size;
};
#pragma pack(pop)

static_assert(sizeof(Queue) == 0x10, "Incorrect struct size: Queue");



inline Queue* InitialiseQueue(Queue* q, int size)
{
    q->queue = new int[size];
    q->size = size;
    q->head = q->tail = 0;
    return q;
}

inline void FinalizeQueue(Queue* q)
{
    delete[] q->queue;
    q->size = q->head = q->tail = 0;
}



inline void AddToQueue(Queue* q, int i)
{
    q->queue[q->tail] = i;
    q->tail = (q->tail + 1) % q->size;
}

inline int GetFirstInQueue(Queue* q)
{
    return (q->head == q->tail ? -1 : q->queue[q->head]);
}

inline void RemoveFirstInQueue(Queue* q)
{
    if (q->head != q->tail)
        q->head = (q->head + 1) % q->size;
}
