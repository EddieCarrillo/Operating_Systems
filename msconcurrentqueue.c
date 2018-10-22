typedef struct __node_t {
   int value;
   struct __node_t *next;
} node_t;


typedef struct __queue_t{
  node_t *head;
  node_t *tail;
 // We only want to lock the head and tail (Operations mostly occur on these nodes)  
  pthread_mutex_t headLock;
  pthread_mutex_t tailLock;
}  queue_t;



  void Queue_Init(queue_t *q){
     //Go ahead and initialize head and tail to dummy node
      node_t *tmp = malloc(sizeof(node_t));
      tmp->next = NULL;
      q->head = q->tail = tmp;
      //initialize head and tail locks
      pthread_mutex_init(&q->headLock, NULL);
      pthread_mutex_init(&q->tailLock, NULL);
   }


  void Queue_Enqueue(queue_t *q, int value){
       //Create a new node for enqueue value
       node_t *tmp = malloc(sizeof(node_t));
        //make sure that malloc did not fail
       assert(tmp != NULL)
       tmp->value = value;
       tmp->next = NULL;
        
       pthread_mutex_lock(&q->tailLock);
       //Insert the node 
       q->tail->next = tmp;
        //Update the tail pointer
       q->tail = tmp;
       pthread_mutex_unlock(&q->tailLock); //Release the lock

  }
  

 int Queue_Dequeue(queue_t *q, int *value){
      pthread_mutex_lock(&q->headLock);//Lock the head
      node_t *tmp = q->head;
      node_t *newhead = tmp->next;
      if (newHead == NULL){
          pthread_mutex_unlock(&q->headLock); //Release key since queue was empty
          return -1;
      }
      *value = newHead ->value;
      q->head = newHead;
      pthread_mutex_unlock(&q->headLock);
      free(tmp);

       return 0;
  
 }
