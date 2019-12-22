# Project 5, Modeling the Solar System using ordinary differential equations
[Project assignment file](https://github.com/CompPhysics/ComputationalPhysics/blob/master/doc/Projects/2019/Project5/SolarSystem/pdf/SolarSystem.pdf)

![Image](https://github.com/OlineRanum/FYS3150/blob/master/Project_5/Paper/Figures/betta2.png)


## Description

This repository contains the work of project 5 - Building a model for the solar system using ordinary differential equations - of the course computational physics, FYS3150. The project evaluates the forward Euler and velocity Verlet algorithms to solve the Newtonian ordinary differential equations, and make a simple simulation of the Solar System. 


## Structure

All associated scripts are found in the _Scripts_ folder, and the entire project is run through _main.cpp_. The _Paper_ folder contains the PDF of the finished project paper. The _Results_ folder contains all python based scripts for reading and plotting of the results. 

## Setup & Running 

The program is developed using [QT creator](https://www.qt.io/download) for project management and construction.

The program takes three input text files called _Names.txt_, _InitialConditions.txt_ and _Mass.txt_ containing respectively a list of planet names, the Initial conditions for each planed (three intitial positions + three initial velocities) and the final file contains a list of the mass of each planet relative to the solar mass. The class for reading files _ReadFiles.cpp_ reads all files, presented as in the example below.  

##### Example of _Names.txt_ file:
```diff
Sun
Earth
Jupiter
```
##### Example of _Initial Conditions.txt_ file:
```diff
-3.445794798894677E-03 7.514129097010522E-03 1.331363550190799E-05 -8.442031504341172E-06 -1.537062205934645E-06 2.314790690956382E-07
5.335858905497771E-01 8.370731944610594E-01 -2.812649127895525E-05 -1.472817722343729E-02 9.288879282185889E-03 -5.766212639367660E-07
2.101106711987771E-01 -5.230907987162060E+00 1.699342433382969E-02 7.447883568716252E-03 6.628387409912372E-04 -1.693570419889271E-04
```

##### Example of _Mass.txt_ file:
```diff
1
3E-6
0.00095
``


The write file class writes the results to two types new text files.

