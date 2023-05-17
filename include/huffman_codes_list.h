#ifndef HUFFMAN_CODES_LIST
#define HUFFMAN_CODES_LIST

#include <stdint.h>

#include "huffman_tree_node.h"


typedef unsigned int uint_t;

struct _huffman_codes_list {
    uint8_t **  codes;
    uint8_t *   codes_lengths;
    uint8_t     bytes_per_code;    
};

struct _canonical_huffman_codebook {
    uint8_t * alphabet;
    uint8_t ** codes;
    uint8_t * codes_lengths;
    uint8_t bytes_per_code;
    uint_t size, capacity;
};

typedef struct _huffman_codes_list          _huffman_codes_list;
typedef struct _canonical_huffman_codebook  _canonical_huffman_codebook;


/* Huffman codes list functions.  */

_huffman_codes_list *
_create_huffman_codes_list(_huffman_tree *);

_huffman_codes_list *
_convert_huffman_codebook_to_codes_list(_canonical_huffman_codebook *);


/* Canonical huffman codebook functions.  */

_canonical_huffman_codebook *
_create_canonical_huffman_codebook(_huffman_tree *);

void
_qsort_canonical_huffman_codebook(_canonical_huffman_codebook *);

void
_qsort(_canonical_huffman_codebook *, size_t, size_t);

size_t
_partition(_canonical_huffman_codebook *, size_t, size_t);

#endif
