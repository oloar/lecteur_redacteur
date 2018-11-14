#include <malloc.h>

#include "fifo.h"

// TODO : hide cell_t

/*
 * fifo_init : initialize empty queue
 * @return : struct fifo_queue_t pointer
 */
struct fifo_queue_t *
fifo_init() {
    struct fifo_queue_t * q = malloc(sizeof(struct fifo_queue_t));
    q->head = NULL;
    q->tail = NULL;
    q->m = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(q->m, NULL);
    return q;
}

/*
 * fifo_is_empty : if there are no element in queue.
 * @param q : pointer to queue.
 * @return : true if empty, false otherwise.
 */
int
fifo_is_empty(struct fifo_queue_t * q) {
    return (q->head == NULL);
}

/*
 * fifo_create_cell : create a cell with given parameters
 * @param data : pointer to cell's data
 * @return : pointer to the cell_t
 */
cell_t *
fifo_cell_init(void * data) {
    cell_t * c = malloc(sizeof(cell_t));
    c->data = data;
    c->next = NULL;
    return c;
}

/*
 * fifo_cell_has_next : if a cell has a next cell in queue.
 * @param c : pointer to cell_t
 * return : 1 if true, 0 otherwise.
 */
int
fifo_cell_has_next(cell_t * c) {
    return c->next != NULL;
}

/*
 * fifo_cell_get_lr : retruns lr_t struct from a cell_t
 * @params c : pointer to the cell
 * @return : pointer to the lr_t struct from the cell
 */
void *
fifo_cell_get_data(cell_t * c) {
    return c->data;
}

/*
 * fifo_add : add element to queue's tail.
 * @param q : pointer to the queue
 * @param data : pointer to the element to add
 */
void
fifo_add(struct fifo_queue_t * q, void * data) {
    cell_t * c = fifo_cell_init(data);
    pthread_mutex_lock(q->m);
    if(fifo_is_empty(q)) {
        q->head = c;
        q->tail = c;
    } else {
        q->tail->next = c;
        q->tail = c;
    }
    pthread_mutex_unlock(q->m);
}

/*
 * fifo_get : returns the value of the next element.
 * Returns NULL if queue empty
 * @param q : the queue
 * @return : pointer to the data
 */
void *
fifo_get(struct fifo_queue_t * q) {
    return q->head ? q->head->data : NULL;
}


/*
 * fifo_get : remove the head from the queue and returns it.
 * @param q : the queue
 * @return :  pointer to data, NULL if empty queue.
 */
void *
fifo_next(struct fifo_queue_t * q) {
    cell_t * c = NULL;
    void * data = NULL;
    pthread_mutex_lock(q->m);
    if(!fifo_is_empty(q)) {
        c = q->head;
        if (fifo_cell_has_next(q->head)) {
            q->head = q->head->next;
        } else {
            q->head = NULL;
            q->tail = NULL;
        }
    }
    pthread_mutex_unlock(q->m);
    data = c->data;
    free(c);
    return data;
}

void
fifo_destroy(struct fifo_queue_t * q) {
    cell_t * curr;
    while(!fifo_is_empty(q)) {
        curr = fifo_next(q);
        free(curr->data);
        free(curr);
    }
    pthread_mutex_destroy(q->m);
    free(q->m);
    free(q);
}

