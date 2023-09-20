#ifndef HUFFMAN_STRUCTURES
#define HUFFMAN_STRUCTURES

#include <stdbool.h>
#include <stdint.h>


typedef unsigned int uint_t;



/* Structures.  */

struct _huffman_tree_node {
    char    key;
    uint_t  value;  // TODO: change uint_t to (unsigned) long.

    _huffman_tree_node * left;
    _huffman_tree_node * right;
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

struct _huffman_tree {
    _huffman_tree_node * root;
    uint8_t height;
};

/* Maps ASCII characters to corresponding code lengths.  */
struct _huffman_codes_lengths_map {
    uint8_t * lengths;
};

/* Wrapper around array of codes. Maps ASCII value of a character into its
 * code. `codes` has fixed size of 256 elements.  */
struct _canonical_huffman_codebook {
    _prefix_code ** codes;
};

struct _prefix_code {
    uint8_t * data;
    /* Number of bytes in data array.  */
    uint8_t bytes;
    /* Number of significant bits.  */
    uint8_t length;
};

/* Implementation of queue for uint8_t arrays, that represent huffman 
 * codes. Memo: this implementation of queue has no capacity field because
 * its capacity is fixed and equals to 256.  */
struct _codes_queue {
    _prefix_code ** data;
    uint8_t size, head, tail;
};



// Sort typedefs. 
typedef struct _huffman_tree_node           _huffman_tree_node;
typedef struct _huffman_tree                _huffman_tree;
typedef struct _huffman_codes_lengths_map   _huffman_codes_lengths_map;
typedef struct _canonical_huffman_codebook  _canonical_huffman_codebook;
typedef struct _heap                        _heap;
typedef struct _queue                       _queue;
typedef struct _prefix_code                 _prefix_code;
typedef struct _codes_queue                 _codes_queue;



/* Huffman tree functions.  */

_huffman_tree_node *
_create_huffman_tree_node(char, uint_t);

_huffman_tree *
_create_huffman_tree(_huffman_tree_node *);

/* Height stands for number of levels in the huffman tree.  */
uint8_t
_height(_huffman_tree_node *);



/* Heap functions. */

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

void
_delete_heap(_heap * h, bool delete_contents);



/* Queue functions. */

_queue *
_initialize_queue();

bool
_queue_is_empty(_queue *);

/* TODO: There is no need in this function.  */
bool
_queue_is_full(_queue *);

/* Returns 0 on success, -1 otherwise.  */
void
_enqueue(_queue *, _huffman_tree_node *);

/* Returns _huffman_tree_node on success, NULL otherwise.  */
_huffman_tree_node *
_dequeue(_queue *);



/* Huffman codes lengths map functions.  */

_huffman_codes_lengths_map *
_evaluate_huffman_codes_lengths(_huffman_tree *);

void
_delete_huffman_codes_lengths_map();



/* Canonical huffman codebook functions.  */

_canonical_huffman_codebook *
_create_canonical_huffman_codebook(_huffman_codes_lengths_map *);

void
_delete_canonical_huffman_codebook(_canonical_huffman_codebook *);



// /* Canonical huffman codebook functions.  */

// _huffman_codes_lengths_map *
// _initialize_canonical_huffman_codebook(uint8_t);

// _huffman_codes_lengths_map *
// _create_canonical_huffman_codebook(_huffman_tree *);

// void
// _sort_canonical_huffman_codebook(_huffman_codes_lengths_map *);

// void
// _delete_canonical_huffman_codebook();



// /* Huffman codes list functions.  */

// _canonical_huffman_codebook *
// _initialize_huffman_codes_list();

// _canonical_huffman_codebook *
// _create_huffman_codes_list(_huffman_codes_lengths_map *);



/* Prefix code functions.  */

_prefix_code *
_initialize_prefix_code(uint8_t);

_prefix_code *
_duplicate_prefix_code(_prefix_code *);

void
_delete_prefix_code(_prefix_code * c);



/* Codes queue functions.  */

_codes_queue *
_initialize_codes_queue();

bool
_codes_queue_is_empty(_codes_queue *);

int
_enqueue_code(_codes_queue *, _prefix_code *);

_prefix_code *
_dequeue_code(_codes_queue *);



/* Other.  */

void
_swap(_huffman_tree_node *, _huffman_tree_node *);



/* Temporary.  */

/* Recursively fill array of huffman codes "codes". depth stands for n'th 
 * node height (counting from top). path stores bits representing path to
 * node n in huffman tree. memb_size represents number of bytes, needed to 
 * store longest huffman code for given huffman tree.  */
static void
_get_huffman_codes(struct _huffman_tree_node * n, uint8_t *** codes,
    uint8_t * path, uint8_t depth, uint8_t memb_size);

#endif
