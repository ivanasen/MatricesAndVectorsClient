# MatricesClient
Simple terminal client which uses MatricesAndVectors library. Made as a homework project for "Intro to Programming course at FMI". The client uses  [text](https://github.com/ivanasen/MatricesAndVectors)  library for matrix calculations.

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

Here is some example usage:

 ```python
 > Pesho = [3, 3]
Enter row 1: 23 23 1
Enter row 2: 1 0 345
Enter row 3: 34 2 9
23.00 23.00 1.00
1.00  0.00  345.00
34.00 2.00  9.00

> Gosho = [3]
Enter row 1: 2432 43 23
2432.00
43.00
23.00

> Transformed = Pesho * Gosho
56948.00
10367.00
82981.00

> (Pesho + Gosho) * 3 - 2
7367.00 69.00 3.00
132.00  2.00  1035.00
171.00  6.00  29.00

> Pesho.det
253715
> Gosho.normalise
1.00
0.02
0.01

> Kiro = [3]
Enter row 1: 24 2 435
24.00
2.00
435.00

> Gosho . Kiro
68459.00

> Pesho.inverse
-0.00 -0.00 0.03
0.05  0.00  -0.03
0.00  0.00  -0.00 
 ```