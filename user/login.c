#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#define USERSIZE 17
#define PASSSIZE 65
#define HASHSIZE 33
#define UIDSIZE 3

int main(void) {
    setuid(0);
    int fd, dstatus, uid;
    char username[USERSIZE], password[PASSSIZE], correcthash[HASHSIZE], passhash[HASHSIZE], rawuid[UIDSIZE];

    mkdir("shadow");
    chdir("shadow");

    printf("\x1b[2J\x1b[1;1H");
    printf("Group 6 xv6 Login: ");
    read(0, username, sizeof(username));
    username[strlen(username)-1] = '\0';

    dstatus = chdir(username);
    if(dstatus == -1) {
        printf("User doesn't exist. Proceeding to create a user.\n");
        char *passwd[] = {"passwd", username, 0};
        chdir("..");
        exec("passwd", passwd);
    }
    else {
        fd = open("passhash", O_RDONLY);
        printf("Password: ");
        read(0, password, sizeof(password));
        password[strlen(password)-1] = '\0';
        MD5Get(password, sizeof(password), passhash);
        read(fd, correcthash, sizeof(correcthash));
        if(strcmp(passhash, correcthash) == 0) {
            close(fd);
            fd = open("uid", O_RDONLY);
            read(fd, rawuid, sizeof(rawuid));
            uid = atoi(rawuid);
            close(fd);
            setuid(uid);
            char *sh[] = {"sh", 0};
            printf("\x1b[2J\x1b[1;1H");
            printf("Login success!!\n");
            chdir("../..");
            exec("sh", sh);
        }
        else {
            printf("Login failed!!\n");
            sleep(3);
            close(fd);
            exit(1);
        }
    }

    exit(0);
}
