#ifndef MEMORY_H
#define MEMORY_H

#include "../types.h"

int memory_read(int pid, 
                ptr src, 
                ptr dst, 
                unsigned int size);

int memory_write(   int pid, 
                    ptr src, 
                    ptr dst, 
                    unsigned int size);

int memory_breakpoint(  int pid, 
                        ptr addr, 
                        unsigned int size,
                        int (*callback)(void*));

#endif
