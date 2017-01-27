#include <iostream>
#include "temps.hpp"

Temps::Temps(){
	secondes = 0;
	minutes = 0;
	heures = 0;
}

int Temps::getSecondes(){
	return secondes;
}

int Temps::getMinutes(){
	return minutes;
}

int Temps::getHeures(){
	return heures;
}

void Temps::setSecondes(int sec){
	secondes = sec;
}

void Temps::setMinutes(int min){
	minutes = min;
}

void Temps::setHeures(int h){
	heures = h;
}

void Temps::ajoutSecondes(){
	secondes++;
}

//Permet la conversion du Temps t en secondes
int Temps::conversion(Temps t){
	int tempsConverti;

    tempsConverti = (t.getHeures())*3600 + (t.getMinutes())*60 + t.getSecondes();

    return tempsConverti;
}

Temps::~Temps(){}