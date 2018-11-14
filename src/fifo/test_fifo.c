#include <stdlib.h>
#include <stdio.h>

#include "fifo.h"

#define NB_VAL 10

typedef struct test_t {
    int v;
} test_t;

void
display_result(int b, char * test_name) {
    printf("Fifo test %-15s ", test_name);
    if (b)
        printf("passed");
    else
        printf("failed");
    printf("\n");
}

int
fifo_test_init(queue_t * q) {
    return fifo_get(q) == NULL && q->tail == NULL;
}

int
fifo_test_order(queue_t * q) {
    int i, nb;
    test_t values[NB_VAL];

    for(i = 0; i < NB_VAL; i++) {
        values[i].v = i;
        fifo_add(q, &values[i]);
    }

    nb = 0;
    while(!fifo_is_empty(q) && ((test_t *) fifo_get(q))->v == values[nb].v) {
        fifo_next(q);
        nb++;
    }
    return fifo_is_empty(q);
}

int
main(int argc, char * argv[]) {
    queue_t * q = fifo_init();

    display_result(fifo_test_init(q), "init");
    display_result(fifo_test_order(q), "order");

    return EXIT_SUCCESS;
}

