#include "../include/huffman_codes_list.h"

#include <stddef.h>

#include "../include/huffman_tree_node.h"
#include "../include/uint8_t_queue.h"


/* Huffman codes list functions.  */

_huffman_codes_list *
_create_huffman_codes_list(_huffman_tree * t) {
    _canonical_huffman_codebook * cb = \
        _create_canonical_huffman_codebook(t);
    _huffman_codes_list * cl = \
        _convert_huffman_codebook_to_codes_list(cb);

    free(cb->alphabet);
    free(cb->codes);
    free(cb->codes_lengths);
    free(cb);
    return cl;
}


_huffman_codes_list *
_convert_huffman_codebook_to_codes_list(_canonical_huffman_codebook * cb) {
    _huffman_codes_list * cl = calloc(1, sizeof(_huffman_codes_list));
    cl->codes = calloc(256, sizeof(uint8_t *));
    cl->codes_lengths = calloc(256, 1);
    cl->bytes_per_code = cb->bytes_per_code;

    memset(cl->codes_lengths, 0, 256);
    for (uint_t i = 0; i < cb->size; ++i) {
        uint8_t character = cb->alphabet[i];
        cl->codes[character] = cb->codes[i];
        cl->codes_lengths[character] = cb->codes_lengths[i];
    }

    return cl;
}


/* Canonical huffman codebook functions.  */

/* TODO.  */
_canonical_huffman_codebook *
_create_canonical_huffman_codebook(_huffman_tree * t) {
    /* Initialize huffman codebook.  */
    _canonical_huffman_codebook * cb = \
        calloc(1, sizeof(_canonical_huffman_codebook));
    cb->bytes_per_code  = max((t->height - 1) / 8, 1);
    cb->alphabet        = calloc(256, 1);
    cb->codes_lengths   = calloc(256, 1);
    cb->size            = 0;
    cb->capacity        = 265;

    /* Traverse the huffman tree to figure out code lengths.  */
    _queue         * q    = _initialize_queue();
    _uint8_t_queue * uq   = _initialize_uint8_t_queue(); 
    _enqueue(q, t->root);
    _enqueue_uint8_t(uq, 0);
    while(!_queue_is_empty(q)) {
        _huffman_tree_node * n = _dequeue(q);
        uint8_t u = _dequeue_uint8_t(uq);

        if (n->left == NULL) {
            cb->alphabet[cb->size] = n->key;
            cb->codes_lengths[cb->size] = u;
            cb->size += 1;
            continue;
        }
    
        _enqueue(q, n->left);
        _enqueue_uint8_t(uq, u + 1);

        _enqueue(q, n->right);
        _enqueue_uint8_t(uq, u + 1);
    } 

    free(q->data);
    free(q);
    free(uq->data);
    free(uq);

    /* Sort codebook.  */
    _qsort_canonical_huffman_codebook(cb);
    
    /* Build canonical codes.  */
    cb->codes = calloc(cb->size, sizeof(uint8_t *));

    cb->codes[0] = calloc(cb->bytes_per_code, 1);
    for (uint_t i = 0; i < cb->bytes_per_code; ++i)
        cb->codes[0][i] = 0;

    for (uint_t i = 1; i < cb->size; ++i) {
        cb->codes[i] = calloc(cb->bytes_per_code, 1);
        /* i'th code is based on i - 1'th code.  */
        for (size_t j = 0; j < cb->bytes_per_code; ++j)
            cb->codes[i][j] = cb->codes[i - 1][j];

        /* Increment.  */
        uint_t k = 0;
        while(++(cb->codes[i][k]) == 0) ++k;

        /* TODO: check.  */
        /* Shift if neccessary.  */
        uint8_t shifts = cb->codes_lengths[i] - cb->codes_lengths[i - 1];
        for (uint_t j = cb->bytes_per_code - 1; j > 0; --j)
            cb->codes[i][j] = (cb->codes[i][j] << shifts) | \
                (cb->codes[i][j - 1] >> (8 - shifts));
        cb->codes[i][0] <<= shifts;
    }

    return cb;
}


void
_qsort_canonical_huffman_codebook(_canonical_huffman_codebook * cb) {
    if (cb->size == 0)
        return;
    size_t q = _partition(cb, 0, cb->size);
    _qsort(cb, 0, q);
    _qsort(cb, q + 1, cb->size); 
}


void 
_qsort(_canonical_huffman_codebook * cb, size_t p, size_t r) {
    if (p >= r)
        return;
    int q = _partition(cb, p, r);
    _qsort(cb, p, q);
    _qsort(cb, q + 1, r);
}


size_t
_partition(_canonical_huffman_codebook * cb, size_t p, size_t r) {
    uint8_t len = cb->codes_lengths[r - 1];
    size_t i = p;
    for (size_t j = p; j < r - 1; ++j)
        if (cb->codes_lengths[j] <= len) {
            uint8_t temp_len = cb->codes_lengths[j];
            cb->codes_lengths[j] = cb->codes_lengths[i];
            cb->codes_lengths[i] = temp_len;

            char temp_char = cb->alphabet[j];
            cb->alphabet[j] = cb->alphabet[i];
            cb->alphabet[i++] = temp_char;
        }
    
    if (i < r - 1) {
        uint8_t temp_len = cb->codes_lengths[r - 1];
        cb->codes_lengths[r - 1] = cb->codes_lengths[i];
        cb->codes_lengths[i] = temp_len;

        char temp_char = cb->alphabet[r - 1];
        cb->alphabet[r - 1] = cb->alphabet[i];
        cb->alphabet[i] = temp_char;
    }

    return i;
}
