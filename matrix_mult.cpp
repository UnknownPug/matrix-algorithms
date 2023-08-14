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

            // Add a comment to explain how the element is calculated
            cout << "c" << (i + 1) << (j + 1) << " = ";
            for (int k = 0; k < n; ++k) {
                cout << A[i][k] << " * " << B[k][j];
                if (k < n - 1) {
                    cout << " + ";
                }
            }
            cout << " = " << result[i][j] << "\n";
        }
    }

    return result;
}

// Function to display help information
void displayHelp() {
    std::cout << "Matrix Multiplication Program\n";
    std::cout << "This program performs matrix multiplication of two square matrices.\n";
    std::cout << "Usage: ./matrix_mult [options]\n";
    std::cout << "Options:\n";
    std::cout << "  --help    Display this help message\n";
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
        } else {
            std::cerr << "Unknown switch: " << argv[1] << "\n";
            return 1;
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
            cerr << "Invalid input for number of rows for matrix A\n";
            return 1;
        }
        if (numRowsA <= 0) {
            cerr << "Invalid number of rows for matrix A\n";
            return 1;
        }
    } catch (const invalid_argument &e) {
        cerr << "Invalid input for number of rows for matrix A\n";
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
    getline(cin, numColsInputB);
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

    vector<vector<int> > result = multiplyMatrices(matrixA, matrixB);

    std::cout << "\nResult:\n";
    printMatrix(result);

    return 0;
}
