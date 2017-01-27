#include "commissaire.hpp"
#include <algorithm>

Commissaire::Commissaire(){
	nombreDeCoureur=1; //Les dossards commencent au numero 1
}

int Commissaire::getNombreDeCoureur(){
	return nombreDeCoureur;
}

void Commissaire::inscription(){
	Coureur coureur(nombreDeCoureur);
	tabCoureur[nombreDeCoureur] = coureur;
	nombreDeCoureur++;
}

void Commissaire::afficherClassement(Coureur tab[], int n){
	int i;
	for(i=1; i<=n ; i++){
		std::cout<<"Coureur "<< tab[i].getNumero() <<" arrive en "<<i<<" eme avec un temps de "<<tabCoureur[i].getTemps().getSecondes() << " secondes."<<std::endl;
	}
}

void Commissaire::triBulleTableauCoureur(Coureur tab[], int n){
	int i;
	bool estTrie = false;
	while(!estTrie){
		estTrie = true;
		for(i=1; i<n; i++){
			if(tab[i].getTemps().getSecondes() > tab[i+1].getTemps().getSecondes()){
				std::swap(tab[i], tab[i+1]);
				estTrie = false;
			}
		}
	}
}

void Commissaire::lancerCourse(int tmpCoureur){
	int i = 0;
	int j = 0;
	
	for(i=1; i<=tmpCoureur; i++){
		tabCoureur[i].lanceCoureur();
		std::cout<<"Le coureur "<< tabCoureur[i].getNumero() << " est arrive"<<std::endl;
		tabCoureurFinal[i] = tabCoureur[i];
		if(i!=1)
			triBulleTableauCoureur(tabCoureurFinal, i);
		if(i!=1 && i!= tmpCoureur){
			std::cout<<"================Classement partiel================"<<std::endl;
			afficherClassement(tabCoureurFinal, i);
		}
	}
	i--; // car i se fait incrementer en fin de boucle
	std::cout<<"================Classement final================"<<std::endl;
	afficherClassement(tabCoureurFinal, i);
}

Commissaire::~Commissaire(){}