#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void main(void) {
    int pid = getpid();
    printf("PID: %d\n", pid);
    int uid = getuid(pid);
    printf("UID: %d\n", uid);
    printf("Setting UID to 5...\n");
    setuid(5);
    uid = getuid(pid);
    printf("UID: %d\n", uid);
    exit(0);
}
