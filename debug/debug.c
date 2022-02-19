#include "debug.h"
#include "../mm/memory.h"

int exec(   int pid, 
            ptr program,
            unsigned int program_size)
{
    return 0;
}

int breakpoint( int pid, 
                ptr addr,
                int (*callback)(void*))
{
    
    unsigned char int3 = 0xcc;
    unsigned char old;

    // save old instruction
    memory_read(pid, 
                addr,
                (ptr)&old,
                1);

    // write int3 instead
    memory_write(pid, 
                 &int3,
                 (ptr)addr,
                 1);

    // wait for the breakpoint to hit
    printf("waiting for the breapoint to hit...\n");
    int wstatus;
    int ret;
    ret = waitpid(pid, &wstatus, 0);
    if (ret == -1){
        // TODO: what should i do here?
        printf("wtf?\n");
    }
    printf("wstatus: %x\n", wstatus);

    // restore old instruction
    memory_write(pid, 
                 (ptr)&old,
                 addr,
                 1);
    return 0;
}
