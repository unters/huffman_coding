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

struct _pair {
    char c;
    uint8_t length;
};

struct _ordered_pairs_list {
    _pair ** data;
};

struct _prefix_code {
    uint8_t * data;
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
typedef struct _pair                        _pair;
typedef struct _ordered_pairs_list          _ordered_pairs_list;



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

void
_delete_queue(_queue * q, bool delete_contents);



/* Huffman codes lengths map functions.  */

_huffman_codes_lengths_map *
_evaluate_huffman_codes_lengths(_huffman_tree *);

void
_delete_huffman_codes_lengths_map(_huffman_codes_lengths_map *);



/* Canonical huffman codebook functions.  */

_canonical_huffman_codebook *
_create_canonical_huffman_codebook(_huffman_codes_lengths_map *);

void
_delete_canonical_huffman_codebook(_canonical_huffman_codebook *);



/* _pair functions.  */

_pair *
_create_pair(char, uint8_t);

/* Returns true if p1 is less than p2.  */
bool
_compare_pairs(_pair * p1, _pair * p2);

void
_swap_pairs(_pair *, _pair *);

void
_qsort(_ordered_pairs_list *);



/* _ordered_pairs_list functions.  */

_ordered_pairs_list *
_create_ordered_pairs_list(_huffman_codes_lengths_map *);

void
_delete_ordered_pairs_list(_ordered_pairs_list * pl, bool delete_contents);



/* Prefix code functions.  */

/* Intitialize _prefix_code structure capable of holding code of given
 * length.  */
_prefix_code *
_initialize_prefix_code(uint8_t length);

/* Create canonical huffman code of length `length` that follows prefix
 * code `prev`.  */
_prefix_code *
_generate_next_prefix_code(_prefix_code * prev, uint8_t length);

void
_delete_prefix_code(_prefix_code *);



// STATUS: DEPRECATED.
/* Codes queue functions.  */

_codes_queue *
_initialize_codes_queue();

bool
_codes_queue_is_empty(_codes_queue *);

int
_enqueue_code(_codes_queue *, _prefix_code *);

_prefix_code *
_dequeue_code(_codes_queue *);
