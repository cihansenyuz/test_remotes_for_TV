import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import sys 

xLabels = []

def read_data():
    global xlabel
    with open("testResults.txt", "r") as file:
        lines = file.readlines()
    testValues = []
    for line in lines:
        parts = line.strip().split(": ")
        if "--sc" in sys.argv:
            xLabels.append(float(parts[0][4:]))
            testValues.append(float(parts[1]))
            xlabel = "Time (h,m)"
        elif "--sibc" in sys.argv:
            xLabels.append(int(parts[0][4:]))
            testValues.append(float(parts[1]))
            xlabel = "Test Number"
    return testValues

#def update_graph(frame):
testValues = read_data()
num_data_points = len(testValues)
x_values = np.linspace(xLabels[0], xLabels[-1], num=num_data_points)
plt.cla()
plt.plot(x_values, testValues[:len(x_values)], color='#1f77b4', linewidth=2, marker='o', markersize=6, markerfacecolor='#ff7f0e', markeredgewidth=1, markeredgecolor='#ff7f0e')
plt.title('Test Results', fontsize=16, fontweight='bold')
if "--sc" in sys.argv:
    plt.xticks(x_values, ['{:.2f}'.format(val) for val in x_values])  
plt.xlabel(xlabel, fontsize=14)
plt.ylabel('Voltage', fontsize=14)
plt.xticks(fontsize=12)
plt.yticks(fontsize=12)
plt.grid(True, linestyle='--', linewidth=0.5, alpha=0.7)

#plt.figure(figsize=(10, 6))

#ani = animation.FuncAnimation(plt.gcf(), update_graph, frames=len(read_data()), interval=1000)  

plt.tight_layout()
plt.show()