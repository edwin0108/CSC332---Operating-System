#!/bin/bash

# to display the graph
sudo apt install python-pip
sudo pip install numpy
sudo pip install matplotlib
sudo apt-get install python-tk

#remove AlgorithmData to prevent error
rm AlgorithmData.txt

# run all java files
javac *.java

# FIFO Scheduling
java CPU_Emulator 1

# Shortest Job Scheduling
java CPU_Emulator 2

# Priority Scheduling
java CPU_Emulator 3

# Round Robin FIFO: 10 units
java CPU_Emulator 4

# Round Robin FIFO: 100 units
java CPU_Emulator 5

# Round Robin FIFO: 1000 units
java CPU_Emulator 6

# Round Robin Shortest Job
java CPU_Emulator 7

# Round Robin Priority
java CPU_Emulator 8

#analysis graph
python ./graph.py