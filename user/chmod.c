#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv) {
    if(argc != 3) {
      printf("Usage: chmod permision filename\n");
      exit(-1);
    }
    else {
      int perm = atoi(argv[1]);
      chmod(perm, argv[2]);
      exit(0);
    }
}
