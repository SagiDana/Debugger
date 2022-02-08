#ifndef PTRACE_H
#define PTRACE_H

#include "../types.h"

int pause_tracee(int pid);
int resume_tracee(int pid);
int attach(int pid);
int detach(int pid);
int _poke(int pid, ptr addr, unsigned int value);
int poke(int pid, ptr addr, unsigned int value);
int _peek(int pid, ptr addr, unsigned int* out);
int peek(int pid, ptr addr, unsigned int* out);

#endif
