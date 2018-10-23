//conditional vars practice

int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t = PTHREAD_COND_INITIALIZER;


void thr_exit(){
   //Do work of child thread
    Pthread_mutex_lock(&m);
    done = 1;
    //Signals other threads that use conditional variable for waiting a signal
    Pthread_cond_signal(&c);
    Pthread_mutex_unlock(&m);
}


void *child(void* arg){
   //Work of child thread
    printf("child\n");
    thr_exit();

    return NULL;
}


void thr_join(){
    pthread_mutex_lock(&m);
    //Stops waiting once thread recieves signal from child thread
    while (done == 0)
         pthread_cond_wait(&c, &mk);
   
    pthread_mutex_unlock(&m);
}


int main(int argc, char*argv[]){
    printf("parent: begin\n");
    pthread_t p;
    pthread_create(&p, NULL, child, NULL);
    thr_join();
    printf("parent: end\n");
    return 0;
}
