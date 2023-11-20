#include "kernel/types.h"   // some data type
#include "user/user.h"  // system call

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(2, "usage: sleep [ticks num]\n");
    exit(1);
  }
  // atoi sys call guarantees return an integer
  int ticks = atoi(argv[1]);
  int ret = sleep(ticks);
  exit(ret);
}