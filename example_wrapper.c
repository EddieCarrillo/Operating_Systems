Pthred_mutex_lock(pthread_mutex_t *mutex){
  int rc = pthread_mutex_lock(mutex);
  assert(rc == 0);

}


//Examples

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

Pthread_mutex_lock(&lock);


while(ready == 0)
    Pthread_cond_wait(&cond,&lock);
Pthread_mutex_unlock(&lock);


//Other code to signal above thread

Pthread_mutex_lock(&lock);
ready = 1;
Pthread_cond_signal(&cond);
Pthread_mutex_unlock(&lock);
