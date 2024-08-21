# This program was created as a semester project of the PCC

## Multiplication of matrices

## (CTU - SIT winter semester 2023)

### Author: Dmitry Rastvorov

-- -- 

### Contents

#### 1. [Task](#task)

#### 2. [Description](#description)

#### 3. [Implementation](#implementation)

#### 4. [Running project](#running)

#### 5. [Testing](#testing)

#### 6. [Measurements](#measurements)

-- --

### Task <a name="task"></a>

The program represents a calculator for matrix multiplication with used 2 algorithms: Strassen's Algorithm and Coppersmith Winograd Algorithm.
-- --

### Description <a name="description"></a>

Matrix multiplication is one of the most interesting topics in linear algebra.
In this program, we can set the number of rows and columns for each matrix,
specify the numbers and get the answer with a description of the operations performed on the result.
The matrix implementation was inspired by the presentations of the course B6B01LAG Doc.RNDr.
Jiří Velebil,
Ph.D. ([Algebra of matrices](https://math.fel.cvut.cz/en/people/velebil/files/b6b01lag/lag_handout04b.pdf))
and also by Abdul Bari's video ([Strassen's Matrix Multiplication](https://www.youtube.com/watch?v=0oJyNmEbS4w))
-- --

### Implementation <a name="implementation"></a>

##### Program functionality:

- The program asks the user for the dimensions of matrices A and B (number of rows and columns).
- After entering the dimensions, the program asks for the elements of matrices A and B one by one.
- The matrices A and B are multiplied, and the result is displayed on the screen.

##### Multiple Threads:

The code does not use multiple threads explicitly. It performs matrix multiplication using a loop structure, but there
is no use of multithreading or parallelism. The multiplication is done using single-threaded calculations.

##### Single Thread Optimized Implementation:

The code includes implementations of several matrix multiplication algorithms,
including the Coppersmith–Winograd algorithm and Strassen's Algorithm.
The program allows the user to choose between these algorithms and input two matrices for multiplication.

##### Language Extensions:

The code does not use any explicit language extensions like OpenMP or variable length arrays (VLA). 
It uses standard C++ functions and libraries.

##### Non-portable Libraries:

The code does not use non-portable libraries such as POSIX or Win32.
It relies on standard C++ libraries for input/output and vector operations.

### Running project <a name="running"></a>

If you are using CLion, you can run the program by opening the project ``matrix_mult.cpp`` and clicking the **Run**
button.

Or you can run the program in the terminal by following these steps:

1) To get the executable file, you need to write this command in the terminal:

```shell 
g++ -o matrix_mult  matrix_mult.cpp  
```

To get the executable file with optimization, you need to write this command in the terminal:

```shell
g++ -O3 -o matrix_mult  matrix_mult.cpp
```

2) To run the program, you need to write this command in the terminal:

```shell
./matrix_mult
```

#### Help:

If you want to get help, you need to write this command:

```shell
./matrix_mult --help
```

And you will see this description:

``` 
Matrix Multiplication Program
This program performs matrix multiplication of two matrices using different algorithms.
Usage: ./matrix_mult [options]
Options:
  --help    Display this help message
  --copsmth Use Coppersmith Winograd Algorithm for multiplication (default)
  --strassen Use Strassen's Algorithm for multiplication
Description:
After running the matrix_mult program, you will see the following interactive process in the terminal: 
    - The program will prompt you to enter the dimensions of square matrices A and B.
    - After entering the dimensions of matrices A and B, the program will prompt you to enter the elements of both matrices in turn.
    - The program will display the result of the multiplication.
    - The program will then exit.
```

If you try calling another option that does not exist, you will get an invalid message:
``Unknown command: [your written switch]``

#### Scenario

After running the program, you will see the following interactive process in the terminal:

1) The program will prompt you to enter the dimensions of square matrices A and B.
2) After entering the dimensions of matrices A and B, the program will prompt you to enter the elements of both matrices
   in turn.
3) The program will display the result of the multiplication.
4) The program will then exit.

#### Example:

```
Enter number of rows for matrix A: 2
Enter number of columns for matrix A: 2

Enter number of rows for matrix B: 2
Enter number of columns for matrix B: 2

Enter matrix A (2x2):
1 2
3 4

Enter matrix B (2x2):
5 6
7 8

Result:
   19	   22	
   43	   50
```

#### Errors:

The program also contains error handling. If you enter the wrong data, you will see the following error messages:

##### Example 1:

```
Enter number of rows for matrix A: cpp
Invalid input for number of rows for matrix A
```

##### Example 2:

```
Enter number of rows for matrix A: 2
Enter number of columns for matrix A: pcc
Invalid input for number of columns for matrix A
```

##### Example 3:

```
Enter number of rows for matrix A: -1
Invalid number of rows for matrix A
```

##### Example 4:

```
Enter number of rows for matrix A: 1
Enter number of columns for matrix A: 2

Enter number of rows for matrix B: 1
Enter number of columns for matrix B: 1
Invalid matrix dimensions: Number of columns in matrix A must match number of rows in matrix B
```

##### Example 5:

```
Enter number of rows for matrix A: 2
Enter number of columns for matrix A: 2

Enter number of rows for matrix B: 2
Enter number of columns for matrix B: 2

Enter matrix A (2x2):
1 2 3
Invalid format: Entered row has more than the required number of elements
```

##### Example 6:

```
Enter number of rows for matrix A: 2
Enter number of columns for matrix A: 2

Enter number of rows for matrix B: 2
Enter number of columns for matrix B: 2

Enter matrix A (2x2):
1
Invalid input for matrix element
```

-- --

### Testing <a name="testing"></a>

The project contains [testing folder](https://github.com/UnknownPug/matrix-algorithms/tree/main/testing) where you can
find different matrices and their multiplication results.
-- --

### Measurements <a name="measurements"></a>

Measurements were performed on an 8-core Apple M1 3.2GHz CPU.

To measure the code rate time, the following was used:

1) ``chrono`` library:

```c++
template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}
 
 
int main() {
    auto start = std::chrono::high_resolution_clock::now();
    // do work
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
}
```

2) [Testing folder](https://github.com/UnknownPug/matrix-algorithms/tree/main/testing) with different matrices.

##### To demonstrate the result, I attach a table with files, matrix sizes, and algorithms (data are specified in milliseconds).

| File          | Type      | Coppersmith Winograd Algorithm | Strassen's Algorithm                     |
|---------------|-----------|--------------------------------|------------------------------------------|
| testing_1.txt | 2x2       | 0.0 ms                         | 0.0 ms                                   |
| testing_2.txt | 3x3       | 0.0 ms                         | 0.0 ms                                   |
| testing_3.txt | 4x4       | 0.0 ms                         | 0.0 ms                                   |
| testing_4.txt | 5x5       | 0.0 ms                         | ~1 ms                                    |
| testing_5.txt | different | 0.0 ms                         | designed for multiplying square matrices |
| testing_6.txt | 10x10     | ~4 ms                          | ~10 ms                                   |
| testing_7.txt | 12x12     | ~6 ms                          | ~12 ms                                   |
| testing_8.txt | 15x15     | ~11 ms                         | ~10 ms                                   |
| testing_9.txt | 20x20     | ~20 ms                         | ~72 ms                                   |
