#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>

#define FALSE (0)
#define TRUE (!(FALSE))

#define BETWEEN(x, a, b)    ((x) >= (a) && ((x) <= (b)))

#define LOG_FILE_PATH "/tmp/promody.log"

void promody_log(char* msg);

#define LOG(...) do{                \
    char buff[1024*8];                 \
    sprintf(buff, __VA_ARGS__);     \
    promody_log(buff);                   \
}while(0)

#define ASSERT(expr, ...) if(!expr) {LOG(__VA_ARGS__); goto fail;}
#define ASSERT_TO(label, expr, ...) if(!expr) {LOG(__VA_ARGS__); goto label;}

#define LENGTH(x) (sizeof(x) / sizeof(x[0]))

#define COL_SIZE (8)

void promody_hexdump(unsigned char* buf, unsigned int size);

#endif
