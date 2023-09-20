#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>

#include "../include/huffman.h"
#include "../include/utility.h"


int
main(int argc, char ** argv) {
    int     action_code = 0;   /* 1 - compression, 2 - decompression.  */
    bool    silent_mode = false;
    char *  filename;

    {
        struct option longopts[] = {
            {"compress", required_argument, 0, 'c'},

            {"decompress", required_argument, 0, 'd'},

            {"silent", no_argument, 0, 's'},

            {0, 0, 0, 0}
        };

        int optchar;
        while (-1 != (optchar = \
            getopt_long(argc, argv, ":c:d:s", longopts, NULL))) 
        {
            switch (optchar) {
                case 'c':
                    action_code = 1;
                    filename = optarg;
                    break;
                case 'd':
                    action_code = 2;
                    filename = optarg;
                    break;
                case 's':
                    silent_mode = true;
                    break;
                default:
                    print_usage();
                    return -1;
            }
        }
    }

    /* TODO: Add stats for nonsilent mode: compression rate and time.
     * TODO: Change if statement to switch statement.  */
    switch (action_code) {
        case 1:
            compress_file(filename, add_huf_extension(filename));
            break;
        case 2:
            int return_code = \
                decompress_file(filename, remove_huf_extension(filename));
            if (return_code == 1)
                printf("Error - could not decompress given file.\n");
                return 1;
            break;
        default:
            print_usage();
    } 

    free(filename);

    return 0;
}
