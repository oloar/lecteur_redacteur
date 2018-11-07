#include <malloc.h>
#include "lecteur_redacteur.h"

#define REDACTEUR 0
#define LECTEUR 1

typedef struct data_t {
    int est_lecteur;
    pthread_cond_t cond;
} data_t;

/*
 * lr_add_to_queue : Initialise la structure et l'ajoute à la file
 * @param lr : pointeur sur la structure lecteur_redacteur_t
 * @param type : le type du thread 
 *  - 0 : redacteur
 *  - 1 : lecteur
 */
void
lr_add_to_queue(lecteur_redacteur_t * lr, int type) {
    data_t d;
    /* initialise la structure à enfiler */
    d.est_lecteur = type;
    pthread_cond_init(&d.cond, NULL);
    /* Enfile la structure */
    fifo_add(lr->queue, &d);
    /* wait sur la condition et relache le mutex */
    pthread_cond_wait(&d.cond, lr->m);
}

/*
 * lr_remove_from_queue : Sort le premier élément de la file
 * @param q : la file
 */
void
lr_remove_from_queue(queue_t * q) {
    data_t * d = (data_t *) fifo_next(q);
    pthread_cond_signal(&d->cond);
}

/*
 * initialiser_lecteur_redacteur : initialise une structure lr_t allouée
 * @param : la structure à initialisée
 */
void
initialiser_lecteur_redacteur(lecteur_redacteur_t *lr) {
    lr->queue = fifo_init();
    lr->m = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(lr->m, NULL);
    lr->en_ecriture = 0;
    lr->nb_lecteur = 0;
}

/*
 * detruire_lecteur_redacteur : détruit une structure lr_t initialisée
 * @param : la structure à détruire
 */
void
detruire_lecteur_redacteur(lecteur_redacteur_t *lr) {
    fifo_destroy(lr->queue);
    pthread_mutex_destroy(lr->m);
}

/*
 * debut_lecture : demande la main pour lire, lit si disponible,
 * attend sinon.
 * @param : la structure de contrôle de type lr_t
 */
void
debut_lecture(lecteur_redacteur_t *lr) {
    pthread_mutex_lock(lr->m);
    if(!fifo_is_empty(lr->queue) || lr->en_ecriture) {
        lr_add_to_queue(lr, LECTEUR);
        if (!fifo_is_empty(lr->queue) && ((data_t *) fifo_get(lr->queue))->est_lecteur)
            lr_remove_from_queue(lr->queue);
    }
    lr->nb_lecteur++;
    pthread_mutex_unlock(lr->m);
}

/*
 * fin_lecture : rend la main en fin de lecture
 * @param : la structure de contrôle de type lr_t
 */
void
fin_lecture(lecteur_redacteur_t *lr) {
    pthread_mutex_lock(lr->m);
    lr->nb_lecteur--;
    if(lr->nb_lecteur == 0 && !fifo_is_empty(lr->queue) && !((data_t *) fifo_get(lr->queue))->est_lecteur)
        lr_remove_from_queue(lr->queue);

    pthread_mutex_unlock(lr->m);
}

/*
 * debut_redaction : demande la main pour rédiger, rédige si disponible
 * attend sinon.
 * @param : la structure de contôle de type lr_t
 */
void
debut_redaction(lecteur_redacteur_t *lr) {
    pthread_mutex_lock(lr->m);
    if(!fifo_is_empty(lr->queue) || lr->en_ecriture || lr->nb_lecteur)
        lr_add_to_queue(lr, REDACTEUR);
    lr->en_ecriture = 1;
    pthread_mutex_unlock(lr->m);
}

/*
 * fin_redaction : rend la main en fin de redaction
 * @param : la structure de contrôle de type lr_t
 */
void 
fin_redaction(lecteur_redacteur_t *lr) {
    pthread_mutex_lock(lr->m);
    lr->en_ecriture = 0;
    if(!fifo_is_empty(lr->queue))
        lr_remove_from_queue(lr->queue);

    pthread_mutex_unlock(lr->m);
}

