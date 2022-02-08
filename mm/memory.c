#include "memory.h"

#include "../ptrace/ptrace.h"
#include "../common.h"

int memory_read(int pid, 
                ptr src, 
                ptr dst, 
                unsigned int size)
{
    int copied = -1;

    ASSERT((pause_tracee(pid) != -1),
            "Failed to pause tracee\n");

    int i;
    for (i = 0; i < size; i += sizeof(unsigned int)){ 
        if (_peek(pid, src, (unsigned int*)dst) == -1){
            goto fail_peeking;
        }
        dst += sizeof(unsigned int);
        src += sizeof(unsigned int);
        copied += sizeof(unsigned int);
    }

fail_peeking:
    resume_tracee(pid);
fail:
    return copied;
}

int memory_write(   int pid, 
                    ptr src, 
                    ptr dst, 
                    unsigned int size)
{
    int copied = -1;

    ASSERT((pause_tracee(pid) != -1),
            "Failed to pause tracee\n");

    int i;
    for (i = 0; i < size; i += sizeof(unsigned int)){ 
        if (_poke(pid, dst, *((unsigned int *)src)) == -1){
            goto fail_poking;
        }
        src += sizeof(unsigned int);
        dst += sizeof(unsigned int);
        copied += sizeof(unsigned int);
    }

fail_poking:
    resume_tracee(pid);
fail:
    return copied;
}

int memory_breakpoint(  int pid, 
                        ptr addr, 
                        unsigned int size,
                        int (*callback)(void*))
{
    return 0;
}
