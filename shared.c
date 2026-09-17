#include<stdio.h>
#include<ctype.h>

#include "shared.h"

void dump(const unsigned char *data, const size_t length) {
    for (size_t i = 0; i < length; i += 16) {
        size_t row_length = (length - i > 16) ? 16 : (length - i);

        for (size_t j = 0; j < 16; j++) {
            if (j < row_length) {
                printf("%02x ", data[i + j]);
            } else {
                printf("   ");
            }
        }
        
        printf("| ");
        for (size_t j = 0; j < row_length; j++) {
            unsigned char c = data[i + j];
            printf("%c", isprint((unsigned char)c) ? c : '.');
        }
        
        printf("\n");
    }
}
