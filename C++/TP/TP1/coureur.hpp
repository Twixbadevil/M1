#include "temps.hpp"

class Coureur{
	private:
		int numero; // Numero du dossard du coureur
		Temps temps; // Temps du coureur
		bool estArrive; // Booleen pour savoir si le coureur a fini sa course
	public:
		Coureur(int num); // Constructeur de la classe Coureur

		int getNumero(); // Retourne le numero du dossard du coureur

		Temps getTemps(); // Retourne le temps du coureur

		void lanceCoureur(); // Permet a un coureur de demarrer sa course
		
		bool aFini(); // Permet de savoir si un coureur a fini sa course

		~Coureur(); // Destructeur de la classe Coureur
};