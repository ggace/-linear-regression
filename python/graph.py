import matplotlib.pyplot as plt

f = open("../files/values.txt", "r")

xs_value = []
ys_value = []

min_value = None
max_value = None

for x in f.read().split("\n"):
    if(min_value is None):
        min_value = [int(x.split(": ")[0]), int(x.split(": ")[1])]
    elif(min_value[0] > int(x.split(": ")[0])):
        min_value = [int(x.split(": ")[0]), int(x.split(": ")[1])]
    if(max_value is None):
        max_value = [int(x.split(": ")[0]), int(x.split(": ")[1])]
    elif(max_value[0] < int(x.split(": ")[0])):
        max_value = [int(x.split(": ")[0]), int(x.split(": ")[1])]
    
    xs_value.append(int(x.split(": ")[0]))
    ys_value.append(int(x.split(": ")[1]))
plt.scatter(xs_value, ys_value)
f.close()

xs = []
ys = []

f = open("../files/result.txt", "r")

current_w = 1
current_b = 0

for x in f.read().split("\n")[:-1]:
    if(float(x.split(": ")[0]) != current_w or current_b != float(x.split(": ")[1])):
        xs = []
        ys = []
        for i in range(min_value[0], max_value[0] + 1):
            xs.append(i)
            ys.append(float(x.split(": ")[0]) * i + float(x.split(": ")[1]))
            
        plt.plot(xs, ys)
        plt.scatter(xs_value, ys_value)  
        plt.pause(0.000001)
        current_w = float(x.split(": ")[0])
        current_b = float(x.split(": ")[1])
    
    
    
    


plt.show()