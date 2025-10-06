#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/time.h>

int main(int argc, char *argv[]){
    struct timeval tv;
    struct timezone tz;
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments\n");
        return EXIT_FAILURE;
    }
    int iters = atoi(argv[1]);
    int fd = open("./syscallmeasurement.c",O_RDONLY);
    char buffer[0];


    gettimeofday(&tv,&tz);
    long long start = tv.tv_sec * 1000000LL + tv.tv_usec;
    for (int i=0; i<iters;i++){
        read(fd, buffer, 0);
    }
    gettimeofday(&tv,&tz);
    long long end = tv.tv_sec * 1000000LL + tv.tv_usec;
    long takes = (end-start)/iters;
    printf("It takes %lu microseconds\n", takes);

    return 0;
}
