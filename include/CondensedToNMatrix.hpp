#ifndef CondensedToNMatrix_HH
#define CondensedToNMatrix_HH

#include <vector>
#include <complex>
#include <iostream>

template <typename T>


//This class only works for square matrices
class CMatrix{
    private:
        T CondensedN;
        std::vector<T> condensedMatrix;
        std::vector<int> colIndexes;
        std::vector<int> rowPointer;

    public:
        CMatrix(int n) : CondensedN(n) {}

        CMatrix(const std::vector<std::vector<T>>& matrix, int n) : CondensedN(n) {matrixToCMatrix(matrix);}


        void matrixToCMatrix(const std::vector<std::vector<T>>& matrix) {
            rowPointer.push_back(0);
            for (const auto& row : matrix) {
                for (int j = 0; j < row.size(); ++j) {
                    if (row[j] != T(0)) {
                        condensedMatrix.push_back(row[j]);
                        colIndexes.push_back(j);
                    }
                }
                rowPointer.push_back(condensedMatrix.size());
            }
        }

        void IdentityTensoredWithMatrix (int n) {
            int originalItems = condensedMatrix.size(); 
            int originalDim = rowPointer.size() - 1;

            condensedMatrix.reserve(originalItems * n);
            colIndexes.reserve(originalItems * n);
            rowPointer.reserve(originalDim * n + 1);

            for (int j = 1; j < n; ++j) {
                for (int i = 0; i < originalItems; ++i) {
                    condensedMatrix.push_back(condensedMatrix[i]);
                    colIndexes.push_back(colIndexes[i] + originalDim * j); 
                }
    
                for (int i = 1; i <= originalDim; ++i) {
                    rowPointer.push_back(rowPointer[i] + originalItems * j); 
                }
            }
        }

        void printCMatrix() const {
            std::cout << "Condensed Matrix: ";
            for (const auto& val : condensedMatrix) {
                std::cout << val << " ";
            }
            std::cout << std::endl;

            std::cout << "Column Indexes: ";
            for (const auto& idx : colIndexes) {
                std::cout << idx << " ";
            }
            std::cout << std::endl;

            std::cout << "Row Pointer: ";
            for (const auto& ptr : rowPointer) {
                std::cout << ptr << " ";
            }
            std::cout << std::endl;
        }


};

#endif