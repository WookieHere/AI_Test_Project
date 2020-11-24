
import matplotlib.pyplot as plt
import numpy as np
import re
import random as rd


def findMax(list):
    max = 0.0
    for i in range(len(list)):
        for j in range(len(list[i])):
            if list[i][j] > max:
                max = list[i][j]
    return max


def findMin(list):
    min = 99999999.0
    for i in range(len(list)):
        for j in range(len(list[i])):
            if list[i][j] < min:
                min = list[i][j]
    return min


temp = []
i = 0
x_coord = [[]]
y_coord = [[]]
with open("test.txt", "r") as f:
    for line in f:
        if line.endswith('}\n'):    #everytime there is a new player append another list
            i = i + 1
            x_coord.append([])
            y_coord.append([])
        elif line.startswith('{\n'):    #this is the start of a new player
            print("Next Player: ", i)
        else:
            for p in re.split('[{}, \n]', line):
                temp.append(p)
            x_coord[i].append(float(temp[0]))   #append what was in temp and convert it to a float
            y_coord[i].append(float(temp[1]))
            temp.clear()
f.close()
for i in range(len(x_coord)):
        rgb = (rd.random(), rd.random(), rd.random())
        plt.plot(x_coord[i],y_coord[i], c=rgb)
plt.xlabel('X Axis')
plt.xticks(np.arange(findMin(x_coord), findMax(x_coord), findMax(x_coord)/2))    #scale the axes properly
plt.ylabel('Y Axis')
plt.yticks(np.arange(findMin(y_coord), findMax(y_coord), findMax(y_coord)/10))
plt.title('Particle Paths')
plt.show()
f.close()