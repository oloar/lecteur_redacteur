#ifndef __FIFO_H__
#define __FIFO_H__

#include <pthread.h>

typedef struct cell_t cell_t;

struct cell_t {
    void * data;
    cell_t * next;
};

struct fifo_queue_t {
    cell_t * head;
    cell_t * tail;
    pthread_mutex_t * m;
};

/*
 * fifo_init : initialize empty queue
 * @return : fifo_queue_t pointer
 */
struct fifo_queue_t *
fifo_init();

/*
 * fifo_is_empty : if there are no element in queue.
 * @param q : pointer to queue.
 * @return : true if empty, false otherwise.
 */
int
fifo_is_empty(struct fifo_queue_t * q);

/*
 * fifo_cell_init : create a cell with given parameters
 * @param lr : pointer to lr_t struct
 * @return : pointer to the cell_t
 */
cell_t *
fifo_cell_init(void * lr);

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
void *
fifo_cell_get_data(cell_t * c);

/*
 * int
 * fifo_cell_is_redacteur(cell_t * c);
 *
 * int
 * fifo_cell_is_lecteur(cell_t * c);
 */

/*
 * fifo_add : add element to queue's tail.
 * @param q : the queue
 * @param data : element to add
 */
void
fifo_add(struct fifo_queue_t * q, void * data);


/*
 * fifo_get : returns the value of the next element.
 * Returns NULL if queue empty
 * @param q : the queue
 * @return : pointer to the data
 */
void *
fifo_get(struct fifo_queue_t * q);

/*
 * fifo_next : remove the head from the queue and returns it.
 * Returns NULL if queue empty
 * @param q : the queue
 * @return : pointer to the data
 */
void *
fifo_next(struct fifo_queue_t * q);

void
fifo_destroy(struct fifo_queue_t * q);

#endif /* __FIFO_H__ */
