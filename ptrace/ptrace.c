#include <signal.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

#include "../common.h"
#include "ptrace.h"


int pause_tracee(int pid)
{
    int ret = 0;
    ret = kill(pid, SIGSTOP);

    if (ret == -1){
        perror("interrupt()");
        return -1;
    }

    int wstatus;
    ret = waitpid(pid, &wstatus, 0);
    if (ret == -1){
        // TODO: what should i do here?
        printf("wtf?\n");
        return -1;
    }
    if (!WIFSTOPPED(wstatus)){
        // TODO: what should i do here?
        printf("wtf?\n");
        return -1;
    }

    return 0;
}

int resume_tracee(int pid)
{
    int ret = 0;
    ret = ptrace(PTRACE_CONT, pid, 0, 0);
    if (ret == -1) return -1;

    // TODO: do i need to check whether or not the tracee had continued?
    return 0;
}

int attach(int pid)
{
    int ret = 0;
    ret = ptrace(PTRACE_ATTACH, pid, 0, 0);    
    if (ret == -1) return ret;

    int wstatus;
    ret = waitpid(pid, &wstatus, 0);
    if (ret == -1){
        // TODO: what should i do here?
        printf("wtf?\n");
        return -1;
    }
    if (!WIFSTOPPED(wstatus)){
        // TODO: what should i do here?
        printf("wtf?\n");
        return -1;
    }

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
