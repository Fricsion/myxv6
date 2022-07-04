#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void main(void) {
    printf("\x1b[2J\x1b[1;1H");
    exit(0);
}
