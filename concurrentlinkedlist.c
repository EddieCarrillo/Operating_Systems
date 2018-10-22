typedef struct __node_t {
    int key;
    stuct __node_t *next;
}  node_t;



typdef struct __list_t {
    node_t  *head;
    pthread_mutex_t lock;
} list_t;


//Use constructor to init head of linked list and also intialize lock
void List_Init(list_t *L){
   L-> head = NULL;
   pthread_mutex_init(&L->lock, NULL);
}



int List_Insert(list_t *L, int key){
   pthread_mutex_lock(&L->lock);
   node_t *new = malloc(sizeof(node_t));
   if (new == NULL){//malloc() failed
        perror("malloc");
        //Make sure to unlock the code since malloc failed
        pthread_mutex_unlock(&L->lock);
        return -1;
   }
 //Init node and insert to begininning of the list
  new->key = key;
  new->next = L->head;
  L->head = new;
  pthread_mutex_unlock(&L->lock);
  return 0; //success

}




int List_Lookup(list_t *L, int key){
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr){
        //We have found the key
        if (curr->key == key){
          //We are finished so unlock
            pthread_mutex_unlock(&L->lock);
            return 0;
        }
       curr = curr->next;
    }
   pthread_mutex_unlock(&L->lock);
   return -1; //Failure
}

