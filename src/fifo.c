#include <malloc.h>

#include "fifo.h"

/*
 * fifo_is_empty : if there are no element in queue.
 * @param q : pointer to queue.
 * @return : true if empty, false otherwise.
 */
int
fifo_is_empty(queue_t * q) {
    return (q->head == NULL);
}

/*
 * fifo_create_cell : create a cell with given parameters
 * @param lr : pointer to lr_t struct
 * @param type : integer representing element type
 *  - lecteur : value of 0
 *  - redacteur : value of 1
 * @return : pointer to the cell_t
 */
cell_t *
fifo_create_cell(lecteur_redacteur_t *lr, int type) {
    cell_t *c = malloc(sizeof(cell_t));
    pthread_cond_t * ccell = malloc(sizeof(pthread_cond_t));
    pthread_cond_init(ccell, NULL);
    c->lr = lr;
    c->ccell = ccell;
    c->type = type;
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
lecteur_redacteur_t *
fifo_cell_get_lr(cell_t * c) {
    return c->lr;
}

/*
 * fifo_add : add element to queue's tail.
 * @param q : pointer to the queue
 * @param c : pointer to the element to add
 */
void
fifo_add(queue_t * q, cell_t * c) {
    if(fifo_is_empty(q)) {
        q->head = c;
        q->tail = c;
    } else {
        q->tail->next = c;
        q->tail = c;
    }
}

/*
 * fifo_get : remove the head from the queue and returns it.
 * @param q : the queue
 * @return :  pointer to cell_t struct, NULL if empty queue.
 */
cell_t *
fifo_get(queue_t * q) {
    cell_t * c = NULL;
    if(!fifo_is_empty(q)) {
        c = q->head;
        if (fifo_cell_has_next(q->head)) {
            q->head = q->head->next;
        } else {
            q->head = NULL;
            q->tail = NULL;
        }
    }
    return c;
}



