#include "lecteur_redacteur.h"

/*
 * initialiser_lecteur_redacteur : initialise une structure lr_t allouée
 * @param : la structure à initialisée
 */
void
initialiser_lecteur_redacteur(lecteur_redacteur_t *lr) {
    pthread_mutex_init(lr->m, NULL);
    pthread_cond_init(&lr->clecture, NULL);
    pthread_cond_init(&lr->credac, NULL);
    lr->en_lecture = 0;
    lr->en_redac = 0;
    lr->nb_att_redac = 0;
    lr->nb_att_lecture = 0;
}

/*
 * detruire_lecteur_redacteur : détruit une structure lr_t initialisée
 * @param : la structure à détruire
 */
void
detruire_lecteur_redacteur(lecteur_redacteur_t *lr) {
    pthread_cond_destroy(&lr->clecture);
    pthread_cond_destroy(&lr->credac);
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
    lr->nb_att_lecture++;
    while(lr->en_redac)
        pthread_cond_wait(&lr->clecture, lr->m);
    lr->en_lecture++;
    lr->nb_att_lecture--;
    pthread_mutex_unlock(lr->m);
}

/*
 * fin_lecture : rend la main en fin de lecture
 * @param : la structure de contrôle de type lr_t
 */
void
fin_lecture(lecteur_redacteur_t *lr) {
    pthread_mutex_lock(lr->m);
    lr->en_lecture--;
    if(lr->en_lecture == 0)
        pthread_cond_signal(&lr->credac);
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
    lr->nb_att_redac++;
    while(lr->en_lecture || lr->nb_att_lecture || lr->en_redac)
        pthread_cond_wait(&lr->credac, lr->m);
    lr->en_redac++;
    lr->nb_att_redac--;
    pthread_mutex_unlock(lr->m);
}

/*
 * fin_redaction : rend la main en fin de redaction
 * @param : la structure de contrôle de type lr_t
 */
void 
fin_redaction(lecteur_redacteur_t *lr) {
    pthread_mutex_lock(lr->m);
    lr->en_redac--;
    if(lr->nb_att_lecture)
        pthread_cond_broadcast(&lr->clecture);
    else
        pthread_cond_signal(&lr->credac);
    pthread_mutex_unlock(lr->m);
}

