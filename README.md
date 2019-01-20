# MatricesClient
Simple terminal client which uses MatricesAndVectors library. Made as a homework project for "Intro to Programming course at FMI".

## Prerequisites
 - CMake: version 3.13 or higher
 
## Building the project

Run these commands while in the project directory:

 ```bash
 cmake .
 make
 ```

After that a **MatricesAndVectorsClient** executable should be available in the project root.

## Usage

The way of declaring an N by M matrix with is the following:

 ```python
 <matrix-name> = [N, M]
 Enter row 1: el(1,1) el(1,2) ... el(1, M)
 Enter row 2: el(2,1) el(2,2) ... el(2, M)
 ............
 Enter row N: el(N,1) el(N,2) ... el(N, M)
 ```

Declaring a Vector of N elements:

 ```python
 <vector-name> = [N]
 Enter row 1: el(1,1) el(1,2) ... el(1, N)
 ```

Declaring a Scalar with a value of n:

 ```python
 <scalar-name> = n
 ```

Here is an example usage of the program:

 ```python
 
 ```