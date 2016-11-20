import numpy as np
import matplotlib.pyplot as plt
import math
import scipy.stats as stats
from scipy import pi

from sklearn import datasets


#code brouillon, devrait etre ameliorer, mise en place de fonction et autres


#fonction pour caluler la vraisemblance grâce a la matrice variance covariance et la moyenne
def calculer_Prob(cov, mean, x):

    tmp =  np.dot(np.transpose(np.asarray(x) - np.asarray(mean)), np.linalg.inv(cov))
    expo = np.dot(tmp,(np.asarray(x) - np.asarray(mean)))
    expo = math.exp(-expo/2.0)

    deno = (2*pi)*(pow(np.linalg.norm(cov),1/2))

    res = expo/deno

    return res






#Obtention des donnes
irisData = datasets.load_iris()
CirisData = np.c_[irisData.data.reshape(len(irisData.data), -1), irisData.target.reshape(len(irisData.target), -1)]


#Decoupage du corpus en aleatoire 2/3 (train) et 1/3 (dev + test)

np.random.seed(987654321) ;
np.random.shuffle(CirisData);

shuffledIrisData = CirisData[ :, :irisData.data.size//len(irisData.data)].reshape(irisData.data.shape)
shuffledIrisTarget = CirisData[ :, irisData.data.size//len(irisData.data) :].reshape(irisData.target.shape)

apprentissageData = shuffledIrisData[0:100]
devData = shuffledIrisData[100:130]
testData = shuffledIrisData[130:150]

apprentissageTar = shuffledIrisTarget[0:100]
devTar = shuffledIrisTarget[100:130]
testTar = shuffledIrisTarget[130:150]

apprentissageData = np.column_stack((apprentissageData,apprentissageTar))
devData = np.column_stack((devData,devTar))
testData= np.column_stack((testData,testTar))



#======================================== APPRENTISSAGE ==================================



# Calcul de l'apriori pour chaque classe

nbZero = apprentissageTar.tolist().count(0)
nbUn = apprentissageTar.tolist().count(1)
nbDeux = apprentissageTar.tolist().count(2)

aPriori0 = nbZero/100
aPriori1 = nbUn/100
aPriori2 = nbDeux/100

tab = [nbZero,nbUn,nbDeux]

tabClassZero = []
tabClassUn = []
tabClassDeux = []

for i in range(100):
    if(apprentissageTar[i]==0):
        tabClassZero.append(apprentissageData[i].tolist())
    elif(apprentissageTar[i]==1):
        tabClassUn.append(apprentissageData[i].tolist())
    elif(apprentissageTar[i]==2):
        tabClassDeux.append(apprentissageData[i].tolist())

matClassZero = np.asarray(tabClassZero)
matClassUn = np.asarray(tabClassUn)
matClassDeux = np.asarray(tabClassDeux)



print("\n SECTION APPRENTISSAGE\n")
# print('Affichage des donnees en fonction de la classe')
# print(matClassZero)
# print("\n=============================\n")
# print(matClassUn)
# print("\n=============================\n")
# print(matClassDeux)
# print("\n=============================\n")

tabMoyClassZero = [0,0,0,0]
tabMoyClassUn = [0,0,0,0]
tabMoyClassDeux = [0,0,0,0]
tabVarClassZero = [0,0,0,0]
tabVarClassUn = [0,0,0,0]
tabVarClassDeux = [0,0,0,0]



#calcul moy et variance
for i in range(4):
    tabMoyClassZero[i] = np.mean(matClassZero[:,i])
    tabMoyClassUn[i] = np.mean(matClassUn[:,i])
    tabMoyClassDeux[i] = np.mean(matClassDeux[:,i])
    tabVarClassZero[i] = np.var(matClassZero[:,i])
    tabVarClassUn[i] = np.var(matClassUn[:,i])
    tabVarClassDeux[i] = np.var(matClassDeux[:,i])


print('\n\n\nAffichage des moyenne et variance en fonction de la classe')
print('\nMOYENNE\n')
print(tabMoyClassZero)
print("\n=============================\n")
print(tabMoyClassUn)
print("\n=============================\n")
print(tabMoyClassDeux)
print("\n=============================\n")
print('\nVARIANCE\n')
print(tabVarClassZero)
print("\n=============================\n")
print(tabVarClassUn)
print("\n=============================\n")
print(tabVarClassDeux)
print("\n=============================\n")


C0Col1 = matClassZero[:,0]
C0Col2 = matClassZero[:,1]
C0Col3 = matClassZero[:,2]
C0Col4 = matClassZero[:,4]

C1Col1 = matClassZero[:,0]
C1Col2 = matClassZero[:,1]
C1Col3 = matClassZero[:,2]
C1Col4 = matClassZero[:,4]

C2Col1 = matClassZero[:,0]
C2Col2 = matClassZero[:,1]
C3Col3 = matClassZero[:,2]
C4Col4 = matClassZero[:,4]


#test affichage des gaussiennes

x = np.linspace(-5,10,100)
vrais00 = stats.norm.pdf(x,tabMoyClassZero[0],math.sqrt(tabVarClassZero[0]))
vrais01 = stats.norm.pdf(x,tabMoyClassZero[1],math.sqrt(tabVarClassZero[1]))
vrais02 = stats.norm.pdf(x,tabMoyClassZero[2],math.sqrt(tabVarClassZero[2]))
vrais03 = stats.norm.pdf(x,tabMoyClassZero[3],math.sqrt(tabVarClassZero[3]))
vrais10 = stats.norm.pdf(x,tabMoyClassUn[0],math.sqrt(tabVarClassUn[0]))
vrais11 = stats.norm.pdf(x,tabMoyClassUn[1],math.sqrt(tabVarClassUn[1]))
vrais12 = stats.norm.pdf(x,tabMoyClassUn[2],math.sqrt(tabVarClassUn[2]))
vrais13 = stats.norm.pdf(x,tabMoyClassUn[3],math.sqrt(tabVarClassUn[3]))
vrais20 = stats.norm.pdf(x,tabMoyClassDeux[0],math.sqrt(tabVarClassDeux[0]))
vrais21 = stats.norm.pdf(x,tabMoyClassDeux[1],math.sqrt(tabVarClassDeux[1]))
vrais22 = stats.norm.pdf(x,tabMoyClassDeux[2],math.sqrt(tabVarClassDeux[2]))
vrais23 = stats.norm.pdf(x,tabMoyClassDeux[3],math.sqrt(tabVarClassDeux[3]))

plt.subplot(221)
plt.plot(x,vrais00*aPriori0)
plt.plot(x,vrais10*aPriori1)
plt.plot(x,vrais20*aPriori2)


plt.subplot(222)
plt.plot(x,vrais01*aPriori0)
plt.plot(x,vrais11*aPriori1)
plt.plot(x,vrais21*aPriori2)


plt.subplot(223)
plt.plot(x,vrais02*aPriori0)
plt.plot(x,vrais12*aPriori1)
plt.plot(x,vrais22*aPriori2)


plt.subplot(224)
plt.plot(x,vrais03*aPriori0)
plt.plot(x,vrais13*aPriori1)
plt.plot(x,vrais23*aPriori2)





#======================================== DEVELOPPEMENT ==================================

fetcher00 = matClassZero[:,0]
fetcher01 = matClassZero[:,1]
fetcher02 = matClassZero[:,2]
fetcher03 = matClassZero[:,3]

fetcher10 = matClassUn[:,0]
fetcher11 = matClassUn[:,1]
fetcher12 = matClassUn[:,2]
fetcher13 = matClassUn[:,3]

fetcher20 = matClassDeux[:,0]
fetcher21 = matClassDeux[:,1]
fetcher22 = matClassDeux[:,2]
fetcher23 = matClassDeux[:,3]


fetchersClassZero=[fetcher00,fetcher01,fetcher02,fetcher03]
fetchersClassUn=[fetcher10,fetcher11,fetcher12,fetcher13]
fetchersClassDeux=[fetcher20,fetcher21,fetcher22,fetcher23]
x0=0
x1=0
x2=0

tabResult =[]
vecteurdevtest = [5.1,2.5]
vecteurtest = [tabMoyClassDeux[0],tabMoyClassDeux[1]]


print("\n SECTION DEVELOPPEMENT \n")
print("\n On prédit les classes de chaque element du corpus de dev selon tous les modeles\n ")
print("\n On regarde le nombre d'erreur selon chaque modele\n ")




#pour chaque modele et chaque vecteur du corpus de test on calcule la probablité d'appartennance a une classe
for i in range(4):
    for j in range(4):
        for x in range(30):
            if i!=j:

                x0=calculer_Prob(np.cov((fetchersClassZero[i]),(fetchersClassZero[j])),[tabMoyClassZero[i],tabMoyClassZero[j]],devData[x,[i,j]])*aPriori0
                x1=calculer_Prob(np.cov(fetchersClassUn[i],fetchersClassUn[j]),[tabMoyClassUn[i],tabMoyClassUn[j]],devData[x,[i,j]])*aPriori1
                x2=calculer_Prob(np.cov(fetchersClassDeux[i],fetchersClassDeux[j]),[tabMoyClassDeux[i],tabMoyClassDeux[j]],devData[x,[i,j]])*aPriori2


                if x2>x1>x0:
                    tabResult.append([i,j,2])
                elif x1>x2>x0:
                    tabResult.append([i,j,1])
                else:
                    tabResult.append([i,j,0])

#np.reshape(tabResult,(len(tabr,3))

test =np.reshape(tabResult, len(tabResult)*3)
test = np.reshape(test, (-1,3) )

print("\n colonne 1 : caracteristique 1 (ex : 0 : longueur sépale), colonne 2 : carac 2, colonne 3 : classe prédite\n")
print(test)


y=0
i=0
cptError=0
nbErrorModele = []



ind_devtar=0


#on a toute les classes predites pour tous les modeles dans l'ordre dans une matrice
#on parcourt la matrice et la on compare la classe predite a la classe reelle
#on creer une nouvelle matrice qui contient les numeros des caracteristiques et le nombre d'erreurs associe

for x in range(360):


    if(ind_devtar>=30):
        ind_devtar=0

    if(test[x,2]!=devTar[ind_devtar]):
        cptError=cptError+1


    ind_devtar=ind_devtar+1


    if(x>=y+30):
        y=x
        i=i+1
        nbErrorModele.append([test[x,0],test[x,1],cptError])

        cptError=0


print("\n colonne 1 : carac 1, colonne 2 : carac 2, colonne 3 : nb erreur\n")
nbErrorModele =np.reshape(nbErrorModele, len(nbErrorModele)*3)
nbErrorModele=np.reshape(nbErrorModele,(-1,3))
print(nbErrorModele)




#======================================== TEST ==================================

print("\n SECTION DE TEST \n")
print("\n Choix du modele colonne 3 et 2, longueur petale et largeur sépale\n")
print("\n matrice de confusion pour ce modele sur le corpus de test\n")

tabClassConfu=[]

#meme chose que dans le corpus de dev mais cette fois avec le meilleur modele et sur le corpus de test
for x in range(20):
    x0=calculer_Prob(np.cov((fetchersClassZero[2]),(fetchersClassZero[1])),[tabMoyClassZero[2],tabMoyClassZero[1]],testData[x,[2,1]])*aPriori0
    x1=calculer_Prob(np.cov(fetchersClassUn[2],fetchersClassUn[1]),[tabMoyClassUn[2],tabMoyClassUn[1]],testData[x,[2,1]])*aPriori1
    x2=calculer_Prob(np.cov(fetchersClassDeux[2],fetchersClassDeux[1]),[tabMoyClassDeux[2],tabMoyClassDeux[1]],testData[x,[2,1]])*aPriori2


    if x2>x1>x0:
        tabClassConfu.append(2)
    elif x1>x2>x0:
        tabClassConfu.append(1)
    else:
        tabClassConfu.append(0)


print(tabClassConfu)

#on incremente la position dans la matrice qui correspond, en axe x on a la classe reelle et en axe y on a la classe predite
matriceConfu=[0,0,0,0,0,0,0,0,0]

matriceConfu=np.reshape(matriceConfu,(3,3))
cptError2=0
for x in range(20):
    matriceConfu[testTar[x],tabClassConfu[x]]=matriceConfu[testTar[x],tabClassConfu[x]]+1
    if(testTar[x]!=tabClassConfu[x]):
        cptError2=cptError2+1

precision=(20-cptError2)/20*100
print(precision)
print(matriceConfu)