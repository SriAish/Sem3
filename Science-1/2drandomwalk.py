import random
import matplotlib.pyplot as pl
from math import factorial as fact
from math import sin, cos

def th_prob(x):
	return fact(2*x)/( ( fact(x) ** 2 ) * ( 2**(2*x) ) )

ele = [0,0]
N=1000
N = N + 1
experiments=1000
Calculated=[0]*(N)
Steps=[x for x in range(N)]

for j in range(1,N):
    d2=random.uniform(0,360)
    ele[0] += cos(d2)
    ele[1] += sin(d2)

print(ele)
