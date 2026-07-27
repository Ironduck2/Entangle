#ifndef CondensedToNMatrix_HH
#define CondensedToNMatrix_HH

#include <vector>
#include <complex>
#include <iostream>

template <typename T>


//This class only works for square matrices
class CMatrix{
    private:
        std::vector<T> condensedMatrix;
        std::vector<int32_t> colIndexes;
        std::vector<int32_t> rowPointer;

    public:
        CMatrix(const std::vector<std::vector<T>>& matrix) {matrixToCMatrix(matrix);}


        void matrixToCMatrix(const std::vector<std::vector<T>>& matrix) {
            condensedMatrix.clear();
            colIndexes.clear();
            rowPointer.clear();
            
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

        void MatrixTensoredWithIdentity (int n) {
            int originalDim = rowPointer.size() - 1;
            int newDim = originalDim * n;

            std::vector<T> newCondensed;
            std::vector<int> newColIndexes;
            std::vector<int> newRowPointer;

            newCondensed.reserve(condensedMatrix.size() * n);
            newColIndexes.reserve(colIndexes.size() * n);
            newRowPointer.reserve(newDim + 1);

            newRowPointer.push_back(0);

            for (int i = 0; i < originalDim; ++i) {
                for (int k = 0; k < n; ++k) {
                    
                    for (int j = rowPointer[i]; j < rowPointer[i + 1]; ++j) {
                        newCondensed.push_back(condensedMatrix[j]);
                        
                        newColIndexes.push_back(colIndexes[j] * n + k);
                    }
                    
                    newRowPointer.push_back(newCondensed.size());
                }
            }

            condensedMatrix = std::move(newCondensed);
            colIndexes = std::move(newColIndexes);
            rowPointer = std::move(newRowPointer);
        }

        void MultiplyMatrixVector(std::vector<T>& vec, std::vector<T>& result) const {
            int dim = rowPointer.size() - 1;
            result.assign(dim, T(0));

            for (int i = 0; i < dim; ++i) {
                for (int j = rowPointer[i]; j < rowPointer[i + 1]; ++j) {
                    result[i] += condensedMatrix[j] * vec[colIndexes[j]];
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