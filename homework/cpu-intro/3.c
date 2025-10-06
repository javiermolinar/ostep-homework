#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

//A simple way to write Hello, Goodbye without using the wait() syscall is by making the parent process to sleep one second. This will switch the context to the child process
int main(int argc, char *argv[]){
    int rc = fork();
    if (rc < 0){
        fprintf(stderr,"fork failed\n");
        exit(1);
    }
    else if (rc==0){
        printf("hello\n");
    }else {
        sleep(1);
        printf("goodbye\n");
    }
    return 0;
}
