#include "../include/huffman.h"

#include <stdio.h>
#include <stdint.h>
#include <limits.h>     /* For UINT_MAX.  */


/* TODO: review error handling policy. 
 * TODO: what rb and wb in fopen do?  */
int
compress_file(const char * src_path, const char * save_as_path) {
    FILE * file_input;
    if ((file_input = fopen(src_path, "r")) == 0) {
        fprintf(stderr, "Error: could not open the file %s.\n",
            src_path);
        return 1;
    }

    FILE * file_output;
    if ((file_output = fopen(save_as_path, "w")) == 0) {
        fprintf(stderr, "Error: could not create the file %s.\n",
            save_as_path);
        fclose(file_input);
        return 2;
    }

    _huffman_tree * t = _huffman(file_input);
    _huffman_codes_list * cl = _create_huffman_codes_list(t);

    /* ... compress ... */
    
    fclose(file_input);
    fclose(file_output);
    return 0;
}


/* TODO.  */
int
decompress_file(const char * src_path, const char * save_as_path) {
    /* ... open src file ... */
    
    /* ... create dest file ... */

    /* ... build huffman tree ... */

    /* ... decompress ... */

    return 0;
}


static _huffman_tree *
_huffman(FILE * f) {
    _heap * h = _count_char_frequencies(f);

    while (h->size > 1) {
        _huffman_tree_node * l = _extract_minimum(h);
        _huffman_tree_node * r = _extract_minimum(h);

        _huffman_tree_node * s = \
            _create_huffman_tree_node('\0', l->value + r->value);
        s->left = l; s->right = r;

        _insert(h, s);        
    }

    _huffman_tree * t = _create_huffman_tree(_minimum(h));
    free(h->data);
    free(h);

    return t;
}


static _heap *
_count_char_frequencies(FILE * f) {
    /* Rewind the file to ensure full statistics.  */
    rewind(f);

    uint_t * counts = calloc(256, sizeof(uint_t));

    int c;
    while((c = fgetc(f)) != EOF) {
        if (counts[c] == UINT_MAX)
            for (uint16_t i = 0; i < 256; ++i)
                if (counts[i] > 1) counts[i] /= 2;        
        ++counts[c];
    }

    /* Create _heap structure using collected statictics.  */
    _heap * h = _initialize_heap();
    for (uint16_t i = 0; i < 256; ++i) {
        if (counts[i] == 0)
            continue;

        _huffman_tree_node * n = \
            _create_huffman_tree_node((char)i, counts[i]);

        _insert(h, n);
    }

    return h;
}
