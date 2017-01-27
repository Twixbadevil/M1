class Temps{
	private:

		int secondes;
		int minutes;
		int heures;
		int secondesConverties;

	public:

		Temps(); // Constructeur de la classe Temps
		// Getters et Setters de la classe Temps
		int getSecondes();
		int getMinutes();
		int getHeures();
		void setSecondes(int sec);
		void setMinutes(int min);
		void setHeures(int h);
		void ajoutSecondes(); // Permet d'ajouter une seconde au temps
		int conversion(Temps t); // Permet la conversion du temps uniquement en secondes
		~Temps(); // Destructeur de la classe Temps
};