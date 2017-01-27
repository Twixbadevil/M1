#include <iostream>
#include <stdlib.h>
#include "coureur.hpp"
#include <unistd.h>

Coureur::Coureur(int num){
	numero=num;
	estArrive=false;
}

int Coureur::getNumero(){
	return numero;
}

Temps Coureur::getTemps(){
	return temps;
}

void Coureur::lanceCoureur(){
	int limite = 20; // Limite a atteindre pour un coureur afin de finir sa course
	int tampon = 0; // Variable qui sert a avancer pour le coureur
	int hasard; // Variable qui prendre une valeur random entre 0 et 5 et sera ajouter au score du coureur symbolisant un lancé de des

	// A chaque tour de boucle, le temps du coureur prend une seconde et son score et incrementé avec le random qu'il obtient
	while(tampon <= limite && estArrive==false){
		hasard = rand()%6;
		tampon = tampon + hasard;
		temps.ajoutSecondes();
		sleep(1);
	}
	//Lorsque l'on sort de la boucle, le coureur a fini sa course
	estArrive = true;
}

bool Coureur::aFini(){
	return estArrive;
}

Coureur::~Coureur(){}
