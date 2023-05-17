#include "../include/huffman_tree_node.h"

#include <stddef.h>
#include <stdbool.h>


/* Huffman tree (node) functions.  */

_huffman_tree_node *
_create_huffman_tree_node(char key, uint_t value) {
    _huffman_tree_node * n = \
        calloc(1, sizeof(_huffman_tree_node));
    
    n->key = key; n->value = value;
    n->left = NULL; n->right = NULL;

    return n;
}


_huffman_tree *
_create_huffman_tree(_huffman_tree_node * n) {
    _huffman_tree * t = calloc(1, sizeof(_huffman_tree));
    t->root = n;
    t->height = _height(n);
    return t;
}


uint8_t
_height(_huffman_tree_node * n) {
    _queue * q = _initialize_queue();
    _enqueue(q, n);

    uint8_t height = 0;
    while (!(_queue_is_empty(q))) {
        for (uint_t i = 0; i < q->size; ++i) {
            _huffman_tree_node * n = _dequeue(q);

            if (n->left != NULL)
                _enqueue(q, n->left);

            if (n->right != NULL)
                _enqueue(q, n->right);
        }

        ++height;
    }

    free(q->data);
    free(q);
    return height;
}


/* Heap functions. */

_heap *
_initialize_heap() {
    _heap * h = calloc(1, sizeof(struct _heap));
    h->data = calloc(256, sizeof( _huffman_tree_node *));
    return h;
}


void
_heapify_nondesc(_heap * q, unsigned int i) {
    if (q->size == 0)
        return;
        
    uint_t smallest = i;
    uint_t l = i * 2 + 1;
    uint_t r = i * 2 + 2;

    if (l < q->size)
        if (q->data[l]->value < q->data[i]->value)
            smallest = l;

    if (r < q->size)
        if (q->data[r]->value < q->data[smallest]->value)
            smallest = r;
        
    if (smallest != i) {
        _swap(q->data[i], q->data[smallest]);
        _heapify_nondesc(q, smallest);
    }
}


_huffman_tree_node *
_minimum(_heap * q) {
    return q->data[0];
}


_huffman_tree_node *
_extract_minimum(_heap * q) {
    if (q->size < 1)
        return NULL;
    
    if (q->size == 1) {
        _huffman_tree_node * min = q->data[0];
        q->size = 0;
        return min; 
    }

    _huffman_tree_node * min = q->data[0];
    q->data[0] = q->data[q->size - 1]; 
    q->size = q->size - 1;
    _heapify_nondesc(q, 0);
    return min;
}


void
_insert(_heap * h, _huffman_tree_node * n) {
    /* Proceed insertion.  */
    h->data[h->size] = n;
    h->size += 1;

    uint_t i = h->size - 1;
    uint_t parent_index = (i - 1) / 2;

    while (i > 0 && h->data[parent_index]->value > h->data[i]->value)
    {
        _swap(h->data[parent_index], h->data[i]);
        i = parent_index;
        parent_index = (i - 1) / 2;
    }
}


/* Queue functions.  */

_queue *
_initialize_queue() {
    _queue * q = calloc(1, sizeof(_queue));
    q->data = calloc(256, sizeof(_huffman_tree_node *));
    q->size = 0; q->head = 0; q->tail = 0;
    return q;
}


bool
_queue_is_empty(_queue * q) {
    return q->size == 0 ? true : false;
}


int
_enqueue(_queue * q, _huffman_tree_node * n) {
    if (q->size == 256)
        return 1;
    q->data[q->tail] = n;
    q->tail = q->tail == 255 ? 0 : q->tail + 1;
    ++(q->size);
    return 0;
}


_huffman_tree_node *
_dequeue(_queue * q) {
    if (_queue_is_empty(q))
        return NULL;
    _huffman_tree_node * n = q->data[q->head];
    q->data[q->head] = NULL;
    q->head = q->head == 255 ? 0 : q->head + 1;
    --(q->size);
    return n;
}




