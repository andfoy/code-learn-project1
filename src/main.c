#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cbmp.h"

int main() {
    BMP* bmp = bopen("../cat.bmp");

    unsigned int x, y, width, height;
    unsigned char r, g, b;

    // Gets image width in pixels
    width = get_width(bmp);

    // Gets image height in pixels
    height = get_height(bmp);

    printf("Image: %u x %u\n", height, width);

    char* to_write = "Example string";
    int str_size = strlen(to_write);

    int str_pos = 0;
    int pix_pos = 0;
    char cur_char = to_write[str_pos];

    // Mask: 1000 (8) 0000 (0)
    unsigned char mask = 0x80;
    int displ = 7;
    unsigned char* pixels = (unsigned char*) bmp->pixels;
    int pix_cnt = 0;

    while(str_pos < str_size && pix_pos < (width * height * 4)) {
        unsigned char pix = pixels[pix_pos];

        if(mask == 0) {
            mask = 0x80;
            str_pos++;
            cur_char = to_write[str_pos];
            displ = 7;
        }

        if(str_pos == str_size) {
            break;
        }

        /** TAREA: 
         * 1. Recuperar el n-esimo bit en cur_char usando mask y una operación binaria.
         * 2. Mover ese bit `displ` veces a la derecha para que quede en la primera posición.  
         * 3. Limpiar el primer bit en pix.
         * 4. Insertar el bit de la instrucción 2 en el primer bit de pix, reasignando en pix.
         * **/

        pixels[pix_pos] = pix;
        pix_pos++;
        pix_cnt++;
        if(pix_cnt == 3) {
            pix_pos++;
            pix_cnt = 0;
        }
    }

    // Write bmp contents to file
    bwrite(bmp, "../out.bmp");

    // Free memory
    bclose(bmp);

    return 0; 
}
