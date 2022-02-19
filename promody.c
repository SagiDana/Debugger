#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "common.h"
#include "types.h"

#include "ptrace/ptrace.h"
#include "debug/debug.h"
#include "mm/memory.h"


enum action{
    READ_MEMORY,
    WRITE_MEMORY,
    BREAKPOINT,
};

typedef struct{
    int pid;
    enum action act;
    ptr addr;
}args_t;

void print_usage()
{
    char* usage = 
        "Usage:\n"
        "promody <pid> <action> <addr>\n"
        ;
    printf("%s", usage);
}

int parse_args( int argc, 
                char* argv[],
                args_t* args)
{
    if (argc <= 3) return -1;

    args->pid = atoi(argv[1]);
    args->act = atoi(argv[2]);
    args->addr = strtoul(argv[3], NULL, 16);

    return 0;
}

int action_breakpoint(args_t* args)
{
    if (attach(args->pid) == -1){
        printf("Failed to attach to pid: %d\n", args->pid);
        return -1;
    }

    breakpoint(args->pid, args->addr, NULL);

    detach(args->pid);
    return 0;
}

int main(int argc, char* argv[])
{
    args_t args = {0};

    if (parse_args(argc, argv, &args)) {
        print_usage();
        return 0;
    }
    printf("pid: %d\n", args.pid);
    printf("action: %d\n", args.act);
    printf("addr: 0x%lx\n", args.addr);

    if (args.act == BREAKPOINT){
        return action_breakpoint(&args);
    }

    // ASSERT_TO(fail, (attach(pid) != -1), "Failed to attach to pid: %d\n", pid);

    // ptr addr = 0x7f6cdad55000;
    // unsigned char buf[sizeof(int) * 2] = {0};

    // ret = memory_read(pid, addr, (ptr)buf, sizeof(buf));
    // if (ret == -1){
        // LOG("Failed to write()\n");
        // goto fail_detach;
    // }
    // promody_hexdump(buf, sizeof(buf));

    // buf[1] = 1;
    // ret = memory_write(pid, (ptr)buf, addr, sizeof(buf));
    // if (ret == -1){
        // LOG("Failed to write()\n");
        // goto fail_detach;
    // }

    // ret = memory_read(pid, addr, (ptr)buf, sizeof(buf));
    // if (ret == -1){
        // LOG("Failed to read()\n");
        // goto fail_detach;
    // }
    // promody_hexdump(buf, sizeof(buf));

// end:
    // detach(pid);
    // return 0;

// fail_detach:
    // printf("errno: %d\n", errno);
    // goto end;
// fail:
    return 0;
}
