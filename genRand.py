#!/usr/bin/python
#encoding:utf-8
import random
import numpy as np
import os

# N=20

# a=[i for i in range(N)]
# a=random.shuffle(a) #permutate array

# a=[random.randint(0,2*N) for i in range(N)]
# a[N-N/2]=40
# a[N-N/3]=60
# a[N-N/4]=60
# a[N-N/5]=50
# a[N/5]=50
# a[N/4]=50
# a[N/3]=50
# a[N/2-N/8]=50

# a=random.sample(xrange(1,N+1), N) # unique int elements 
# a[-2]=a[3]

# a=[random.uniform(0,100) for i in range(100)] # random floats
# a=[int(os.urandom(1).encode('hex'),16) for i in range(N)]

"""for almost ordered arr:"""
# a=[i for i in range(N)]
# a[-1]=a[0]
# a[0]=a[31]
# # if N>10000:
# # 	a[-1000]=a[10000]
# a[N-N/2]=40
# a[N-N/3]=60
# a[N-N/4]=60
# a[N-N/5]=50
# a[N/5]=50
# a[N/4]=50
# a[N/3]=50
# a[N/2-N/8]=50

# """for almost ordered unique elemented arr:"""
# a=[i for i in range(N)]
# a[-1]=-N/3
# a[0]=-a[31]
# if N>10001:
# 	a[-1000]=-a[10000]



# print a
# print max(a)
# print min(a)

# a=[i for i in range(N)]
# a=random.shuffle(a) #permutate array

N=3000000
p=100000
# a=[[random.randint(1,2*p),np.log(np.abs(random.randint(1,2*p)))] for i in range(N)]
a=[[i+1,np.log(i+2)] for i in range(N)]
a[N-N/2]=[40,np.log(39)]
a[N-N/3]=[60,np.log(55)]
a[N-N/4]=[60,np.log(50)]
a[N-N/5]=[60,np.log(45)]
a[N/5]=[50,np.log(45)]
a[N/4]=[50,np.log(30)]
a[N/3]=[50,np.log(25)]
a[N/2-N/8]=[50,np.log(20)]

lines=[str(item[0])+' '+str(item[1])+'\n' for item in a]

#lines.insert(0,str(len(a))+'\n')
#lines[-1]=str(a[-1])

with open('pairs.dat', 'w') as f:
	# f.write(fline)
	for line in lines:
		f.write(line)
