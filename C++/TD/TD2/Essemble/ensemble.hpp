
#pragma once

#include <iostream>

using namespace std;

template<typename T>
class Ensemble {

	private:
	int nmax;
	T * adval;
	int nelem;

	public:
	Ensemble();
	Ensemble(int nmax);
	Ensemble(const Ensemble<T> & ens);
	~Ensemble();
	Ensemble<T> & operator=(const Ensemble<T> & ens);
	bool appartient(T & e) const;
	void ajoute(T & e);
	void supprime(T & e);
	bool estvide() const;
	bool estplein() const;
	int cardinal() const;
	T operator[](int i) const;

	template<typename U>
	friend ostream & operator<<(ostream & stream, const Ensemble<U> & ens);
	template<typename U>
	friend istream & operator>>(istream & stream, Ensemble<U> & ens);

	class EnsembleIter {

		private:
		const Ensemble<T> * _ptrl;
		T * _courant;

		public:
		EnsembleIter(const Ensemble<T> & ens);
		T & operator()();
		T & operator++(int i);
		void raz();
	};
};
