#include <iostream>
#include <string>

template <class T> class Ensemble {
	private: 
		int nmax;
		T * adval;
		int nelem;

	public: 

		//Getter Setter

		int getNmax(){
			return nmax;
		}
		void setNmax(int val){
			nmax = val;
		}
		T getAdval(){
			return adval;
		}
		void setAdval(T val){
			adval = val;
		}
		int getNelem(){
			return nelem;
		}
		void setNelem(int val){
			nelem = val;
		}

		//	Constructeur 

		Ensemble(int i=20){
			nmax = i;				// nb maxi d'elements
			adval = new T[i];		// adresse du tableau des valeurs
			nelem = 0;				// nb d'elements 
		}

		// Par recopie

		Ensemble(const T &e): nmax(e.getNmax()),adval(e.getAdval()),nelem(e.getNelem);

		int appartient(T e){
			for(int i=0;i<nelem;i++){
				if(e==adval[i]){
					return 1;
				}
			}
			return 0;
		}

		void ajoute(T e){
			if(!appartient(e)){
				if(nelem < nmax){
					adval[nelem] = e;
					nelem++;
				}
				cout<<"Ensemble plein"<<endl;
			}
			cout<<"Element deja dans l'ensemble"<<endl;
		}

		void supprimer(T e){
			int flag = 0;
			for(int i=0;i<nelem-1;i++){
				if(flag)
					adval[i]=adval[i+1];
				else if(e == adval[i])
					flag = 1;
			}
			if(flag){
				delete(adval[nelem]);
				nelem--;
			}else{
				cout<<"L'element n'etais pas dans l'ensemble avant la suppression"<<endl;
			}
		}

		int estvide(){
			return(nelem == 0);
		}

		int cardinal(){
			return nelem;
		}

		//Destructeur

		~Ensemble(){
			delete [] adval;
		}

		//Opérateur d'affectation

		Ensemble & Ensemble::operator =(Ensemble &e){
			nmax = e.getNmax();
			adval = e.getAdval();
			nelem = e.getNelem();
		}

		//Affichage

		friend ostream & operator <<(ostream & flux , const Ensemble & e){
			return flux<<adval<<endl
		}

}