#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <commun.h>
#include <liste.h>
#include <piste.h>


static struct sembuf Op_P ={0,-1,0};
static struct sembuf Op_V ={0,1,0};

static void p(int sem_id){
  semop(sem_id,&Op_P,1);
}

static void v(int sem_id){
  semop(sem_id,&Op_V,1);
}


int
main( int nb_arg , char * tab_arg[] )
{

  int ind_cheval;
  struct sembuf semtmp;

  int cle_piste ;
  piste_t * piste = NULL ;

  int cle_liste ;
  liste_t * liste = NULL ;

  char marque ;

  booleen_t fini = FAUX ;
  piste_id_t deplacement = 0 ;
  piste_id_t depart = 0 ;
  piste_id_t arrivee = 0 ;


  cell_t cell_cheval ;
  cell_t chevalTmp;


  elem_t elem_cheval ;
  elem_t elemTmp;
  elem_t tmp;

  /*-----*/

  if( nb_arg != 4 )
    {
      fprintf( stderr, "usage : %s <cle de piste> <cle de liste> <marque>\n" , tab_arg[0] );
      exit(-1);
    }

  if( sscanf( tab_arg[1] , "%d" , &cle_piste) != 1 )
    {
      fprintf( stderr, "%s : erreur , mauvaise cle de piste (%s)\n" ,
	       tab_arg[0]  , tab_arg[1] );
      exit(-2);
    }


  if( sscanf( tab_arg[2] , "%d" , &cle_liste) != 1 )
    {
      fprintf( stderr, "%s : erreur , mauvaise cle de liste (%s)\n" ,
	       tab_arg[0]  , tab_arg[2] );
      exit(-2);
    }

  if( sscanf( tab_arg[3] , "%c" , &marque) != 1 )
    {
      fprintf( stderr, "%s : erreur , mauvaise marque de cheval (%s)\n" ,
	       tab_arg[0]  , tab_arg[3] );
      exit(-2);
    }
  
  int shmid_liste, semid_liste, shmid_piste, semid_piste;


  /*Gestion de la liste*/
  shmid_liste = shmget(cle_liste,LISTE_MAX*sizeof(elem_t),IPC_CREAT | 0666);
  liste = shmat(shmid_liste,0,0);
  semid_liste = semget(cle_liste,1,0666);


  /*Gestion de la piste*/
  shmid_piste = shmget(cle_piste,PISTE_LONGUEUR*sizeof(cell_t),IPC_CREAT | 0666);
  piste = shmat(shmid_piste,0,0);
  semid_piste = semget(cle_piste,PISTE_LONGUEUR,0666);

  /* Init de l'attente */
  commun_initialiser_attentes() ;

  /* Init de la cellule du cheval pour faire la course */
  cell_pid_affecter( &cell_cheval  , getpid());
  cell_marque_affecter( &cell_cheval , marque );

  /* Init de l'element du cheval pour l'enregistrement */
  elem_cell_affecter(&elem_cheval , cell_cheval ) ;
  elem_etat_affecter(&elem_cheval , EN_COURSE ) ;

  /*
   * Enregistrement du cheval dans la liste
   */

  /*Initialisation du semaphore etat du cheval*/
  if (elem_sem_creer( &elem_cheval )==-1){
    perror("elem_sem_creer: Pb lors de la creation du semaphore\n");
    exit(-1);
  }

  /*
   * Ajout du cheval dans la liste
  */
  p(semid_liste);
  liste_elem_ajouter(liste,elem_cheval);
  v(semid_liste);

  while( ! fini ){
      /* Attente entre 2 coup de de */
      commun_attendre_tour() ;

	   
	    p(semid_liste);
	    liste_elem_rechercher(&ind_cheval,liste,elem_cheval);
	    elem_cheval=liste_elem_lire(liste,ind_cheval);
	    v(semid_liste);

      /*
       * Verification si pas decanille
       */
      elem_sem_verrouiller(&elem_cheval);
      if(elem_decanille(elem_cheval)){
	
        /*Suppression du semaphore etat du cheval*/
        if (elem_sem_detruire( &elem_cheval )==-1){
          perror("elem_sem_detruire: Pb destruction semaphore\n");
          exit(-1);
        }
      	
        if(liste_elem_rechercher(&ind_cheval,liste,elem_cheval)){
          p(semid_liste);
          liste_elem_decaniller( liste ,ind_cheval );
          liste_elem_supprimer(liste,ind_cheval);
          v(semid_liste);
        }
        printf( "Le cheval \"%c\" a ete decanille\n" , marque );
        exit(0);
      }
      elem_sem_deverrouiller(&elem_cheval);

      /*
       * Avancee sur la piste
       */

      /* Coup de de */
      deplacement = commun_coup_de_de() ;
#ifdef _DEBUG_
      printf(" Lancement du De --> %d\n", deplacement );
#endif

      arrivee = depart+deplacement ;

      if( arrivee > PISTE_LONGUEUR-1 ){
	        arrivee = PISTE_LONGUEUR-1 ;
	        fini = VRAI ;
      }

      if( depart != arrivee ){
	        /*
	         * Si case d'arrivee occupee alors on decanille le cheval existant
	         */
	         semtmp.sem_num=arrivee;
	         semtmp.sem_op=-1;
	         semtmp.sem_flg=0;
           /*P(caseArrivee)*/
          if(semop(semid_piste,&semtmp,1)==-1){
	           	perror("Pb semop \n");
		          exit(-1);
	        }
	      
    	   if(piste_cell_occupee(piste,arrivee)){
              piste_cell_lire(piste,arrivee,&chevalTmp);
		          elem_cell_affecter(&elemTmp, chevalTmp);

              
		          p(semid_liste);
		          liste_elem_rechercher(&ind_cheval,liste,elemTmp);
		          tmp = liste_elem_lire(liste,ind_cheval);
		          elem_sem_verrouiller(&tmp);
		          liste_elem_decaniller(liste,ind_cheval);
		          elem_sem_deverrouiller(&tmp);
		          v(semid_liste);
    	   }


	    /*
	     * Deplacement: effacement case de depart, affectation case d'arrivee
	     */
        semtmp.sem_num=depart;
        /*P(caseDepart)*/
        if(semop(semid_piste,&semtmp,1)==-1){
           	perror("Pb semop \n");
	          exit(-1);
        }
 
	      piste_cell_affecter(piste,arrivee,cell_cheval);
	      piste_cell_effacer(piste,depart);
	
        /*V(caseDepart)*/
	      semtmp.sem_op=1;
	      if(semop(semid_piste,&semtmp,1)==-1){
	       	perror("Pb semop \n");
		      exit(-1);
	      }

        /*V(caseArrivee)*/
	      semtmp.sem_num=arrivee;
	      if(semop(semid_piste,&semtmp,1)==-1){
	       	perror("Pb semop \n");
		      exit(-1);
	      }


#ifdef _DEBUG_
	  printf("Deplacement du cheval \"%c\" de %d a %d\n",
		marque, depart, arrivee );
#endif


	}
      /* Affichage de la piste  */
      piste_afficher_lig( piste );

      depart = arrivee ;
    }
	   semtmp.sem_op=-1;
     if(semop(semid_piste,&semtmp,1)==-1){
	     	perror("Pb semop \n");
		    exit(-1);
     }

  	 piste_cell_effacer(piste,depart);

	   semtmp.sem_op=1;
	   if(semop(semid_piste,&semtmp,1)==-1){
	     	perror("Pb semctl \n");
		    exit(-1);
     }

     printf( "Le cheval \"%c\" a franchit la ligne de fin\n" , marque );



  /*
   * Suppression du cheval de la liste
   */
  if(liste_elem_rechercher(&ind_cheval,liste,elem_cheval)){
    p(semid_liste);
    liste_elem_supprimer(liste,ind_cheval);
    v(semid_liste);
  }

  
  if(elem_sem_detruire(&elem_cheval)==-1){
    perror("elem_sem_detruire: Pb destruction semaphore\n");
    exit(-1);
  }

  exit(0);
}
