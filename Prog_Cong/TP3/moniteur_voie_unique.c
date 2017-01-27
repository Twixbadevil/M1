#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include <sens.h>
#include <train.h>
#include <moniteur_voie_unique.h>

/*---------- MONITEUR ----------*/

extern moniteur_voie_unique_t * moniteur_voie_unique_creer( const train_id_t nb )
{
  moniteur_voie_unique_t * moniteur = NULL ;

  /* Creation structure moniteur */
  if( ( moniteur = malloc( sizeof(moniteur_voie_unique_t) ) ) == NULL  )
    {
      fprintf( stderr , "moniteur_voie_unique_creer: debordement memoire (%lu octets demandes)\n" ,
         sizeof(moniteur_voie_unique_t) ) ;
      return(NULL) ;
    }

  /* Creation de la voie */
  if( ( moniteur->voie_unique = voie_unique_creer() ) == NULL )
    return(NULL) ;

  /* Initialisations du moniteur */

  //init mutex
  pthread_mutex_init(&(moniteur->mutexMonit), NULL);
  //init variable de condition
  pthread_cond_init(&(moniteur->condVide), NULL);
  pthread_cond_init(&(moniteur->condPleine), NULL);
  pthread_cond_init(&(moniteur->condEst), NULL);
  pthread_cond_init(&(moniteur->condOuest), NULL);
  //init variables
  moniteur->cpt = 0;
  moniteur->max = nb;
  //init sens de depart
  moniteur->s = OUEST_EST;
  return(moniteur) ;
}

extern int moniteur_voie_unique_detruire( moniteur_voie_unique_t ** moniteur )
{
  int noerr ;

  /* Destructions des attribiuts du moniteur */

  //destruction mutex
  pthread_mutex_destroy(&((*moniteur)->mutexMonit));
  //destruction variables conditionnelles
  pthread_cond_destroy(&((*moniteur)->condVide));
  pthread_cond_destroy(&((*moniteur)->condPleine));
  pthread_cond_destroy(&((*moniteur)->condEst));
  pthread_cond_destroy(&((*moniteur)->condOuest));

  /* Destruction de la voie */
  if( ( noerr = voie_unique_detruire( &((*moniteur)->voie_unique) ) ) )
    return(noerr) ;

  /* Destruction de la strcuture du moniteur */
  free( (*moniteur) );

  (*moniteur) = NULL ;

  return(0) ;
}


extern void moniteur_voie_unique_entree_ouest( moniteur_voie_unique_t * moniteur )
{
    //verrouillage du mutex sur le moniteur
    pthread_mutex_lock(&(moniteur->mutexMonit));

    if(moniteur->cpt==0 && (moniteur->s) == EST_OUEST)
        (moniteur->s) = OUEST_EST;

    //si sens oppose, alors mise en attente
    else if((moniteur->s) == EST_OUEST){
      //printf("\n entree OUEST mauvais sens sommeil \n");
      pthread_cond_wait(&(moniteur->condOuest), &(moniteur->mutexMonit));
      (moniteur->s) = OUEST_EST;
    }

    //si la voie est pleine, on attend
    if((moniteur->cpt) == (moniteur->max)){
      //printf("\n entree OUEST voie pleine sommeil \n");
      pthread_cond_wait(&(moniteur->condPleine), &(moniteur->mutexMonit));
    }

    //mise a jour du nombre de train
    (moniteur->cpt)++;

    //si seul train sur la voie, eveil de train allant dans le meme sens et eveil de la sortie
    if((moniteur->cpt) >= 1 && (moniteur->cpt) <= (moniteur->max)){
        //printf("\n entree OUEST eveil vide et ouest \n");
        pthread_cond_signal(&(moniteur->condVide));
        pthread_cond_signal(&(moniteur->condOuest));
    }

    //deverrouillage du mutex sur le moniteur
    pthread_mutex_unlock(&(moniteur->mutexMonit));
}

