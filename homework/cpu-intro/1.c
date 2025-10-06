#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// When the parent process forks the new one all the memory space is copied over
// From there every process has it's own memory, that's way the variable x it's not overwritten, nor data-races

int main(int argc, char *argv[]){
    int x = 100;
    int rc = fork();
    if (rc < 0){
        fprintf(stderr,"fork failed\n");
        exit(1);
    }
    else if (rc==0){
        printf("child (x=%d)\n",x);
        x = 50;
    }else {
        printf("parent (x=%d)\n",x);
        x = 30;
        int rc_wait = wait(NULL);
        printf("parent after wait (x=%d)\n",x);
    }
    return 0;
}
