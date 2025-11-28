#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cbmp.h"

int main() {
    BMP* bmp = bopen("../out.bmp");

    unsigned int x, y, width, height;
    unsigned char r, g, b;

    // Gets image width in pixels
    width = get_width(bmp);

    // Gets image height in pixels
    height = get_height(bmp);

    printf("Image: %u x %u\n", height, width);

    int expected_len = 14;
    char* to_read = calloc((expected_len + 1), sizeof(char));

    int str_pos = 0;
    int pix_pos = 0;
    char cur_char = to_read[str_pos];

    // Mask: 1000 (8) 0000 (0)
    unsigned char mask = 0x1;
    int displ = 7;
    unsigned char* pixels = (unsigned char*) bmp->pixels;
    int pix_cnt = 0;

    while(str_pos < expected_len && pix_pos < (width * height * 4)) {
        unsigned char pix = pixels[pix_pos];

        if(displ == -1) {
            str_pos++;
            if(str_pos == expected_len) {
                break;
            }
            cur_char = to_read[str_pos];
            displ = 7;
        }

        unsigned char pix_bit = (pix & mask) << displ;
        cur_char = cur_char | pix_bit;
        displ--;

        to_read[str_pos] = cur_char;
        pix_pos++;
        pix_cnt++;
        if(pix_cnt == 3) {
            pix_pos++;
            pix_cnt = 0;
        }
    }

    printf("Stored: %s\n", to_read);
    free(to_read);

    // Write bmp contents to file
    bwrite(bmp, "../out.bmp");

    // Free memory
    bclose(bmp);

    return 0; 
}
