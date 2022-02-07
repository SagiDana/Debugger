#include <stdio.h>
#include <string.h>

#include "common.h"


void promody_log(char* msg){
    FILE* f = fopen(LOG_FILE_PATH, "a+");
    if (!f) return;

    fwrite(msg, 1, strlen(msg), f);

    fclose(f);
}

void promody_hexdump(unsigned char* buf, unsigned int size){
    int i,j;
    for (i = 0; i < size / COL_SIZE; i++){
        for (j = 0; j < COL_SIZE; j++){
            printf("%02x ", buf[(i*COL_SIZE) + j]);
        }
        printf("\n");
    }

    // print rest if need be.
    if (size % COL_SIZE != 0){
        for (j = 0; j < size % COL_SIZE; j++){
            printf("%02x ", buf[(size / COL_SIZE) + j]);
        }
        printf("\n");
    }
}
