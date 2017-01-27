#include <iostream>
#include "coureur.hpp"

class Commissaire{
	private:
		Coureur tabCoureur[]; // Tableau des coureurs en course
		Coureur tabCoureurFinal[]; // Tableau pour le classement partiel et final des coureurs
		int nombreDeCoureur; // Nombre de coureurs en tout

	public:

		Commissaire(); // Constructeur de la classe Commissaire

		int getNombreDeCoureur(); // Retourne le nombre de coureur

		void inscription(); // Permet d'inscrire un coureur dans la tableau des coureurs

		void triBulleTableauCoureur(Coureur tab[], int n); // Permet de trier en fonction du temps des coureurs pour afficher le classement

		void afficherClassement(Coureur tab[], int n); // Affiche le classement des coureurs

		void lancerCourse(int); // Permet de lancer la course

		~Commissaire(); // Destructeut de la classe Commissaire
};