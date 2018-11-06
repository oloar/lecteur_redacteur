#ifndef __LR_H__
#define __LR_H__

#include <pthread.h>
typedef struct lr_t {
    pthread_mutex_t *m;
    pthread_cond_t clecture;
    pthread_cond_t credac;
    int en_lecture;
    int en_redac;
    int nb_att_redac;
    int nb_att_lecture;
} lecteur_redacteur_t;

/*
 * initialiser_lecteur_redacteur : initialise une structure lr_t allouée
 * @param : la structure à initialisée
 */
void initialiser_lecteur_redacteur(lecteur_redacteur_t *lr);

/*
 * detruire_lecteur_redacteur : détruit une structure lr_t initialisée
 * @param : la structure à détruire
 */
void detruire_lecteur_redacteur(lecteur_redacteur_t *lr);

/*
 * debut_lecture : demande la main pour lire, lit si disponible,
 * attend sinon.
 * @param : la structure de contrôle de type lr_t
 */
void debut_lecture(lecteur_redacteur_t *lr);

/*
 * fin_lecture : rend la main en fin de lecture
 * @param : la structure de contrôle de type lr_t
 */
void fin_lecture(lecteur_redacteur_t *lr);

/*
 * debut_redaction : demande la main pour rédiger, rédige si disponible
 * attend sinon.
 * @param : la structure de contôle de type lr_t
 */
void debut_redaction(lecteur_redacteur_t *lr);

/*
 * fin_redaction : rend la main en fin de redaction
 * @param : la structure de contrôle de type lr_t
 */
void fin_redaction(lecteur_redacteur_t *lr);

#endif /* __LR_H__ */
