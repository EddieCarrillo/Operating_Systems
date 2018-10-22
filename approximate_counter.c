typdef struct __counter_t {
   int global; //global counter
   pthread_mutex_t glock; //global lock;
   int local[NUMCPUS]; //local counters
   pthread_mutex_t llock[NUMCPUS]; //local locks
   int threshold; // Update frequency
} counter_t;




void init(counter_t *c, int threshold){
    c->threshold = threshold;
    c->global = 0; //Init global counter to zero
    pthread_mutex_init(&c->glock, NULL);
    int i;
    for (i = 0; i < NUMCPUS; i++){
        c->local[i] = 0; //Init all the local counters to zero
        pthread_mutex_init(c->llocal[i]); //Init all the local locks
    }
}


//update: usually, just increment the local counter value. IF the local counter variable passes threshold, then transfer to global
void update(counter_t*c, int threadID, int amt){
    int cpu = threadID % NUMCPUS;
    pthread_mutex_lock(&c->llock[cpu]);
    c->llocal[cpu] += amt;
   if (c->local[cpu] >= c->threshold){
      //If the local variable has passed the threshold, then update the global counter
       pthread_mutex_lock(&c->glock);
       c->global += c->llocal[cpu];
       pthread_mutex_unlock(&c->glock);
   }

   pthread_mutex_unlock(&c->llock[cpu]);
  
}


int get(counter_t *c){
    pthread_mutex_lock(&c->glock);
    int val = c->global;
    pthread_mutex_unlock(&c->glock);

    return val; // Only approximate

}
