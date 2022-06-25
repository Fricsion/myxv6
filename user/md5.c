#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

void main(void) {
        char password[33];
        char passhash[33];
        gets(password, 32);
        MD5Get(password, strlen(password), passhash);
        printf("%s\n", passhash);
        exit(0);
}
