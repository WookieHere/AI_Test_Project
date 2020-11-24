import matplotlib.pyplot as plt
import re
temp = []
x_coord = [0]
y_coord = [0]
with open("test.txt", "r") as f:
    for line in f:
        for p in re.split('[, \n]', line):
            temp.append(p)
        x_coord.append(temp[0])
        y_coord.append(temp[1])
        temp.clear()

plt.plot(x_coord,y_coord)
plt.xlabel('X Axis')
plt.ylabel('Y Axis')
plt.title('Best Particle Path of Generation')
plt.show()
f.close()