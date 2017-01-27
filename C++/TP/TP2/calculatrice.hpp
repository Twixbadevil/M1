#include <iostream>
#include <cstdlib>
#include <stack>
#include <cmath> 
#include <stdio.h>
#include <string.h>


template<typename T>
class Calculatrice{

	public:

		std::stack<char*> pileOp;
		std::stack<T> pileT;

		Calculatrice();

		bool estOp1(char * c);

		bool estOp2(char * c);
	
		void estT(char *c,float & valeur);

		std::stack<char*> getPileOp();

		std::stack<T> getPileT();

		T op2(char* op,T a,T b);

		double constante(char* c);

		double op1(char* op,T a);

		void evalExp();
};