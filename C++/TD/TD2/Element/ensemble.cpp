
#include <iostream>

#include "ensemble.hpp"

using namespace std;

Ensemble::Ensemble() : nmax(10), nelem(0) {
	adval = new Element[nmax];
}

Ensemble::Ensemble(int nmax) : nmax(nmax), nelem(0) {
	adval = new Element[nmax];
}

Ensemble::Ensemble(const Ensemble & ens) {
	nmax = ens.nmax;
	nelem = ens.nelem;
	adval = new Element[nmax];
	for (int i = 0 ; i < nelem ; i++) {
		adval[i] = ens.adval[i];
	}
}

Ensemble::~Ensemble() {
	delete[] adval;
}

Ensemble & Ensemble::operator=(const Ensemble & ens) {
	nmax = ens.nmax;
	nelem = ens.nelem;
	delete[] adval;
	adval = new Element[nmax];
	for (int i = 0 ; i < nelem ; i++) {
		adval[i] = ens.adval[i];
	}
	return *this;
}

bool Ensemble::appartient(Element & e) const {
	for (int i = 0 ; i < nelem ; i++) {
		if (adval[i] == e) {
			return true;
		}
	}
	return false;
}

void Ensemble::ajoute(Element & e) {
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

void Ensemble::supprime(Element & e) {
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

bool Ensemble::estvide() const {
	return nelem == 0;
}

bool Ensemble::estplein() const {
	return nelem == nmax;
}

int Ensemble::cardinal() const {
	return nelem;
}

Element Ensemble::operator[](int i) const {
	return adval[i];
}

ostream & operator<<(ostream & stream, const Ensemble & ens) {
	stream << "[ ";
	for (int i = 0 ; i < ens.nelem ; i++) {
		stream << ens.adval[i] << ' ';
	}
	stream << ']';
	return stream;
}

istream & operator>>(istream & stream, Ensemble & ens) {
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
	ens.adval = new Element[nmax];
	for (int i = 0 ; i < nelem; i++) {
		Element e;
		stream >> e;
		ens.ajoute(e);
	}
	return stream;
}

Ensemble::EnsembleIter::EnsembleIter(const Ensemble & ens) : _ptrl(&ens) {
	raz();
}

Element & Ensemble::EnsembleIter::operator()() {
	return *_courant;
}

Element & Ensemble::EnsembleIter::operator++(int i) {
	(void) i;
	if (_courant != NULL) {
		_courant++;
		if (_courant == _ptrl->adval + _ptrl->nelem) {
			_courant = NULL;
		}
	}
	return *_courant;
}

void Ensemble::EnsembleIter::raz() {
	_courant = _ptrl->estvide() ? NULL : _ptrl->adval;
}
