#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

#include "common.h"

// ------------------------------------------------------------------------------
// ptrace wrappers
// ------------------------------------------------------------------------------

// #define ptr (unsigned long)
typedef unsigned long ptr;

int pause_tracee(int pid)
{
    int ret = 0;
    ret = kill(pid, SIGSTOP);

    if (ret == -1){
        perror("interrupt()");
        return -1;
    }

    wait(NULL);

    return 0;
}

int resume_tracee(int pid)
{
    return ptrace(PTRACE_CONT, pid, 0, 0);
}

int attach(int pid)
{
    int ret = 0;
    ret = ptrace(PTRACE_ATTACH, pid, 0, 0);    
    if (ret == -1) return ret;

    wait(NULL);

    return resume_tracee(pid);
}

int detach(int pid)
{
    return ptrace(PTRACE_DETACH, pid, 0, 0);
}

int _poke(int pid, ptr addr, unsigned int value)
{
    return ptrace(PTRACE_POKEDATA, pid, addr, value);
}

int poke(int pid, ptr addr, unsigned int value)
{
    int ret = 0;

    ASSERT((pause_tracee(pid) != -1),
            "Failed to pause tracee\n");

    ret = _poke(pid, addr, value);

    resume_tracee(pid);

    return ret;

fail:
    return -1;
}

int _peek(int pid, ptr addr, unsigned int* out)
{
    unsigned int ret = ptrace(PTRACE_PEEKDATA, pid, addr, 0);

    if (ret != -1){
        *out = ret;
        return 0;
    }
    return -1;
}

int peek(int pid, ptr addr, unsigned int* out)
{
    int ret = 0;

    ASSERT((pause_tracee(pid) != -1),
            "Failed to pause tracee\n");

    ret = _peek(pid, addr, out);

    resume_tracee(pid);

    return ret;

fail:
    return -1;
}

// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// common functions
// ------------------------------------------------------------------------------
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

// ------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    int ret = 0;
    int pid = 465;

    ASSERT_TO(fail, (attach(pid) != -1), "Failed to attach to pid: %d\n", pid);

    // ptr addr = 0x7ffd6333a000;
    ptr addr = 0x5615ce0ac000;
    unsigned char buf[sizeof(int) * 2] = {0};

    ret = memory_read(pid, addr, (ptr)buf, sizeof(buf));
    if (ret == -1){
        LOG("Failed to write()\n");
        goto fail_detach;
    }
    promody_hexdump(buf, sizeof(buf));

    buf[1] = 1;
    ret = memory_write(pid, (ptr)buf, addr, sizeof(buf));
    if (ret == -1){
        LOG("Failed to write()\n");
        goto fail_detach;
    }

    ret = memory_read(pid, addr, (ptr)buf, sizeof(buf));
    if (ret == -1){
        LOG("Failed to read()\n");
        goto fail_detach;
    }
    promody_hexdump(buf, sizeof(buf));

end:
    detach(pid);
    return 0;

fail_detach:
    printf("errno: %d\n", errno);
    goto end;
fail:
    return 0;
}
