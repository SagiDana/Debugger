#include <stdio.h>
#include <errno.h>

#include "common.h"
#include "types.h"

#include "ptrace/ptrace.h"
#include "debug/debug.h"
#include "mm/memory.h"


// ------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    int ret = 0;
    int pid = 2493;

    ASSERT_TO(fail, (attach(pid) != -1), "Failed to attach to pid: %d\n", pid);

    ptr addr = 0x7f6cdad55000;
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
