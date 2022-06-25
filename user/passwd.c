#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#define PASSSIZE 33 

int main(int argc, char **argv)
{
	char username[9], password[PASSSIZE], oldpassword[PASSSIZE], confirm[PASSSIZE], correctpass[PASSSIZE];
	int isNewUser = 0;
	int fd;

	mkdir("shadow");
	chdir("shadow");

	if(argc == 2) strcpy(username, argv[1]);
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
		fd = open(username, O_CREATE);
		fd = open(username, O_RDWR);
	}
    else
    {
	    printf("Current Password: ");
	    read(0, oldpassword, sizeof(oldpassword));
        read(fd, correctpass, sizeof(correctpass));
        if(strcmp(oldpassword, correctpass) != 0) 
        {
            printf("Wrong Password!!\n");
            exit(0);
        }
    }

	printf("New Password: ");
	read(0, password, sizeof(password));
	printf("Confirm Password: ");
    read(0, confirm, sizeof(confirm));
    if(strcmp(password, confirm) != 0) printf("Passwords don't match!!");

	if (isNewUser == 1)
	{
	    fprintf(fd, "%s", password);
	    exit(0);
	}
	else
	{
	    close(fd);
	    if(unlink(username) < 0) printf("Change of password failed!!");
	    fd = open(username, O_CREATE);
	    fd = open(username, O_RDWR);
	    fprintf(fd, "%s", password);
	}

	close(fd);
	exit(0);
}
