# Project 3, Numerical Integration

[Project assignment file](https://github.com/CompPhysics/ComputationalPhysics/blob/master/doc/Projects/2019/Project3/pdf/Project3.pdf)


## Description

This repository contains the work of project 3 - numerical integration - of the course computational 
physics, FYS3150. The project considers two approaches to numerical integration employed to estimate the expectation value of the ground state correlation energy between two electrons a helium atom. The methods of choice are the Gauss Legendre and Gauss Laguerre quadrature and Monte  Carlo integration. 


## Structure
The program is structured in the usual way with main script and class extensions indicated by name.  The Gauss-Legendre and Gauss-Laguerre instances, respectively _GLEG_ and _GLAG_, calls the initialization of both procedure. The Monte Carlo _mc_ instance must be initiated with a mode parameter, I.e. the 7th argument of the function call, following

| __MODE__  | __INITIATOR__  |   
|---|---|
| Brute Force MC  |  0 |
| Importance Sampling MC|  1 |
| Parallellized Importance Sampling MC |  2 |

The classes for reading files _ReadFiles.cpp_, reads solely a file _N.txt_ containing all preferred values of N, presented as in the example below.  

##### Example of _N.txt_ file:
```diff
100
1000
10000
```
The write file class writes the results to two types of text files, one primer suitable for reading by humans and a secondary file denoted with numpy suitable for numpy translations. 

## Setup & Running 

The program is developed using [QT creator](https://www.qt.io/download) for project management and construction.
After compiling the program, all instances can be run directly in qt except mode 2 of the Monte Carlo estimations. 
For running the parallelized Monte Carlo integration please compile program and run with
```diff
mpirun -n 4 ./Project_3
```
for running on 4 processors simultaneously. The number of processors is of course interchangeable. 
