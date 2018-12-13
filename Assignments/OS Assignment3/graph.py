import numpy as np
import matplotlib.pyplot as plt
 
plt.figure(figsize=(10, 4))
plt.title('Analysis - Average wait time')
plt.xlabel('Algorithm')
plt.ylabel('Time')

# Make a testing dataset:
height = []
with open('AlgorithmData.txt', 'rt') as infile:
    lines = infile.read().split(',')
for i in range(0, len(lines) - 1):
    height.append(int(lines[i]))
print(height)
bars = ('FIFO', 'SJN', 'PRIORITY', 'RR-10', 'RR-100', 'RR-1000', 'RR(SRTN)', 'RR(Priority)')
y_pos = range(len(bars))
 
# Create bars
plt.bar(y_pos, height)
 
# Create names on the x-axis
plt.xticks(y_pos, bars)
 
# Show graphic
plt.show()
