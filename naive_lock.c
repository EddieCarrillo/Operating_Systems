typedef struct __lock_t {int flag;} lock_t;


void init(lock_t *mutex){
 // 0 ->Lock is available, 1->Held
 mutex->flag = 0;
}

void lock(lock_t mutex){
   //Make the thread wait until the lock is available
   while (mutex->flag == 1) // Test the flag
   ; //Spin wait do nothing

  mutex->flag = 1; // Now se the flag
}


void unlock(lock_t *mutex){
    mutex->flag = 0;

}
