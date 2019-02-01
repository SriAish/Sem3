import random
import matplotlib.pyplot as pl
from math import factorial as fact

def th_prob(x):
	return fact(2*x)/( ( fact(x) ** 2 ) * ( 2**(2*x) ) )


N=1000
N = N + 1
experiments=1000
Calculated=[0]*(N)
Steps=[x for x in range(N)]
Theoretical=[th_prob(x) for x in range(N)]

for i in range(experiments+1):
	a, b = 0, 0
	for j in range(1,N):
		d1=random.uniform(0,1)
		d2=random.uniform(0,1)
		a += 1 if d1>0.5 else -1
		b += 1 if d2>0.5 else -1
		if a==b :
			Calculated[j]+=1

Calculated[0]=1
for x in range (1,N):
	Calculated[x]=Calculated[x]/experiments

pl.plot(Steps, Calculated, 'r-', label="Calculated Probability")
pl.plot(Steps, Theoretical, 'b-', label="Theoritical Probability")
pl.legend()
pl.xlabel('Number of steps')
pl.ylabel('Probability of meeting (theoritical and calculated)')
pl.title('Theoritical vs Calculated Probability')
pl.show()

