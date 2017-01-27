

import numpy as np
import matplotlib.pyplot as plt
import math 
import scipy.stats as stats
from scipy import pi
import random

def xor(a,b):
	if a!=b:
		return 1
	return 0


def xorTab(a,b):
	la = len(a)
	lb = len(b)
	lm = la * lb
	final = []

	for i in range(1,lb):
		for j in range(la):
			a.append(a[j])
	
	for i in range(1,la):
		for j in range(lb):
			b.append(b[j])
	
	for i in range(lm):
		final.append(xor(a[i],b[i]))

	return(final)




def pgcd(a,b) :  
	while a%b != 0 : 
		a, b = b, a%b 
	return b

def premier(a,b):
	return pgcd(a,b)==1

def longueurMax(vecteur):
	return ((pow(2,vecteur[0]))-1)

def codeLongueurMax(polyGen,vecteurInit):
	LM = longueurMax(polyGen)
	vecteur = vecteurInit
	codeFinal = [];


	for j in range(LM):
		#print(vecteur)

		tmp = vecteur.pop()
		codeFinal.append(tmp)

		for i in range(1,len(polyGen)):
			tmp = xor(tmp,vecteur[polyGen[i]-1])

		vecteur.insert(0,tmp)

	return codeFinal


def codeGold(poly1,poly2,vecteurInit1,vecteurInit2):
	LM1 = longueurMax(poly1)
	LM2 = longueurMax(poly2)
	
	codeGold = []

	if(LM1 == LM2):
		codeLM1 = codeLongueurMax(poly1,vecteurInit1)
		codeLM2 = codeLongueurMax(poly2,vecteurInit2)

		for i in range(len(codeLM1)):
			tmp = xor(codeLM1[i],codeLM2[i])
			codeGold.append(tmp)

	else:
		print("Les longueurs des vecteurs doivent etre egale")

	return codeGold


def codeJPL(codeLM,LM):
	result = True
	codeJPL = []
	
	for i in range(len(LM)):
		for j in range(len(LM)):
			if (i<j):
				result = result and premier(LM[i],LM[j])

	if(result):
		codeJPL = codeLM[0]
		for i in range(1,len(codeLM)):
			codeJPL = xorTab(codeJPL,codeLM[i])
	else:
		print("Les longueurs ne sont pas première entre elle")

	return codeJPL


def mainCodeLongeurMax():
	polynome = []
	vecteur = []

	LP = int(input("Entrez la taille du polynome1 : "))

	for i in range(LP):
		tmp = int(input("Entrez les valeurs une a une du polynome1 : "))
		polynome.append(tmp)

	LV = polynome[0]

	for i in range(LV):
		tmp = int(input("Entrez les valeurs une a une du vecteur1 : "))
		vecteur.append(tmp)

	code = codeLongueurMax(polynome,vecteur)
	print(code)


def mainGold():
	polynome1 = []
	vecteur1 = []
	polynome2 = []
	vecteur2 = []

	LP1 = int(input("Entrez la taille du polynome1 : "))

	for i in range(LP1):
		tmp = int(input("Entrez les valeurs une a une du polynome1 : "))
		polynome1.append(tmp)

	LV1 = polynome1[0]

	for i in range(LV1):
		tmp = int(input("Entrez les valeurs une a une du vecteur1 : "))
		vecteur1.append(tmp)

	LP2 = int(input("Entrez la taille du polynome2 : "))

	for i in range(LP2):
		tmp = int(input("Entrez les valeurs une a une du polynome2 : "))
		polynome2.append(tmp)

	LV2 = polynome2[0]

	for i in range(LV2):
		tmp = int(input("Entrez les valeurs une a une du vecteur2 : "))
		vecteur2.append(tmp)

	code = codeGold(polynome1,polynome2,vecteur1,vecteur2)
	print(code)



def mainJPL():

	NBC = int(input("Entrez le nombre de code a LM a combiener : "))

	codeLM =[]
	LM = []

	for i in range(NBC):
		polynome = []
		vecteur = []
		print(" =========== CODE "+str(i)+"=========== ")

		LP = int(input("Entrez la taille du polynome : "))

		for i in range(LP):
			tmp = int(input("Entrez les valeurs une a une du polynome : "))
			polynome.append(tmp)

		LV = polynome[0]
		
		LM.append(longueurMax(polynome))

		for i in range(LV):
			tmp = int(input("Entrez les valeurs une a une du vecteur : "))
			vecteur.append(tmp)

		codeLM.append(codeLongueurMax(polynome,vecteur))

	code = codeJPL(codeLM,LM)
	print(code)
	


while True :
	print("Menu \n1 - Code de Longueur Max \n2 - Code de Gold \n3 - Code JPL \n4 - Quitter")
	choix = int(input("Votre choix :"))
	if(choix == 1):
		mainCodeLongeurMax()
	elif(choix == 2):
		mainGold()
	elif(choix == 3):
		mainJPL()
	elif (choix == 4):
		break
	else:
		print("Choix invalide")



