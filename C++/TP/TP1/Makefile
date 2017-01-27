coureur: main.o commissaire.o temps.o coureur.o
	g++ main.o commissaire.o temps.o coureur.o -o coureur

main.o: main.cpp
	g++ -c main.cpp -o main.o

commissaire.o: commissaire.cpp
	g++ -c commissaire.cpp -o commissaire.o

temps.o: temps.cpp
	g++ -c temps.cpp -o temps.o

coureur.o: coureur.cpp
	g++ -c coureur.cpp -o coureur.o

clean:
	rm -rf *.o coureur