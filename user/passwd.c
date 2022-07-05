#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#define USERSIZE 17
#define PASSSIZE 65 
#define HASHSIZE 33
#define UIDSIZE 3

int main(int argc, char **argv)
{
	setuid(0);
	char username[USERSIZE], password[PASSSIZE], oldpassword[PASSSIZE], confirm[PASSSIZE], correcthash[HASHSIZE], oldhash[HASHSIZE], newhash[HASHSIZE], uid[UIDSIZE];
	int isNewUser = 0;
	int fd, dstatus, newuid = 10;

	mkdir("shadow");
	chdir("shadow"); 
    fd = open("newuid", O_RDWR);
    if (fd == -1) {
        fd = open("newuid", O_CREATE);
        fd = open("newuid", O_RDWR);
        fprintf(fd, "%d", newuid);
        close(fd);
    }
    else {
        read(fd, uid, UIDSIZE);
        newuid = atoi(uid) + 1;
        close(fd);
    }

	if(argc >= 2) strcpy(username, argv[1]);
	else
	{
	    printf("Username: ");
	    read(0, username, sizeof(username));
	    username[strlen(username)-1] = '\0';
	}
    dstatus = chdir(username);
	if (dstatus == -1)
	{
	    isNewUser = 1;
	}
    else
    {
        fd = open("passhash", O_RDWR);
	    printf("Current Password: ");
	    read(0, oldpassword, sizeof(oldpassword));
	    oldpassword[strlen(oldpassword)-1] = '\0';
	    MD5Get(oldpassword, sizeof(oldpassword), oldhash);
        read(fd, correcthash, sizeof(correcthash));
        if(strcmp(oldhash, correcthash) != 0) 
        {
            printf("Wrong Password!!\n");
            exit(1);
        }
    }

	printf("New Password: ");
	read(0, password, sizeof(password));
	password[strlen(password)-1] = '\0';
	printf("Confirm Password: ");
    read(0, confirm, sizeof(confirm));
	confirm[strlen(confirm)-1] = '\0';
    if(strcmp(password, confirm) != 0)
    {
        printf("Passwords don't match!!\n");
        exit(1);
    }
    else
    {
        MD5Get(password, sizeof(password), newhash);
    }

	if (isNewUser == 1)
	{
	    mkdir(username);
	    chdir(username);
		fd = open("passhash", O_CREATE);
		fd = open("passhash", O_RDWR);
	    fprintf(fd, "%s", newhash);
	    close(fd);
	    fd = open("uid", O_CREATE);
	    fd = open("uid", O_RDWR);
	    fprintf(fd, "%d", newuid);
	    close(fd);
        chdir("..");
        unlink("newuid");
        fd = open("newuid", O_CREATE);
        fd = open("newuid", O_RDWR);
        fprintf(fd, "%d", newuid);
        close(fd);
	}
	else
	{
	    close(fd);
	    if(unlink("passhash") < 0) printf("Change of password failed!!\n");
	    fd = open("passhash", O_CREATE);
	    fd = open("passhash", O_RDWR);
	    fprintf(fd, "%s", newhash);
	}

	close(fd);
	exit(0);
}
