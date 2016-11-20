/*# Victorien Grudé 
# Etienne Pagis
#*/


succNum(0,1).
succNum(1,2).
succNum(2,3).
succNum(3,4).
succNum(4,5).
succNum(5,6).
succNum(6,7).
succNum(7,8).
succNum(8,9).


succAlpha(z,a).
succAlpha(a,b).
succAlpha(b,c).
succAlpha(c,d).
succAlpha(d,e).
succAlpha(e,f).
succAlpha(f,g).
succAlpha(g,h).
succAlpha(h,z).

isCol(a).
isCol(b).
isCol(c).
isCol(d).
isCol(e).
isCol(f).
isCol(g).
isCol(h).

isLig(1).
isLig(2).
isLig(3).
isLig(4).
isLig(5).
isLig(6).
isLig(7).
isLig(8).


campAdverse(x,o).
campAdverse(o,x).


 grilleDeDepart([
 	[-,-,-,-,-,-,-,-],
 	[-,-,-,-,-,-,-,-],
 	[-,-,-,-,-,-,-,-],
 	[-,-,-,o,x,-,-,-],
 	[-,-,-,x,o,-,-,-],
 	[-,-,-,-,-,-,-,-],
 	[-,-,-,-,-,-,-,-],
 	[-,-,-,-,-,-,-,-]]
 	).


/*
/*Affichage d'une ligne de la grille*/
afficherLigne([]).
afficherLigne([H|T]):- write(H),tab(3),afficherLigne(T).

/*Affichage des lettres de la grille*/
afficherLettre(h):-tab(3),write(h),nl,!.
afficherLettre(X) :- tab(3),write(X),succAlpha(X,Y),afficherLettre(Y).

/*Affichage de la grille*/
afficherGrille2([],_).
afficherGrille2([H|T],X):- write(X),tab(2),succNum(X,Y), afficherLigne(H),writeln(''),afficherGrille2(T,Y).

afficheGrille(X):- afficherLettre(a),afficherGrille2(X,1).
*/


afficheLigne2([]):-!.
afficheLigne2([H|T]):-write(H),write('|'),afficheLigne2(T).

afficheLigne(X,A):-write(A),write('|'),afficheLigne2(X).

afficheGrille2([],_):-!.
afficheGrille2([H|T],X):-succNum(X,Y),afficheLigne(H,Y),nl,afficheGrille2(T,Y).

afficheGrille(X):-tab(1),write('|a|b|c|d|e|f|g|h|'),nl,afficheGrille2(X,0).


ligneDansGrille(1,[L|_],L).
ligneDansGrille(N,[_|T],L):- succNum(M,N),ligneDansGrille(M,T,L).


caseDansLigne(a,[V|_],V).
caseDansLigne(N,[_|T],V):- succAlpha(M,N),caseDansLigne(M,T,V).



donneValeurDeCase(G,N,M,V):-ligneDansGrille(M,G,L),caseDansLigne(N,L,V).


caseVide(G,N,M):-donneValeurDeCase(G,N,M,-).


direction(n,VL,VC,NL,VC):-succNum(NL,VL).
direction(ne,VL,VC,NL,NC):-succNum(NL,VL),succAlpha(VC,NC).
direction(e,VL,VC,VL,NC):-succAlpha(VC,NC).
direction(se,VL,VC,NL,NC):-succNum(VL,NL),succAlpha(VC,NC).
direction(s,VL,VC,NL,VC):-succNum(VL,NL).
direction(so,VL,VC,NL,NC):-succNum(VL,NL),succAlpha(NC,VC).
direction(o,VL,VC,VL,NC):-succAlpha(NC,VC).
direction(no,VL,VC,NL,NC):-succNum(NL,VL),succAlpha(NC,VC).



donneListeCaseDansDirection(D,G,VL,VC,[X|L]):-direction(D,VL,VC,NL,NC),donneValeurDeCase(G,NC,NL,X),
	donneListeCaseDansDirection(D,G,NL,NC,L).
donneListeCaseDansDirection(_,_,_,_,[]).


faitPrise(Camp,[H,Camp|_]):-campAdverse(Camp,H).
faitPrise(Camp,[H|T]):-campAdverse(Camp,H),faitPrise(Camp,T).


leCoupEstValide(G,Camp,VL,VC):-caseVide(G,VC,VL),donneListeCaseDansDirection(_,G,VL,VC,L),faitPrise(Camp,L).

