#include <stdio.h>
#include <unistd.h>


int main()
{
    int ret;
    char c;

    printf("pid: %d\n", getpid());

    // block for stdin:
    ret = read( 0, 
                &c, 
                sizeof(c));
    return ret;
}
