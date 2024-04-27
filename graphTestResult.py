import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import sys 

xLabels = []
testValues = []

def openFileAndConfigureData(xLabels_type = int, testValues_type = float):
    with open("testResults.txt", "r") as file:
        lines = file.readlines()
    for line in lines:
        parts = line.strip().split(": ")
        xLabels.append(xLabels_type(parts[0][4:]))
        testValues.append(testValues_type(parts[1]))
    num_data_points = len(testValues)
    x_values = np.linspace(xLabels[0], xLabels[-1], num=num_data_points)
    return x_values

def readDataSibc():
    x_values = openFileAndConfigureData()
    xlabel = "Test Number"
    return x_values, xlabel

def readDataSc():
    x_values = openFileAndConfigureData(xLabels_type = float)
    xlabel = "Time (h,m)"
    plt.xticks(x_values, ['{:.2f}'.format(val) for val in x_values])  
    return x_values, xlabel

plt.cla()
if "--sc" in sys.argv:
    x_values, xlabel = readDataSc()
elif "--sibc" in sys.argv:
    x_values, xlabel = readDataSibc()
plt.plot(x_values, testValues[:len(x_values)], color='#1f77b4', linewidth=2, marker='o', markersize=6, markerfacecolor='#ff7f0e', markeredgewidth=1, markeredgecolor='#ff7f0e')
plt.title('Test Results', fontsize=16, fontweight='bold')
plt.xlabel(xlabel, fontsize=14)
plt.ylabel('Voltage', fontsize=14)
plt.xticks(fontsize=12)
plt.yticks(fontsize=12)
plt.grid(True, linestyle='--', linewidth=0.5, alpha=0.7)

plt.tight_layout()
plt.show()
