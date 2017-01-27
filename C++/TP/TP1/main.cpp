#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "commissaire.hpp"

void usage(){
	std::cout<<"Usage : "<<std::endl;
	std::cout<<"./coureur <nombre de coureur>"<<std::endl;
	std::cout<<"<nombre de coureur> doit etre entre 1 et 100"<<std::endl;
}

int main( int argc, char *argv[]){
	int nbCoureur;

	if(argc != 2){
		usage();
		return(-1);
	}

	nbCoureur = atoi(argv[1]);

	if(nbCoureur>100 || nbCoureur<0){
		usage();
		return(-1);
	}

	Commissaire com;

	//Inscription des coureurs
	for(int i=0; i<nbCoureur; i++){
		com.inscription(); 
	}


	//Lancement de la course
	com.lancerCourse(nbCoureur); 

	return(0);
	
}