#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

// Function to read a matrix from user input
vector<vector<int> > readMatrix(int rows, int cols) {
    vector<vector<int> > matrix(rows, vector<int>(cols, 0));
    string line;

    for (int i = 0; i < rows; ++i) {
        getline(cin, line);
        istringstream iss(line);

        for (int j = 0; j < cols; ++j) {
            int element;
            if (!(iss >> element)) {
                std::cerr << "Invalid input for matrix element\n";
                return vector<vector<int> >(0);
            }
            matrix[i][j] = element;
        }

        // Read and ignore the remaining newline character
        char c;
        if (iss.get(c) && c != '\n') {
            std::cerr << "Invalid format: Entered row has more than the required number of elements\n";
            return vector<vector<int> >(0);
        }

        // Consume any extra input after reading the expected number of elements
        string remaining;
        if (iss >> remaining) {
            std::cerr << "Invalid format: Entered row has more than the required number of elements\n";
            return vector<vector<int> >(0);
        }
    }

    return matrix;
}

// Function to print a matrix
void printMatrix(const vector<vector<int> > &matrix) {
    for (const auto &row: matrix) {
        for (int element: row) {
            std::cout << setw(5) << element << "\t"; // Adjust the width
        }
        std::cout << "\n";
    }
}

// TODO: Implement instead of Naive Algorithm a Coppersmith-Winograd Algorithm
vector<vector<int> > multiplyMatrices(const vector<vector<int> > &A, const vector<vector<int> > &B) {

    int m = static_cast<int>(A.size());
    int n = static_cast<int>(A[0].size());
    int p = static_cast<int>(B[0].size());

    vector<vector<int> > result(m, vector<int>(p, 0));
    cout << "\n";

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            int sum = 0;
            for (int k = 0; k < n - 3; k += 4) { // SMID - Single Instruction Multiple Data
                sum += A[i][k] * B[k][j];
                sum += A[i][k + 1] * B[k + 1][j];
                sum += A[i][k + 2] * B[k + 2][j];
                sum += A[i][k + 3] * B[k + 3][j];
            }
            for (int k = n - n % 4; k < n; ++k) {
                sum += A[i][k] * B[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

vector<vector<int> > addMatrix(const vector<vector<int> >& A, const vector<vector<int> >& B) {
    vector<vector<int> >::size_type n = A.size();
    vector<vector<int> > result(n, vector<int>(n, 0));
    for (vector<vector<int> >::size_type i = 0; i < n; i++) {
        for (vector<vector<int> >::size_type j = 0; j < n; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

vector<vector<int> > subtractMatrix(const vector<vector<int> >& A, const vector<vector<int> >& B) {
    vector<vector<int> >::size_type n = A.size();
    vector<vector<int> > result(n, vector<int>(n, 0));
    for (vector<vector<int> >::size_type i = 0; i < n; i++) {
        for (vector<vector<int> >::size_type j = 0; j < n; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Strassen's Algorithm for matrix multiplication
vector<vector<int> > strassenMultiply(const vector<vector<int> >& A, const vector<vector<int> >& B) {
    vector<vector<int> >::size_type n = A.size();

    // Base case: If the matrix size is 1x1, just multiply the elements.
    if (n == 1) {
        vector<vector<int> > C(1, vector<int>(1, 0));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Pad matrices to the nearest power of 2
    unsigned long newSize = 1;
    while (newSize < n) {
        newSize *= 2;
    }
    vector<vector<int> > A_padded(newSize, vector<int>(newSize, 0));
    vector<vector<int> > B_padded(newSize, vector<int>(newSize, 0));

    for (vector<vector<int> >::size_type i = 0; i < n; i++) {
        for (vector<vector<int> >::size_type j = 0; j < n; j++) {
            A_padded[i][j] = A[i][j];
            B_padded[i][j] = B[i][j];
        }
    }

    // Recursively compute sub-matrix products
    vector<vector<int> > A11(newSize / 2, vector<int>(newSize / 2, 0));
    vector<vector<int> > A12(newSize / 2, vector<int>(newSize / 2, 0));
    vector<vector<int> > A21(newSize / 2, vector<int>(newSize / 2, 0));
    vector<vector<int> > A22(newSize / 2, vector<int>(newSize / 2, 0));
    vector<vector<int> > B11(newSize / 2, vector<int>(newSize / 2, 0));
    vector<vector<int> > B12(newSize / 2, vector<int>(newSize / 2, 0));
    vector<vector<int> > B21(newSize / 2, vector<int>(newSize / 2, 0));
    vector<vector<int> > B22(newSize / 2, vector<int>(newSize / 2, 0));

    for (vector<vector<int> >::size_type i = 0; i < newSize / 2; i++) {
        for (vector<vector<int> >::size_type j = 0; j < newSize / 2; j++) {
            A11[i][j] = A_padded[i][j];
            A12[i][j] = A_padded[i][j + newSize / 2];
            A21[i][j] = A_padded[i + newSize / 2][j];
            A22[i][j] = A_padded[i + newSize / 2][j + newSize / 2];
            B11[i][j] = B_padded[i][j];
            B12[i][j] = B_padded[i][j + newSize / 2];
            B21[i][j] = B_padded[i + newSize / 2][j];
            B22[i][j] = B_padded[i + newSize / 2][j + newSize / 2];
        }
    }

    vector<vector<int> > P1 = strassenMultiply(A11, subtractMatrix(B12, B22));
    vector<vector<int> > P2 = strassenMultiply(addMatrix(A11, A12), B22);
    vector<vector<int> > P3 = strassenMultiply(addMatrix(A21, A22), B11);
    vector<vector<int> > P4 = strassenMultiply(A22, subtractMatrix(B21, B11));
    vector<vector<int> > P5 = strassenMultiply(addMatrix(A11, A22), addMatrix(B11, B22));
    vector<vector<int> > P6 = strassenMultiply(subtractMatrix(A12, A22), addMatrix(B21, B22));
    vector<vector<int> > P7 = strassenMultiply(subtractMatrix(A11, A21), addMatrix(B11, B12));

    // Calculate the result sub-matrices
    vector<vector<int> > C11 = addMatrix(subtractMatrix(addMatrix(P5, P4), P2), P6);
    vector<vector<int> > C12 = addMatrix(P1, P2);
    vector<vector<int> > C21 = addMatrix(P3, P4);
    vector<vector<int> > C22 = subtractMatrix(subtractMatrix(addMatrix(P5, P1), P3), P7);

    // Combine the result sub-matrices into the final result
    vector<vector<int> > C(newSize, vector<int>(newSize, 0));
    for (vector<vector<int> >::size_type i = 0; i < newSize / 2; i++) {
        for (vector<vector<int> >::size_type j = 0; j < newSize / 2; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize / 2] = C12[i][j];
            C[i + newSize / 2][j] = C21[i][j];
            C[i + newSize / 2][j + newSize / 2] = C22[i][j];
        }
    }

    // Remove padding to get the actual result
    vector<vector<int> > result(n, vector<int>(n, 0));
    for (vector<vector<int> >::size_type i = 0; i < n; i++) {
        for (vector<vector<int> >::size_type j = 0; j < n; j++) {
            result[i][j] = C[i][j];
        }
    }

    return result;
}

// Function to display help information
void displayHelp() {
    std::cout << "Matrix Multiplication Program\n";
    std::cout << "This program performs matrix multiplication of two matrices using different algorithms.\n";
    std::cout << "Usage: ./matrix_mult [options]\n";
    std::cout << "Options:\n";
    std::cout << "  --help    Display this help message\n";
    std::cout << "  --naive Use Naive Algorithm for multiplication (default)\n";
    std::cout << "  --strassen Use Strassen's Algorithm for multiplication\n";
    std::cout << "Description:\n";
    std::cout
            << "After running the matrix_mult program, you will see the following interactive process in the terminal: \n";
    std::cout
            << "    - The program will prompt you to enter the dimensions of square matrices A and B.\n";
    std::cout
            << "    - After entering the dimensions of matrices A and B, "
               "the program will prompt you to enter the elements of both matrices in turn.\n";
    std::cout
            << "    - The program will display the actions of multiplication of numbers by each other"
               " and the matrix obtained after multiplication.\n";
    std::cout << "    - The program will then exit.\n";
}

// Main function to run the program
int main(int argc, char *argv[]) {

    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0) {
            displayHelp();
            return 0;
        }
    }

    string algorithm = "naive"; // Default algorithm is a Naive Algorithm

    if (argc > 2) {
        if (strcmp(argv[2], "--strassen") == 0) {
            algorithm = "strassen";
        }
    }

    int numRowsA, numColsA, numRowsB, numColsB;

    // Read number of rows and columns for matrix A
    std::cout << "Enter number of rows for matrix A: ";
    string numRowsInputA;
    getline(std::cin, numRowsInputA);
    try {
        size_t pos;
        numRowsA = stoi(numRowsInputA, &pos);
        if (pos != numRowsInputA.size() || numRowsInputA[0] == '0') {
            std::cerr << "Invalid input for number of rows for matrix A\n";
            return 1;
        }
        if (numRowsA <= 0) {
            std::cerr << "Invalid number of rows for matrix A\n";
            return 1;
        }
    } catch (const invalid_argument &e) {
        std::cerr << "Invalid input for number of rows for matrix A\n";
        return 1;
    }

    std::cout << "Enter number of columns for matrix A: ";
    string numColsInputA;
    getline(std::cin, numColsInputA);
    try {
        size_t pos;
        numColsA = stoi(numColsInputA, &pos);
        if (pos != numColsInputA.size() || numColsInputA[0] == '0') {
            std::cerr << "Invalid input for number of columns for matrix A\n";
            return 1;
        }
        if (numColsA <= 0) {
            std::cerr << "Invalid number of columns for matrix A\n";
            return 1;
        }
    } catch (const invalid_argument &e) {
        std::cerr << "Invalid input for number of columns for matrix A\n";
        return 1;
    }

    // Read number of rows and columns for matrix B
    std::cout << "\nEnter number of rows for matrix B: ";
    string numRowsInputB;
    getline(std::cin, numRowsInputB);
    try {
        size_t pos;
        numRowsB = stoi(numRowsInputB, &pos);
        if (pos != numRowsInputB.size() || numRowsInputB[0] == '0') {
            std::cerr << "Invalid input for number of rows for matrix B\n";
            return 1;
        }
        if (numRowsB <= 0) {
            std::cerr << "Invalid number of rows for matrix B\n";
            return 1;
        }
    } catch (const invalid_argument &e) {
        std::cerr << "Invalid input for number of rows for matrix B\n";
        return 1;
    }

    std::cout << "Enter number of columns for matrix B: ";
    string numColsInputB;
    getline(std::cin, numColsInputB);
    try {
        size_t pos;
        numColsB = stoi(numColsInputB, &pos);
        if (pos != numColsInputB.size() || numColsInputB[0] == '0') {
            std::cerr << "Invalid input for number of columns for matrix B\n";
            return 1;
        }
        if (numColsB <= 0) {
            std::cerr << "Invalid number of columns for matrix B\n";
            return 1;
        }
    } catch (const invalid_argument &e) {
        std::cerr << "Invalid input for number of columns for matrix B\n";
        return 1;
    }
    if (numColsA != numRowsB) {
        std::cerr << "Invalid matrix dimensions: Number of columns in matrix A must match number of rows in matrix B\n";
        return 1;
    }

    vector<vector<int> > matrixA, matrixB;

    std::cout << "\nEnter matrix A (" << numRowsA << "x" << numColsA << "):\n";
    try {
        matrixA = readMatrix(numRowsA, numColsA);
        if (matrixA.empty()) {
            return 1; // Error encountered in matrix A input
        }
    } catch (const invalid_argument &e) {
        std::cerr << "Invalid input for matrix A: " << e.what() << "\n";
        return 1;
    }

    std::cout << "\nEnter matrix B (" << numRowsB << "x" << numColsB << "):\n";
    try {
        matrixB = readMatrix(numRowsB, numColsB);
        if (matrixB.empty()) {
            return 1; // Error encountered in matrix B input
        }
    } catch (const invalid_argument &e) {
        std::cerr << "Invalid input for matrix B: " << e.what() << "\n";
        return 1;
    }

    vector<vector<int> > result;

    if (algorithm == "naive") {
        result = multiplyMatrices(matrixA, matrixB);
    } else if (algorithm == "strassen") {
        result = strassenMultiply(matrixA, matrixB);
    } else {
        std::cerr << "Invalid algorithm selection\n";
        return 1;
    }

    std::cout << "\nResult:\n";
    printMatrix(result);

    return 0;
}
