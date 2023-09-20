#include "../include/huffman_structures.h"

#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>



// STATUS: verified.
/* Huffman tree functions.  */

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


// STATUS: verify.
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



/* Heap functions (STATUS: verified). */

_heap *
_initialize_heap() {
    _heap * h = calloc(1, sizeof(struct _heap));
    h->data = calloc(256, sizeof(_huffman_tree_node *));
    return h;
}


// TODO: verify.
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
    
    _huffman_tree_node * min = q->data[0];
    if (q->size == 1) {
        q->data[0] = NULL;
        q->size = 0;
    }

    else {
        q->data[0] = q->data[q->size - 1]; 
        q->data[q->size - 1] = NULL;
        q->size = q->size - 1;
        _heapify_nondesc(q, 0);
    }

    return min;
}


// TODO: verify.
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


void
_delete_heap(_heap * h, bool delete_contents) {
    if (delete_contents == true)
        for (int i = 0; i < h->size; ++i)
            free(h->data[i]);
    free(h->data);
    free(h);
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


bool
_queue_is_full(_queue * q) {
    return q->size == 256 ? true : false;
}


void
_enqueue(_queue * q, _huffman_tree_node * n) {
    assert(q->size != 256);
    assert(n != NULL);

    q->data[q->tail] = n;
    q->tail = (q->tail + 1) % 256;
    ++(q->size);
}


_huffman_tree_node *
_dequeue(_queue * q) {
    assert(_queue_is_empty(q) == false);

    _huffman_tree_node * n = q->data[q->head];
    q->data[q->head] = NULL;
    q->head = (q->head + 1) % 256;
    --(q->size);
    return n;
}



/* Huffman codes lengths map functions.  */

_huffman_codes_lengths_map *
_evaluate_huffman_codes_lengths(_huffman_tree * t) {
    _huffman_codes_lengths_map * cl = \
        calloc(1, sizeof(_huffman_codes_lengths_map));
    cl->lengths = calloc(256, 1);
    memset(cl->lengths, 0, 256);

    /* ... */
}

void
_delete_huffman_codes_lengths_map();



/* Canonical huffman codebook functions.  */

_canonical_huffman_codebook *
_create_canonical_huffman_codebook(_huffman_codes_lengths_map *);

void
_delete_canonical_huffman_codebook(_canonical_huffman_codebook *);



// // STATUS: todo.
// /* Huffman codes list and canonical huffman codebook functions.  */

// /* TODO.  */
// _huffman_codes_lengths_map *
// _initialize_canonical_huffman_codebook(uint8_t b) {
//     _huffman_codes_lengths_map * cb = \
//         calloc(1, sizeof(_huffman_codes_lengths_map));
    
//     return cb;
// }


// /* TODO.  */
// _huffman_codes_lengths_map *
// _create_canonical_huffman_codebook(_huffman_tree * t) {

// }


// void
// _sort_canonical_huffman_codebook(_huffman_codes_lengths_map * cb) {

// }



// // STATUS: TODO.
// /* Huffman codes lists functions.  */

// _canonical_huffman_codebook *
// _initialize_huffman_codes_list() {
//     _canonical_huffman_codebook * cl = calloc(1, sizeof(_canonical_huffman_codebook));
//     cl->codes = calloc(256, sizeof(_prefix_code *));
//     return cl;
// }


// _canonical_huffman_codebook *
// _create_huffman_codes_list(_huffman_codes_lengths_map * cb) {
//     _canonical_huffman_codebook * cl = \
//         _initialize_huffman_codes_list();

//     for (int i = 0; i < 256; ++i) {
//         size_t index = cb->alphabet[i];
//         cl->codes[index] = cb->codes[i];
//     }
    
//     return cl;
// }



// STATUS: verified.
/* Prefix code functions.  */

_prefix_code *
_initialize_prefix_code(uint8_t bytes) {
    _prefix_code * c = calloc(1, sizeof(_prefix_code));
    c->bytes     = bytes;
    c->length    = 0;
    c->data      = calloc(bytes, 1);
    memset(c->data, 0, bytes);
    return c;
}


_prefix_code *
_duplicate_prefix_code(_prefix_code * c) {
    _prefix_code * cd = calloc(1, sizeof(_prefix_code));
    cd->bytes = c->bytes;
    cd->length = c->length;
    cd->data = calloc(c->bytes, 1);
    for (uint8_t i = 0; i < cd->bytes; ++i)
        cd->data[i] = c->data[i];
    return cd;
}


void
_delete_prefix_code(_prefix_code * c) {
    free(c->data);
    free(c);
}



// STATUS: todo.
/* Codes queue functions.  */

_codes_queue *
_initialize_codes_queue() {
    _codes_queue * cq = calloc(1, sizeof(_codes_queue));
    cq->size = 0;
    cq->head = 0;
    cq->tail = 0;
    cq->data = calloc(256, sizeof(_prefix_code *));
    return cq;
}


bool
_codes_queue_is_empty(_codes_queue * cq) {
    return cq->size == 0 ? true : false;
}


int
_enqueue_code(_codes_queue * cq, _prefix_code * c) {
    if (cq->size == 256)
        return 1;
    cq->data[cq->tail] = c;
    cq->tail = cq->tail == 255 ? 0 : cq->tail + 1;
    ++(cq->size);
    return 0;
}


_prefix_code *
_dequeue_code(_codes_queue * cq) {
    if (cq->size == 0)
        return NULL;
    _prefix_code * c = cq->data[cq->head];
    cq->data[cq->head] = NULL;
    cq->head = cq->head == 255 ? 0 : cq->head + 1;
    --(cq->size);
    return c;
}



/* Other.  */

void
_swap(_huffman_tree_node * p, _huffman_tree_node * q) {
    /* TODO.  */
}
