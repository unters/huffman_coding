#ifndef HUFFMAN_TREE_NODE
#define HUFFMAN_TREE_NODE

#include <stdint.h>
#include <stdbool.h>


typedef unsigned int uint_t;

struct _huffman_tree_node {
    char    key;
    uint_t  value;

    _huffman_tree_node * left;
    _huffman_tree_node * right;
};

struct _huffman_tree {
    _huffman_tree_node * root;
    uint8_t height;
};

/* Implementation of heap for _huffman_tree_node variables. Memo:
 * has no capacity field because its capacity is intentionally fixed and
 * equals to 256.  */
struct _heap {
    _huffman_tree_node ** data;
    uint_t size;
};

/* Implementation of queue for _huffman_tree_node variables. Memo:
 * this implementation of queue has no capacity field because its capacity
 * is intentionally fixed and equals to 256.  */
struct _queue {
    _huffman_tree_node ** data;
    uint_t size, head, tail;
};

typedef struct _huffman_tree_node   _huffman_tree_node;
typedef struct _huffman_tree        _huffman_tree;
typedef struct _heap                _heap;
typedef struct _queue               _queue;


/* Huffman tree (node) functions.  */

_huffman_tree_node *
_create_huffman_tree_node(char, uint_t);

uint8_t
_height(_huffman_tree_node *);

_huffman_tree *
_create_huffman_tree(_huffman_tree_node *);


/* Heap functions.  */

_heap *
_initialize_heap();

void
_heapify_nondesc(_heap *, uint_t);

_huffman_tree_node *
_minimum(_heap *);

_huffman_tree_node *
_extract_minimum(_heap *);

void
_insert(_heap *, _huffman_tree_node *);


/* Queue functions.  */

_queue *
_initialize_queue();

bool
_queue_is_empty(_queue *);

/* Returns 0 on success, -1 otherwise.  */
int
_enqueue(_queue *, _huffman_tree_node *);

/* Returns _huffman_tree_node on success, NULL otherwise.  */
_huffman_tree_node *
_dequeue(_queue *);

#endif
