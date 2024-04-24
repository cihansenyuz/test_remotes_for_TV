import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

testNoLabels = []


def read_data():
    with open("testResults.txt", "r") as file:
        lines = file.readlines()
    testValues = []
    for line in lines:
        parts = line.strip().split(": ")
        testNoLabels.append(int(parts[0][4:]))
        testValues.append(float(parts[1]))
    return testValues

def update_graph(frame):
    testValues = read_data()
    num_data_points = len(testValues)
    x_values = np.linspace(testNoLabels[0], testNoLabels[-1], num=num_data_points)
    plt.cla()
    plt.plot(x_values, testValues[:len(x_values)], color='#1f77b4', linewidth=2, marker='o', markersize=6, markerfacecolor='#ff7f0e', markeredgewidth=1, markeredgecolor='#ff7f0e')
    plt.title('Test Results', fontsize=16, fontweight='bold')
    plt.xlabel('Test Number', fontsize=14)
    plt.ylabel('Voltage', fontsize=14)
    plt.xticks(fontsize=12)
    plt.yticks(fontsize=12)
    plt.grid(True, linestyle='--', linewidth=0.5, alpha=0.7)

plt.figure(figsize=(10, 6))

ani = animation.FuncAnimation(plt.gcf(), update_graph, frames=len(read_data()), interval=1000)  

plt.tight_layout()
plt.show()