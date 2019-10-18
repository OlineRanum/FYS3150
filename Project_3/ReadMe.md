# Project 3, Numerical Integration

[Project assignment file](https://github.com/CompPhysics/ComputationalPhysics/blob/master/doc/Projects/2019/Project3/pdf/Project3.pdf)


## Description

This repository contains the work of project 3 - numerical integration - of the course computational 
physics, FYS3150. The project considers two approaches to numerical integration employed to estimate the expectation value of the ground state correlation energy between two electrons a helium atom. The methods of choice are the Gauss Legendre and Gauss Laguerre quadrature and Monte  Carlo integration. 


## Structure
The program is structured in the usual way with main script and class extensions indicated by name.  The Gauss-Legendre and Gauss-Laguerre instances, respectively _GLEG_ and _GLAG_, calls the initialization of both procedure. The Monte Carlo _mc_ instance must be initiated with a mode parameter, i.e. the 7th argument of the function call, following

| __MODE__  | __INITIATOR__  |   
|---|---|
| Brute Force MC  |  0 |
| Importance Sampling MC|  1 |
| Parallellized Importance Sampling MC |  2 |

The classes for reading files _ReadFiles.cpp_, reads solely a file _N.txt_ containing all the values 

### Example of _N.txt_ file:
```diff
- text in red
+ text in green
! text in orange
# text in gray
```


## Setup & Running 

The program is developed using [QT creator](https://www.qt.io/download) for project management and construction.

After compiling the program 
