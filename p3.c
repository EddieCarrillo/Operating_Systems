#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char*argv[]){
   printf("hello world (pid:%d)", (int)getpid());
   int rc = fork(); //Create a new process
   if (rc < 0){ //This means that the fork failed
      fprintf(stderr, "fork failed\n");
   }else if (rc == 0){ //We are in the child process
      printf("hello, I am child (pid:%d)\n", (int)getpid());
      char * myargs[3];
      myargs[0] = strdup("w3");
      myargs[1] = strdup("p3.c");
      myargs[2] = NULL;
      execvp(myargs[0], myargs); //runs word count
   }else {
       int rc_wait = wait(NULL);
       printf("hello, I am parent of %d (rc_wait: %d) (pid:%d)\n", rc, rc_wait, (int)getpid());
} 
return 0;



}
