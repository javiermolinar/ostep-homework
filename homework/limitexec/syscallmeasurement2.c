#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/time.h>

enum { NS_PER_SECOND = 1000000000 };

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
}

int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments\n");
        return EXIT_FAILURE;
    }
    int iters = atoi(argv[1]);
    int fd = open("./syscallmeasurement.c",O_RDONLY);
    char buffer[0];


    struct timespec start, finish, delta;
    clock_gettime(CLOCK_REALTIME, &start);
    for (int i=0; i<iters;i++){
        read(fd, buffer, 0);
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    sub_timespec(start, finish, &delta);
    double time_per_iter = (delta.tv_sec * 1e9 + delta.tv_nsec) / (double)iters;
    printf("It takes %.3f nanoseconds\n", time_per_iter);


    return 0;
}
