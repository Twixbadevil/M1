#!/usr/bin/python3

import numpy as np
import matplotlib.pyplot as plt
import math 
import scipy.stats as stats
from scipy import pi

from sklearn import datasets
irisData = datasets.load_iris()
#print (irisData.data)
#print (irisData.target)

CirisData = np.c_[irisData.data.reshape(len(irisData.data), -1), irisData.target.reshape(len(irisData.target), -1)]
np.random.seed(24681012) ;
np.random.shuffle(CirisData);
shuffledIrisData = CirisData[ :, :irisData.data.size//len(irisData.data)].reshape(irisData.data.shape)
shuffledIrisTarget = CirisData[ :, irisData.data.size//len(irisData.data) :].reshape(irisData.target.shape)

apprentissageData = shuffledIrisData[0:100]
devData = shuffledIrisData[100:130]
testData = shuffledIrisData[130:150]

apprentissageTar = shuffledIrisTarget[0:100]
devTar = shuffledIrisTarget[100:130]
testTar = shuffledIrisTarget[130:150]

nbZero = apprentissageTar.tolist().count(0)
nbUn = apprentissageTar.tolist().count(1)
nbDeux = apprentissageTar.tolist().count(2)

tab = [nbZero,nbUn,nbDeux]
print("Apriori la classe", tab.index(max(tab)), "est dominante avec", max(tab),"apparitions.")

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

tabMoyClassZero = [0,0,0,0]
tabMoyClassUn = [0,0,0,0]
tabMoyClassDeux = [0,0,0,0]
tabVarClassZero = [0,0,0,0]
tabVarClassUn = [0,0,0,0]
tabVarClassDeux = [0,0,0,0]

for i in range(4):
    tabMoyClassZero[i] = np.mean(matClassZero[:,i])
    tabMoyClassUn[i] = np.mean(matClassUn[:,i])
    tabMoyClassDeux[i] = np.mean(matClassDeux[:,i])
    tabVarClassZero[i] = np.var(matClassZero[:,i])
    tabVarClassUn[i] = np.var(matClassUn[:,i])
    tabVarClassDeux[i] = np.var(matClassDeux[:,i])

print("\nMoyenne classe 0\n")
print(tabMoyClassZero)
print("\nVariance classe 0\n")
print(tabVarClassZero)
print("\n======================================================\n")
print("\nMoyenne classe 1\n")
print(tabMoyClassUn)
print("\nVariance classe 1\n")
print(tabVarClassUn)
print("\n======================================================\n")
print("\nMoyenne classe 2\n")
print(tabMoyClassDeux)
print("\nVariance classe 2\n")
print(tabVarClassDeux)
print("\n======================================================\n")


# tabVal00 = matClassZero[:,0]
# tabVal01 = matClassZero[:,1]
# tabVal02 = matClassZero[:,2]
# tabVal03 = matClassZero[:,3]

# tabVal10 = matClassUn[:,0]
# tabVal11 = matClassUn[:,1]
# tabVal12 = matClassUn[:,2]
# tabVal13 = matClassUn[:,3]

# tabVal20 = matClassDeux[:,0]
# tabVal21 = matClassDeux[:,1]
# tabVal22 = matClassDeux[:,2]
# tabVal23 = matClassDeux[:,3]

# vecteurMoy001 = [tabMoyClassZero[0],tabMoyClassZero[1]]
# cov001 = np.cov(tabVal00,tabVal01, ddof=0)

# print(cov001)

coef0 = nbZero/100
coef1 = nbUn/100
coef2 = nbDeux/100

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
plt.plot(x,vrais00*coef0)
plt.plot(x,vrais10*coef1)
plt.plot(x,vrais20*coef2)

plt.subplot(222)
plt.plot(x,vrais01*coef0)
plt.plot(x,vrais11*coef1)
plt.plot(x,vrais21*coef2)

plt.subplot(223)
plt.plot(x,vrais02*coef0)
plt.plot(x,vrais12*coef1)
plt.plot(x,vrais22*coef2)

plt.subplot(224)
plt.plot(x,vrais03*coef0)
plt.plot(x,vrais13*coef1)
plt.plot(x,vrais23*coef2)

plt.savefig("gaussian.png")
plt.show()
