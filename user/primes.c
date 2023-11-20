#include "kernel/types.h"   // some data type
#include "user/user.h"  // system call

void sieve(int in, int my_prime){
    int pipes[2];
    pipe(pipes);
    int num;
    printf("prime %d\n", my_prime);

    while(read(in, &num, 4) > 0){
        // pipe has num
        // printf("prime %d\n", my_prime);
        if(num % my_prime != 0){
            write(pipes[1], &num, 4);
        }
    }

    close(in);
    close(pipes[1]);

    if(read(pipes[0], &num, 4) > 0){
        // have prime
        if(fork() == 0){
            sieve(pipes[0], num);
        } else {
            wait(0);
        }
    }

    exit(0);
}

int main(){
    int pipes[2];
    pipe(pipes);

    for(int i=2; i<=35; i++){
        write(pipes[1], &i, 4);
    }
    close(pipes[1]);
    sieve(pipes[0], 2);
    exit(0);

}