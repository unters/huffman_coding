#ifndef HUFFMAN
#define HUFFMAN

#include <stdio.h>

#include "./huffman_structures.h"


/* Compress file with filename src_path and save it as file with filename
 * save_as_path.  */
int
compress_file(const char * src_path, const char * save_as_path);

/* Decompress file with filename src_path and save it as file with filename
 * save_as_path.  */
int
decompress_file(const char * src_path, const char * save_as_path);


static _huffman_tree *
_huffman(FILE *);

static _heap *
_count_char_frequencies(FILE *);

#endif
