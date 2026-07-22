#ifndef ArrayMatrix_HH
#define ArrayMatrix_HH

#include <vector>
#include <complex>
#include <iostream>
#include <utility>
#include <algorithm>

template <typename T>
class AMatrix {
private:
    std::vector<T> arrayMatrix;
    int columns;

public:
    explicit AMatrix(int cols = 0) : columns(cols), arrayMatrix(cols * cols, T(0)) {}

    AMatrix(const std::vector<T>& matrix, int cols) : arrayMatrix(matrix), columns(cols) {}

    explicit AMatrix(const std::vector<std::vector<T>>& matrix) {
        matrixToCMatrix(matrix);
    }

    void matrixToCMatrix(const std::vector<std::vector<T>>& matrix) {
        columns = static_cast<int>(matrix.size());
        arrayMatrix.assign(columns * columns, T(0));

        for (int i = 0; i < columns; ++i) {
            for (int j = 0; j < columns; ++j) {
                arrayMatrix[i * columns + j] = matrix[i][j];
            }
        }
    }

    void matrixToCMatrix(const std::vector<T>& matrix, int cols) {
        columns = cols;
        arrayMatrix = matrix;
    }

    void IdentityTensoredWithMatrix(int n) {
        if (n <= 1) return;

        int origCols = columns;
        int newCols = origCols * n;
        std::vector<T> newCondensed(newCols * newCols, T(0));

        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < origCols; ++i) {
                auto srcStart = arrayMatrix.begin() + i * origCols;
                auto destStart = newCondensed.begin() + (k * origCols + i) * newCols + (k * origCols);
                
                std::copy_n(srcStart, origCols, destStart);
            }
        }

        columns = newCols;
        arrayMatrix = std::move(newCondensed);
    }

    void MatrixTensoredWithIdentity(int n) {
        if (n <= 1) return;

        int origCols = columns;
        int newCols = origCols * n;
        std::vector<T> newCondensed(newCols * newCols, T(0));

        int diagStep = newCols + 1;

        for (int i = 0; i < origCols; ++i) {
            int rowBaseOffset = i * n * newCols;
            
            for (int j = 0; j < origCols; ++j) {
                T val = arrayMatrix[i * origCols + j];
                
                if (val == T(0)) continue; 
                
                int blockStartIndex = rowBaseOffset + (j * n);
                
                for (int k = 0; k < n; ++k) {
                    newCondensed[blockStartIndex] = val;
                    blockStartIndex += diagStep;
                }
            }
        }

        columns = newCols;
        arrayMatrix = std::move(newCondensed);
    }

    void MultiplyMatrixVector(const std::vector<T>& vec, std::vector<T>& result) const {
        result.assign(columns, T(0));
        for (int i = 0; i < columns; ++i) {
            for (int j = 0; j < columns; ++j) {
                result[i] += arrayMatrix[i * columns + j] * vec[j];
            }
        }
    }

    int getColumns() const { return columns; }
    const std::vector<T>& getArrayMatrix() const { return arrayMatrix; }

    void printCMatrix() const {
        std::cout << "Matrix (" << columns << "x" << columns << "):\n";
        for (int i = 0; i < columns; ++i) {
            for (int j = 0; j < columns; ++j) {
                std::cout << arrayMatrix[i * columns + j] << " ";
            }
            std::cout << "\n";
        }
    }
};

#endif