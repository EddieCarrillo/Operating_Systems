typedef struct __lock_t{
   int flag;
   int guard;
   queue_t *q;
} lock_t;


void lock_init(lock_t *m){
   m->flag = 0;
   m-> guard = 0;
   queue_init(m->q);
}


void lock(lock_t *m){

   //A 1 means not in queue and not in use
    //Used to set the guard to 1 Not in use.
    while (TestAndSet(&(m->guard), 1) == 1)
     ;
   //If the lock is free, set the flag and turn off the guard
   if (m->flag == 0){
   	m->flag = 1;
        m->guard = 0;//In use now
   }else {
       queue_add(m->q, gettid());
       m->guard = 0; //In queue now
       park(); //Put thread to sleep as it waits it's turn
   }
}

void unlock(lock_t *m){
   while(TestAndSet(&m->guard, 1) == 1)
     ; //Acquire guard lock by spinning
    if (queue_empty(m->q))
        m->flag = 0; //The lock is free
    else 
        unpark(queue_remove(m->q)); //Hold onto lock for next thread

    m->guard = 0; //Lock i
}
