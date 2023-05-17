#include "../include/uint8_t_queue.h"

#include <stddef.h>
#include <stdbool.h>


_uint8_t_queue *
_initialize_uint8_t_queue() {
    _uint8_t_queue * uq = calloc(1, sizeof(_uint8_t_queue));
    uq->size = 0;
    uq->head = 0;
    uq->tail = 0;
    uq->data = calloc(256, 1);
    return uq;
}


bool
_uint8_t_queue_is_empty(_uint8_t_queue * uq) {
    return uq->size == 0 ? true : false;
}


int
_enqueue_uint8_t(_uint8_t_queue * uq, uint8_t c) {
    if (uq->size == 256)
        return 1;
    uq->data[uq->tail] = c;
    uq->tail = uq->tail == 255 ? 0 : uq->tail + 1;
    ++(uq->size);
    return 0;
}


uint8_t 
_dequeue_uint8_t(_uint8_t_queue * uq) {
    if (uq->size == 0)
        return NULL;
    uint8_t u = uq->data[uq->head];
    uq->data[uq->head] = NULL;
    uq->head = uq->head == 255 ? 0 : uq->head + 1;
    --(uq->size);
    return u;
}