extern void moniteur_voie_unique_sortie_est( moniteur_voie_unique_t * moniteur )
{
    //verrouillage du mutex sur le moniteur
    pthread_mutex_lock(&(moniteur->mutexMonit));

    //mise en attente si la voie est vide
    if((moniteur->cpt) == 0){
      //printf("\n sortie EST voie vide, eveil Ouest puis sommeil \n");
      pthread_cond_signal(&(moniteur->condOuest));
      pthread_cond_wait(&(moniteur->condVide), &(moniteur->mutexMonit));
    }

    //mise a jour du nombre de train sur la voie
    (moniteur->cpt)--;

    //si place disponible, eveil d'un train en attente pour entrer sur la voie
    if(moniteur->cpt == (moniteur->max)-1){
      //printf("\n sortie EST cpt = max-1, eveil Pleine \n");
      pthread_cond_signal(&(moniteur->condPleine));
    }

    //si dernier train sorti, changement de sens et eveil des trains en attente direction opposee
    if(moniteur->cpt == 0){
      //printf("\n sortie EST voie vide, changement sens puis eveil Est\n");
      (moniteur->s) = EST_OUEST;
      pthread_cond_signal(&(moniteur->condEst));
    }

    //deverrouillage du mutex sur le moniteur
    pthread_mutex_unlock(&(moniteur->mutexMonit));
}

extern void moniteur_voie_unique_entree_est( moniteur_voie_unique_t * moniteur ){


    //verrouillage du mutex sur le moniteur
    pthread_mutex_lock(&(moniteur->mutexMonit));

    if(moniteur->cpt==0 && (moniteur->s) == OUEST_EST )
        (moniteur->s) = EST_OUEST;

    //si sens oppose, alors mise en attente
    else if((moniteur->s) == OUEST_EST){
      //printf("\n entree EST mauvais sens sommeil \n");
      pthread_cond_wait(&(moniteur->condEst), &(moniteur->mutexMonit));
      (moniteur->s) = EST_OUEST;
    }

    //si la voie est pleine, on attend
    if((moniteur->cpt) == (moniteur->max)){
      //printf("\n entree EST voie pleine sommeil \n");
      pthread_cond_wait(&(moniteur->condPleine), &(moniteur->mutexMonit));
    }


    //mise a jour du nombre de train
    (moniteur->cpt)++;

    //si seul train sur la voie, reveil de la sortie et des trains en attente dans le meme sens
    if((moniteur->cpt) >= 1 && (moniteur->cpt) <= (moniteur->max)){
      //printf("\n entree EST eveil vide et ouest \n");
      pthread_cond_signal(&(moniteur->condVide));
      pthread_cond_signal(&(moniteur->condEst));
    }

    //deverrouillage du mutex sur le moniteur
    pthread_mutex_unlock(&(moniteur->mutexMonit));
}

extern void moniteur_voie_unique_sortie_ouest( moniteur_voie_unique_t * moniteur ){
    //verrouillage du mutex sur le moniteur
    pthread_mutex_lock(&(moniteur->mutexMonit));

    //mise en attente si la voie est vide
    if((moniteur->cpt) == 0){
      //printf("\n sortie OUEST voie vide, eveil EST puis sommeil \n");
      pthread_cond_signal(&(moniteur->condEst));
      pthread_cond_wait(&(moniteur->condVide), &(moniteur->mutexMonit));
    }

    //mise a jour du nombre de train sur la voie
    (moniteur->cpt)--;

    //si place disponible, eveil d'un train en attente pour entrer sur la voie
    if(moniteur->cpt == (moniteur->max)-1){
      //printf("\n sortie OUEST cpt = max-1, eveil Pleine \n");
      pthread_cond_signal(&(moniteur->condPleine));
    }
    //si dernier train sorti, changement de sens et eveil des trains en attente direction opposee
    if(moniteur->cpt == 0){
      //printf("\n sortie OUEST voie vide, changement sens puis eveil entree OUEST\n");
      (moniteur->s) = OUEST_EST;
      pthread_cond_signal(&(moniteur->condOuest));
    }

    //deverrouillage du mutex sur le moniteur
    pthread_mutex_unlock(&(moniteur->mutexMonit));
}

/*
 * Fonctions set/get
 */

extern
voie_unique_t * moniteur_voie_unique_get( moniteur_voie_unique_t * const moniteur )
{
  return( moniteur->voie_unique ) ;
}


extern
train_id_t moniteur_max_trains_get( moniteur_voie_unique_t * const moniteur ){
  return(moniteur->max);
}

/*
 * Fonction de deplacement d'un train
 */

extern
int moniteur_voie_unique_extraire( moniteur_voie_unique_t * moniteur , train_t * train , zone_t zone  )
{
  return( voie_unique_extraire( moniteur->voie_unique,
        (*train),
        zone ,
        train_sens_get(train) ) ) ;
}

extern
int moniteur_voie_unique_inserer( moniteur_voie_unique_t * moniteur , train_t * train , zone_t zone )
{
  return( voie_unique_inserer( moniteur->voie_unique,
             (*train),
             zone,
             train_sens_get(train) ) ) ;
}
