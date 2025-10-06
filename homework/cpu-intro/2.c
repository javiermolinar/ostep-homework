#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

// In my tests, Hello parent goes always first. In theory there is no deterministic guarantee which process will write into the file fist
int main(int argc, char *argv[]){
    int fd = open("./test.output",O_CREAT|O_WRONLY|O_TRUNC);

    int rc = fork();
    if (rc < 0){
        fprintf(stderr,"fork failed\n");
        exit(1);
    }
    else if (rc==0){
         write(fd,"Hello children\n",15);
    }else {
        write(fd,"Hello parent\n",13);
    }
    close(fd);
    return 0;
}
