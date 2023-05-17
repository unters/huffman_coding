#ifndef HUFFMAN_UINT8_T_QUEUE
#define HUFFMAN_UINT8_T_QUEUE

#include <stdint.h>
#include <stdbool.h>


typedef unsigned int uint_t;

/* Implementation of queue for uint8_t arrays, that represent huffman 
 * codes. Memo: this implementation of queue has no capacity frield because
 * its capacity is fixed and equals to 256.  */
struct _uint8_t_queue {
    uint8_t * data;
    uint_t size, head, tail;
};

typedef struct _uint8_t_queue _uint8_t_queue;


/* Functions.  */

_uint8_t_queue *
_initialize_uint8_t_queue();

bool
_uint8_t_queue_is_empty(_uint8_t_queue *);

int
_enqueue_uint8_t(_uint8_t_queue *, uint8_t); 

uint8_t 
_dequeue_uint8_t(_uint8_t_queue *);

#endif
