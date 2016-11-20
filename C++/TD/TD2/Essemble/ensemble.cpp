
#include <iostream>

#include "ensemble.hpp"

using namespace std;

template<typename T>
Ensemble<T>::Ensemble() : nmax(10), nelem(0) {
	adval = new T[nmax];
}

template<typename T>
Ensemble<T>::Ensemble(int nmax) : nmax(nmax), nelem(0) {
	adval = new T[nmax];
}

template<typename T>
Ensemble<T>::Ensemble(const Ensemble & ens) {
	nmax = ens.nmax;
	nelem = ens.nelem;
	adval = new T[nmax];
	for (int i = 0 ; i < nelem ; i++) {
		adval[i] = ens.adval[i];
	}
}

template<typename T>
Ensemble<T>::~Ensemble() {
	delete[] adval;
}

template<typename T>
Ensemble<T> & Ensemble<T>::operator=(const Ensemble<T> & ens) {
	nmax = ens.nmax;
	nelem = ens.nelem;
	delete[] adval;
	adval = new T[nmax];
	for (int i = 0 ; i < nelem ; i++) {
		adval[i] = ens.adval[i];
	}
	return *this;
}

template<typename T>
bool Ensemble<T>::appartient(T & e) const {
	for (int i = 0 ; i < nelem ; i++) {
		if (adval[i] == e) {
			return true;
		}
	}
	return false;
}

template<typename T>
void Ensemble<T>::ajoute(T & e) {
	if (!estplein()) {
		for (int i = 0 ; i < nelem ; i++) {
			if (adval[i] == e) {
				return;
			}
		}
		adval[nelem] = e;
		nelem++;
	}
}

template<typename T>
void Ensemble<T>::supprime(T & e) {
	for (int i = 0 ; i < nelem ; i++) {
		if (adval[i] == e) {
			for (i++; i < nelem ; i++) {
				adval[i-1] = adval[i];
			}
			nelem--;
			return;
		}
	}
}

template<typename T>
bool Ensemble<T>::estvide() const {
	return nelem == 0;
}

template<typename T>
bool Ensemble<T>::estplein() const {
	return nelem == nmax;
}

template<typename T>
int Ensemble<T>::cardinal() const {
	return nelem;
}

template<typename T>
T Ensemble<T>::operator[](int i) const {
	return adval[i];
}

template<typename T>
ostream & operator<<(ostream & stream, const Ensemble<T> & ens) {
	stream << "[ ";
	for (int i = 0 ; i < ens.nelem ; i++) {
		stream << ens.adval[i] << ' ';
	}
	stream << ']';
	return stream;
}

template<typename T>
istream & operator>>(istream & stream, Ensemble<T> & ens) {
	int nmax, nelem;
	stream >> nmax;
	stream >> nelem;
	if (nelem > nmax) {
		cout << "Nombre de valeurs plus grand que le max" << endl;
		return stream;
	}
	ens.nmax = nmax;
	ens.nelem = 0;
	delete []ens.adval;
	ens.adval = new T[nmax];
	for (int i = 0 ; i < nelem; i++) {
		T e;
		stream >> e;
		ens.ajoute(e);
	}
	return stream;
}

template<typename T>
Ensemble<T>::EnsembleIter::EnsembleIter(const Ensemble<T> & ens) : _ptrl(&ens) {
	raz();
}

template<typename T>
T & Ensemble<T>::EnsembleIter::operator()() {
	return *_courant;
}

template<typename T>
T & Ensemble<T>::EnsembleIter::operator++(int i) {
	(void) i;
	if (_courant != NULL) {
		_courant++;
		if (_courant == _ptrl->adval + _ptrl->nelem) {
			_courant = NULL;
		}
	}
	return *_courant;
}

template<typename T>
void Ensemble<T>::EnsembleIter::raz() {
	_courant = _ptrl->estvide() ? NULL : _ptrl->adval;
}

template class Ensemble<int>;
template ostream & operator<<(ostream & stream, const Ensemble<int> & ens);
template istream & operator>>(istream & stream, Ensemble<int> & ens);