/* #lanceLeJeu:-leCoupEstValide([[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,o,x,-,-,-],
# 	[-,-,-,x,o,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-]],x,5,f). 
# true.*/


modifieValeur2([[_|T]|S],VL,VC,VL,VC,V,[[V|T]|S]).
modifieValeur2([[X|_]|T],VL,VC,NL,h,V,[[X|[]]|S]):-succNum(NL,NNL),modifieValeur2(T,VL,VC,NNL,a,V,S).
modifieValeur2([[X|T]|Q],VL,VC,NL,NC,V,[[X|S]|Q1]):-succAlpha(NC,NNC),modifieValeur2([T|Q],VL,VC,NL,NNC,V,[S|Q1]).

modifieValeur(GD,VL,VC,Camp,GA):-modifieValeur2(GD,VL,VC,1,a,Camp,GA).


retournePionsDansDirection(D,GD,VL,VC,Camp,GF):-donneListeCaseDansDirection(D,GD,VL,VC,L),faitPrise(Camp,L),
	direction(D,VL,VC,NL,NC),donneValeurDeCase(GD,NC,NL,X),
	campAdverse(Camp,X),modifieValeur(GD,NL,NC,Camp,GA),
	retournePionsDansDirection(D,GA,NL,NC,Camp,GF).
retournePionsDansDirection(_,G,_,_,_,G).


/*# lanceLeJeu:-retournePionsDansDirection(e,[[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-], 
#   		[-,o,o,o,x,-,-,-],[-,-,-,x,o,o,o,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-]],  
#   		4,a,x,G),afficheGrille(G).  
# lanceLeJeu. 
#   |a|b|c|d|e|f|g|h| 
#  1|-|-|-|-|-|-|-|-| 
#  2|-|-|-|-|-|-|-|-| 
#  3|-|-|-|-|-|-|-|-| 
#  4|-|x|x|x|x|-|-|-| 
#  5|-|-|-|x|o|o|o|-| 
#  6|-|-|-|-|-|-|-|-|  
#  7|-|-|-|-|-|-|-|-| 
#  8|-|-|-|-|-|-|-|-| 
#  true .  */

coupJoueDansGrille(GD,VL,VC,Camp,GF):-leCoupEstValide(GD,Camp,VL,VC),
	retournePionsDansDirection(_,GD,VL,VC,Camp,GA),
	coupJoueDansGrille(GA,VL,VC,Camp,GI),modifieValeur(GI,VL,VC,Camp,GF).
coupJoueDansGrille(G,_,_,_,G).


/* #lanceLeJeu:- coupJoueDansGrille([[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],
# 	[-,o,o,o,x,-,-,-],[-,-,-,x,o,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-]],
# 	4,a,x,G),afficheGrille(G).
# lanceLeJeu.
#  |a|b|c|d|e|f|g|h|
# 1|-|-|-|-|-|-|-|-|
# 2|-|-|-|-|-|-|-|-|
# 3|-|-|-|-|-|-|-|-|
# 4|x|x|x|x|x|-|-|-|
# 5|-|-|-|x|o|-|-|-|
# 6|-|-|-|-|-|-|-|-|
# 7|-|-|-|-|-|-|-|-|
# 8|-|-|-|-|-|-|-|-|
# true .*/


comptePions2([[o|_]|S],NBX,NBO,VL,h,NBFX,NBFO):-NNBO is NBO +1,succNum(VL,NL),comptePions2(S,NBX,NNBO,NL,a,NBFX,NBFO).
comptePions2([[x|_]|S],NBX,NBO,VL,h,NBFX,NBFO):-NNBX is NBX +1,succNum(VL,NL),comptePions2(S,NNBX,NBO,NL,a,NBFX,NBFO).
comptePions2([[-|_]|S],NBX,NBO,VL,h,NBFX,NBFO):-succNum(VL,NL),comptePions2(S,NBX,NBO,NL,a,NBFX,NBFO).

comptePions2([[o|T]|S],NBX,NBO,VL,VC,NBFX,NBFO):-NNBO is NBO +1,succAlpha(VC,NC),
						comptePions2([T|S],NBX,NNBO,VL,NC,NBFX,NBFO).
