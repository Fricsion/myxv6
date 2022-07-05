#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void main(void) {
    int pid = getpid();
    int uid = getuid(pid);
    printf("UID: %d\n", uid);
    exit(0);
}
