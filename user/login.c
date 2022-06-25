#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#define PASSSIZE 33

int main(void) {
    int fd;
    char username[9], password[PASSSIZE], correctpass[PASSSIZE];
    mkdir("shadow");
    chdir("shadow");

    printf("\x1b[2J\x1b[1;1H");
    printf("Group 6 xv6 Login: ");
    read(0, username, sizeof(username));
    username[strlen(username)-1] = '\0';

    fd = open(username, O_RDONLY);
    if(fd == -1) {
        printf("User doesn't exist. Proceeding to create a user.\n");
        chdir("..");
        char *passwd[] = {"passwd", username, 0};
        exec("passwd", passwd);
    }
    else {
        printf("Password: ");
        read(0, password, sizeof(password));
        read(fd, correctpass, sizeof(correctpass));
        if(strcmp(password, correctpass) == 0) {
            char *sh[] = {"sh", 0};
            printf("Login success!!\n");
            chdir("..");
            exec("sh", sh);
        }
        else {
            printf("Login failed!!\n");
            exit(1);
        }
    }

    exit(0);
}
