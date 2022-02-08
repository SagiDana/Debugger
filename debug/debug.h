#ifndef DEBUG_DEBUG_H
#define DEBUG_DEBUG_H

#include "../types.h"

int breakpoint( int pid, 
                ptr addr,
                int (*callback)(void*));

#endif
