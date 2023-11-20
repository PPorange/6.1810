#include "kernel/types.h"   // some data type
#include "user/user.h"  // system call

int main(int argc, char *argv[]) {
    int pid;
    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);
    char buff[1] = {'a'};

    if(fork() == 0){
        // child 
        pid = getpid();
        close(pipe1[0]);
        close(pipe2[1]);
        read(pipe2[0], buff, 1);
        write(pipe1[1], buff, 1);
        printf("%d: received ping\n", pid);
        exit(0);
    } else {
        // parent
        pid = getpid();
        close(pipe1[1]);
        close(pipe2[0]);
        write(pipe2[1], buff, 1);
        wait(0);
        read(pipe1[0], buff, 1);
        printf("%d: received pong\n", pid);
        exit(0);
    }
}