#include "calculatrice.hpp"

template<typename T>
Calculatrice<T>::Calculatrice(){
	pileOp;
	pileT;
};

template<typename T>
bool Calculatrice<T>::estOp1(char * c){
	return !strcmp("sin",c) || !strcmp("cos",c) || !strcmp("tan",c) || !strcmp("exp",c) || !strcmp("log",c);
}

template<typename T>
bool Calculatrice<T>::estOp2(char * c){
	return !strcmp("+",c) || !strcmp("-",c) || !strcmp("/",c) || !strcmp("*",c) || !strcmp("^",c);
}

template<typename T>
void Calculatrice<T>::estT(char * c, float & valeur){
	valeur = atof(c);
}

template<typename T>
T Calculatrice<T>::op2(char* op,T a,T b){
	if(!strcmp("+",op))
		return a+b;
	else if(!strcmp("-",op))
		return a-b;
	else if(!strcmp("/",op))
		return a/b;
	else if(!strcmp("*",op))
		return a*b;
	else if(!strcmp("^",op))
		return(pow((double)a,(double)b));
}

template<typename T>
double Calculatrice<T>::op1(char* op,T a){
	if(!strcmp("sin",op))
		return sin((double)a);
	else if(!strcmp("cos",op))
		return cos((double)a);
	else if(!strcmp("tan",op))
		return tan((double)a);
	else if(!strcmp("exp",op))
		return exp((double)a);
	else if(!strcmp("log",op))
		return log10((double)a);	
}

template<typename T>
double Calculatrice<T>::constante(char* c){
	switch(c){
		case "pi": return M_PI;
		default : std::cout<<"Constante "<<std::string(c)<<" non connu"<<std::endl;
	}
	return(-1);
}

template<typename T>
void Calculatrice<T>::evalExp(){
	double res;
	char * operateur;
	T operande1;
	T operande2;
	while(!pileOp.empty()){
		operateur = pileOp.top();
		pileOp.pop();
		if(estOp1(operateur)){
			operande1 = pileT.top();
			pileT.pop();
			res = op1(operateur, operande1);
			pileT.push(res);
		}
		else if(estOp2(operateur)){
			operande1 = pileT.top();
			pileT.pop();
			operande2 = pileT.top();
			pileT.pop();
			res = op2(operateur, operande2, operande1);
			pileT.push(res);
		}
	}
}

int main ()
{
  Calculatrice<float> cal;
  char str[100];
  int i = 0;
  char * pch;
  float resultat;
  float  valeur;
  std::cout<<"rentre ta chaine : "<<std::endl;
  std::cin.getline(str,sizeof(str));
  std::cout<<str<<std::endl;
  pch = strtok(str," ");
  while (pch != NULL)
  {
    //On rempli les piles en fonction des operateur qu'on chope dans le tableau. 
    if(cal.estOp1(pch)){
    	cal.pileOp.push(pch);
    }
    else if(cal.estOp2(pch)){
    	cal.pileOp.push(pch);
    }
    else{
    	cal.estT(pch,valeur);
    	cal.pileT.push(valeur);
    }
    pch = strtok (NULL, " ");
  }
  cal.evalExp();
  resultat = cal.pileT.top();
  std::cout << resultat << std::endl;
  return 0;
}