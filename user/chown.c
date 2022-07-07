#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv) {
    if(argc != 3) {
      printf("Usage: chown newuid filename\n");
      exit(-1);
    }
    else {
      int newuid= atoi(argv[1]);
      chown(newuid, argv[2]);
      exit(0);
    }
}
