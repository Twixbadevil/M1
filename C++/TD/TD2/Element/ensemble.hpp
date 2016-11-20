
#pragma once

#include <iostream>

using namespace std;

typedef int Element;

class Ensemble {
	
	private:
	int nmax;
	Element * adval;
	int nelem;

	public:
	Ensemble();
	Ensemble(int nmax);
	Ensemble(const Ensemble & ens);
	~Ensemble();
	Ensemble & operator=(const Ensemble & ens);
	bool appartient(Element & e) const;
	void ajoute(Element & e);
	void supprime(Element & e);
	bool estvide() const;
	bool estplein() const;
	int cardinal() const;
	Element operator[](int i) const;

	friend ostream & operator<<(ostream & stream, const Ensemble & ens);
	friend istream & operator>>(istream & stream, Ensemble & ens);

	class EnsembleIter {

		private:
		const Ensemble * _ptrl;
		Element * _courant;

		public:
		EnsembleIter(const Ensemble & ens);
		Element & operator()();
		Element & operator++(int i);
		void raz();
	};
};
