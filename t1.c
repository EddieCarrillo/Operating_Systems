#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0;


// mythread()
//Adds 1 to counter repeatedly



void* mythread(void *arg){
  //Print out the string passed in
   printf("%s: begin\n", (char *) arg);
   int i;
   for (i = 0; i < 1000000; i++){
       counter = counter +1;
   }

   printf("%s: done\n", (char*)arg);

   return NULL;
}


//main()


//launches two threads (pthread_create)
//Then waits for them 

int main(int argc, char*argv[]){
	pthread_t p1, p2;
        printf("main: begin (counter=%d)\n", counter);
        pthread_create(&p1, NULL, mythread, "A");
        pthread_create(&p2, NULL, mythread, "B");
    
       //Join waits for the threads to finish
       pthread_join(p1, NULL);
       pthread_join(p2, NULL);

       printf("main: done with both (counter = %d)\n", counter);
 
}
