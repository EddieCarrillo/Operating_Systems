#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0){
      fprintf(stderr, "fork failed\n");
    }else if (rc == 0){
        printf("hello, I am child (pid:%d)\n",(int)getpid());
     }else {
        int rc_wait = wait(NULL);
        printf("hello, I am a parent of %d (rc_wait:%d) pid: %d\n",rc, rc_wait, (int)getpid());
}
}
