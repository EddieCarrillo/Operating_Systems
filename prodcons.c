//producer:consumer system


int buffer;
int count = 0; //Initially empty
int loops; //Must initialize somewhere
mutex_t mutex;


void put(int value){
    assert(count == 0);
    count = 1;
    buffer = value;
}


void get(){
   assert(count == 1);
   count = 0;
   return buffer;
}


void* producer(void *arg){
    int i;
    int loops = (int) arg;
    for(i = 0; i <loops; i++){
         pthread_mutex_lock(&mutex);//Doing a put() is a critical section operation
         if (count == 1) //We can't put anymore items in our buffer, therefore we need to wait for other thread to get()
             pthread_cond_wait(&cond, &mutex) //Pass the address of the mutex so we can let other thread control the lock
         put(i); //After putting the item into the list we can signal to the other thread, that it can perform a get()
         pthread_cond_signal(&cond);
         pthread_mutex_unlock(&mutex);//we are finished with the critical section of the code 
         
    }
}


void*consumer(void*arg){
   int i;
   while (1){
       pthread_mutex_lock(&mutex); //critical section
       if (count == 0) //We pass in the address of the lock b/c we are going to release for the other thread.
           pthread_cond_wait(&cond, &mutex); //we can only get an item if there is something in the container
       int tmp = get();   
       pthread_cond_signal(&cond);
       pthread_mutex_unlock(&mutex); //We have finished the with critical section therefore we can release the lock
       printf("%d\n", tmp);
   }

}
