#ifndef __FIFO_H__
#define __FIFO_H__

#include "lecteur_redacteur_fifo.h"

// TODO : thread safe

typedef struct cell_t cell_t;

struct cell_t {
    lecteur_redacteur_t *lr;
    pthread_cond_t *ccell;
    int type;
    cell_t *next;
};

typedef struct fifo_queue_t {
    cell_t * head;
    cell_t * tail;
} queue_t;


/*
 * fifo_is_empty : if there are no element in queue.
 * @param q : pointer to queue.
 * @return : true if empty, false otherwise.
 */
int
fifo_is_empty(queue_t * q);

/*
 * fifo_create_cell : create a cell with given parameters
 * @param lr : pointer to lr_t struct
 * @param type : integer representing element type
 *  - lecteur : value of 0
 *  - redacteur : value of 1
 * @return : pointer to the cell_t
 */
cell_t *
fifo_create_cell(lecteur_redacteur_t *lr, int type);

/*
 * fifo_cell_has_next : if a cell has a next cell in queue.
 * @param c : pointer to cell_t
 * return : 1 if true, 0 otherwise.
 */
int
fifo_cell_has_next(cell_t * c);

/*
 * fifo_cell_get_lr : retruns lr_t struct from a cell_t
 * @params c : pointer to the cell
 * @return : pointer to the lr_t struct from the cell
 */
lecteur_redacteur_t *
fifo_cell_get_lr(cell_t * c);

/*
 * fifo_add : add element to queue's tail.
 * @param q : the queue
 * @param lr : element to add
 * @param type : type of element (lecteur/redacteur)
 *  - lecteur : value of 0
 *  - redacteur : value of 1
 */
void
fifo_add(queue_t * q, cell_t * c);

/*
 * fifo_get : remove the head from the queue and returns it.
 * Returns NULL if queue empty
 * @param q : the queue
 */
cell_t *
fifo_get(queue_t * q);

#endif /* __FIFO_H__ */
