# Project 4, Studies of Phase Transitions in Magnetic Systems
[Project assignment file](https://github.com/CompPhysics/ComputationalPhysics/blob/master/doc/Projects/2019/Project4/pdf/Project4.pdf)


## Description

This repository contains the work of project 4 - The Icing Model - of the course computational 
physics, FYS3150. The project evaluates the use of a Monte Carlo Metropolis procedure to simulate the Ising Model. 


## Structure

All associated scripts are found in the _Scripts_ folder, and the entire project is run through _main.cpp_. The _Paper_ folder contains the PDF of the finished project paper. The _Py_Scripts_ folder contains all python based scripts for reading and plotting of the data. 

## Setup & Running 

The program is developed using [QT creator](https://www.qt.io/download) for project management and construction.

The program takes three input text files called _N.txt_, _L.txt_ and _T.txt_ containing respectively the number of Monte Carlo Cycles, the grid lattice size and the temperature to run the simulation at. The class for reading files _ReadFiles.cpp_ reads all files, presented as in the example below.  

##### Example of _N.txt_ file:
```diff
100
1000
10000
```
The write file class writes the results to two types new text files.
