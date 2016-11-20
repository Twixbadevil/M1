import math
import numpy as np
import random

nbUsers=13
tailleMsg=4



def hadamard(n):
	if n<1:
		n=0

	H = np.array([[1]])
	for i in range(0,n):
		H = np.vstack((np.hstack((H, H)), np.hstack((H, -H))))
	return H



def trouverTailleMatrix(nbUsers):
	

	taille = int(math.ceil(pow(nbUsers,0.5)))
	return taille



def generateMessage(tailleMessage):
	message=[]
	for i in range(tailleMessage):
		x=random.getrandbits(1)
		if x==0:
			x=-1
		else:
			x=1
		message.append(x)
	return message





def generateAllMessages(matrixHadamard):
	messages = []
	for i in range(len(matrixHadamard[:,0])):

		messages.append(generateMessage(4))

	messages=np.reshape(messages,(-1,4))
	return messages


def etalement(messages, matrixHadamard):
	etalements=[]

	etalementCourant=[]


	for x in range(nbUsers):
		messageCourant= messages[x,:]
		cleUser= matrixHadamard[x,:]
		for i in range(0, len(messageCourant)):
			for j in range(0, len(cleUser)):		
				etalementCourant.append(messageCourant[i]*cleUser[j])

		etalements.append(etalementCourant)
		etalementCourant=[]

	etalements=np.reshape(etalements,(nbUsers,-1))
	return etalements





def sum_mess(mess):
	return np.cumsum(mess,0)[len(mess)-1]




hada = hadamard(trouverTailleMatrix(nbUsers))

mess = generateAllMessages(hada)


listeMessagesEtales = etalement(mess,hada)

messageFinal = sum_mess(listeMessagesEtales)




def desetalement(messageFinal, matrixHadamard, nbUsers, tailleMsg):
	listeMessagesDesetale = []
	messageCourant = []
	msgFinalDivise=[]
	step= len(messageFinal)/tailleMsg


	for x in range(tailleMsg):
		msgFinalDivise.append(messageFinal[x*step:step*(x+1)])
	msgFinalDivise=np.reshape(msgFinalDivise,(-1,step))


	
	for y in range(nbUsers):
		for x in range(tailleMsg):
			for i in range(16):
				msgFinalDivise[x,i]= msgFinalDivise[x,i]*matrixHadamard[y,i]
			messageCourant.append(sum(msgFinalDivise[x,:])/16)
		listeMessagesDesetale.append(messageCourant)
		messageCourant=[]

	
	listeMessagesDesetale=np.reshape(listeMessagesDesetale,(-1,tailleMsg))

	return listeMessagesDesetale




print(mess)
print("==========")
print(desetalement(messageFinal,hada,nbUsers,tailleMsg))
