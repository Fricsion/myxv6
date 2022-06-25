#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#define USERSIZE 17
#define PASSSIZE 65 
#define HASHSIZE 33

int main(int argc, char **argv)
{
	char username[USERSIZE], password[PASSSIZE], oldpassword[PASSSIZE], confirm[PASSSIZE], correcthash[HASHSIZE], oldhash[HASHSIZE], newhash[HASHSIZE];
	int isNewUser = 0;
	int fd;

	mkdir("shadow");
	chdir("shadow");

	if(argc >= 2) strcpy(username, argv[1]);
	else
	{
	    printf("Username: ");
	    read(0, username, sizeof(username));
	    username[strlen(username)-1] = '\0';
	}
    fd = open(username, O_RDWR);
	if (fd == -1)
	{
	    isNewUser = 1;
	}
    else
    {
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
		fd = open(username, O_CREATE);
		fd = open(username, O_RDWR);
	    fprintf(fd, "%s", newhash);
	}
	else
	{
	    close(fd);
	    if(unlink(username) < 0) printf("Change of password failed!!\n");
	    fd = open(username, O_CREATE);
	    fd = open(username, O_RDWR);
	    fprintf(fd, "%s", newhash);
	}

	close(fd);
	exit(0);
}