comptePions2([[x|T]|S],NBX,NBO,VL,VC,NBFX,NBFO):-NNBX is NBX +1,succAlpha(VC,NC),
						comptePions2([T|S],NNBX,NBO,VL,NC,NBFX,NBFO).
comptePions2([[-|T]|S],NBX,NBO,VL,VC,NBFX,NBFO):-succAlpha(VC,NC),comptePions2([T|S],NBX,NBO,VL,NC,NBFX,NBFO).

comptePions2(_,NBX,NBO,_,_,NBX,NBO).

comptePions(G,NBFX,NBFO):-comptePions2(G,0,0,1,a,NBFX,NBFO).

/* #lanceLeJeu:-comptePions([[-,-,x,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,o,-,-],
# 	[-,o,o,o,x,-,-,-],[-,-,-,x,o,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,o,-,-,-,-]],
# 	NBX,NBO),write(NBX),tab(1),write(NBO).
# lanceLeJeu.
# 3 6
# true . */

coordonneesOuListe(X,Y,[X,Y]):-isLig(X),isCol(Y).


listeCaseVide2([[-|_]|S],[X|L],VL,h):-succNum(VL,NL),coordonneesOuListe(VL,h,X),listeCaseVide2(S,L,NL,a).
listeCaseVide2([[-|T]|S],[X|L],VL,VC):-succAlpha(VC,NC),coordonneesOuListe(VL,VC,X),listeCaseVide2([T|S],L,VL,NC).
listeCaseVide2([[_|_]|S],L,VL,h):-succNum(VL,NL),listeCaseVide2(S,L,NL,a).
listeCaseVide2([[_|T]|S],L,VL,VC):-succAlpha(VC,NC),listeCaseVide2([T|S],L,VL,NC).
listeCaseVide2([[-|_]|_],[X],8,h):-coordonneesOuListe(8,h,X),!.
listeCaseVide2([[_|_]|_],[],8,h):-!.


listeCaseVide(G,L):-listeCaseVide2(G,L,1,a).

/*#lanceLeJeu:-afficheGrille([[x,x,x,x,x,x,x,x],[-,x,x,x,x,-,x,x],[x,x,-,x,x,o,x,x],
# 	[-,o,o,o,x,x,x,x],[x,x,x,x,o,-,-,-],[x,x,x,x,x,x,x,x],[x,x,x,x,x,x,x,x],[x,x,x,o,x,x,x,-]]),
# 	nl,listeCaseVide([[x,x,x,x,x,x,x,x],[-,x,x,x,x,-,x,x],[x,x,-,x,x,o,x,x],
# 	[-,o,o,o,x,x,x,x],[x,x,x,x,o,-,-,-],[x,x,x,x,x,x,x,x],[x,x,x,x,x,x,x,x],[x,x,x,o,x,x,x,-]],L),write(L).

# lanceLeJeu.
#  |a|b|c|d|e|f|g|h|
# 1|x|x|x|x|x|x|x|x|
# 2|-|x|x|x|x|-|x|x|
# 3|x|x|-|x|x|o|x|x|
# 4|-|o|o|o|x|x|x|x|
# 5|x|x|x|x|o|-|-|-|
# 6|x|x|x|x|x|x|x|x|
# 7|x|x|x|x|x|x|x|x|
# 8|x|x|x|o|x|x|x|-|
# [[2,a],[2,f],[3,c],[4,a],[5,f],[5,g],[5,h],[8,h]]
# true . */


listeDesCoupsCamp2(_,_,[],[]):-!.
listeDesCoupsCamp2(G,Camp,[H|T],[H|L]):-coordonneesOuListe(VL,VC,H),leCoupEstValide(G,Camp,VL,VC),
				listeDesCoupsCamp2(G,Camp,T,L),!.
listeDesCoupsCamp2(G,Camp,[_|T],L):-listeDesCoupsCamp2(G,Camp,T,L),!.

listeDesCoupsCamp(G,Camp,L):-listeCaseVide(G,L2),listeDesCoupsCamp2(G,Camp,L2,L).


/* # lanceLeJeu:-listeDesCoupsCamp([[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],
	# 	[-,-,-,o,x,-,-,-],[-,-,-,x,o,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-]],
	# 	x,L),write(L).
# lanceLeJeu.
# [[3,d],[4,c],[5,f],[6,e]]
# true . */

partieGagnee(G,x):-comptePions(G,NBX,NBO),!,NBX>NBO,!.
partieGagnee(G,o):-comptePions(G,NBX,NBO),!,NBO>NBX,!.

/* # lanceLeJeu:-partieGagnee([[x,x,x,x,x,x,x,x],[-,x,x,x,x,-,x,x],[x,x,-,x,x,o,x,x],
#  	[-,o,o,o,x,x,x,x],[x,x,x,x,o,-,-,-],[x,x,x,x,x,x,x,x],[x,x,x,x,x,x,x,x],[x,x,x,o,x,x,x,-]],o).
# lanceLeJeu.
# false.*/



duneListeALautre([C|H],C,H):-!.
duneListeALautre([H|L1],C,[H|L2]):-duneListeALautre(L1,C,L2).

/* #  lanceLeJeu:-duneListeALautre([[a,1],[a,2],[a,3]], [a,2], [[a,1],[a,3]]) .
#  lanceLeJeu.
#  true.*/


joueLeCoup(Case,Valeur,GD,GA):-coordonneesOuListe(VL,VC,Case),leCoupEstValide(GD,Valeur,VL,VC),
						coupJoueDansGrille(GD,VL,VC,Valeur,GA),afficheGrille(GA).

/* # lanceLeJeu:-joueLeCoup([4,a],x,[[x,x,x,x,x,x,x,x],[-,x,x,x,x,-,x,x],[x,x,-,x,x,o,x,x],
#   	[-,o,o,o,x,x,x,x],[x,x,x,x,o,-,-,-],[x,x,x,x,x,x,x,x],[x,x,x,x,x,x,x,x],[x,x,x,o,x,x,x,-]],_).
# lanceLeJeu.
#  |a|b|c|d|e|f|g|h|
# 1|x|x|x|x|x|x|x|x|
# 2|-|x|x|x|x|-|x|x|
# 3|x|x|-|x|x|o|x|x|
# 4|x|x|x|x|x|x|x|x|
# 5|x|x|x|x|o|-|-|-|
# 6|x|x|x|x|x|x|x|x|
# 7|x|x|x|x|x|x|x|x|
# 8|x|x|x|o|x|x|x|-|
# true .*/

saisieUnCoup(NL,NC):-read(NL),read(NC).

/*# lanceLeJeu:-saisieUnCoup(X,Y),write("Les valeurs de rentrees sont : "),write(X),tab(1),write(Y).
# lanceLeJeu.
# |: 4.
# |: b.
# Les valeurs de rentrees sont : 4 b
# true.*/


moteur(G,[],Camp):-nl,partieGagnee(G,Camp),!,write("Joueur "),write(Camp),write(" a gagne").
moteur(G,[],Camp):-nl,campAdverse(Camp,A),partieGagnee(G,A),!,write("Joueur "),write(A),write(" a gagne").
moteur(_,[],_):-nl,write("Grille remplie sans gagnant").

moteur(G,L,x):-listeDesCoupsCamp(G,x,L1),L1\==[],nl,write("Veuillez saisir un coup joueur x "),nl,
				saisieUnCoup(X,Y),coordonneesOuListe(X,Y,C),
				joueLeCoup(C,x,G,GA),duneListeALautre(L,C,LA),moteur(GA,LA,o).
moteur(G,L,x):-listeDesCoupsCamp(G,x,L1),L1\==[],nl,write("Coup non valide"),moteur(G,L,x).


/*Ici le moteur gere le joueur contre joueur uniquement*/

moteur(G,L,o):-listeDesCoupsCamp(G,o,L1),L1\==[],nl,write("Veuillez saisir un coup joueur o "),nl,
				saisieUnCoup(X,Y),coordonneesOuListe(X,Y,C),
				joueLeCoup(C,o,G,GA),duneListeALautre(L,C,LA),moteur(GA,LA,x).
moteur(G,L,o):-listeDesCoupsCamp(G,o,L1),L1\==[],nl,write("Coup non valide"),moteur(G,L,o).



moteur(G,L,Camp):-campAdverse(Camp,A),listeDesCoupsCamp(G,A,L1),!,L1\==[],
			nl,write("Plus de coup valide pour le joueur "),write(Camp),moteur(G,L,A).


moteur(G,_,Camp):-write("Plus de coup valide"),moteur(G,[],Camp).


lanceLeJeu:-grilleDeDepart(G),afficheGrille(G),listeCaseVide(G,L),!,moteur(G,L,x).











