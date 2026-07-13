#ifndef QuantumGate_HH
#define QuantumGate_HH

#include <vector>
#include <complex>
#include <iostream>

using namespace std;

class QuantumGate{
private:
    vector<vector<complex<double>>> quantumGateMatrix;

public:
    QuantumGate(vector<vector<complex<double>>> gateMatrix) :
        quantumGateMatrix(gateMatrix) {}

    vector<vector<complex<double>>> getQuantumGateMatrix() const {
        return quantumGateMatrix;
    }

    void printQuantumGateMatrix() const {
        cout << "Quantum Gate Matrix:" << endl;
        cout << "Rows: " << quantumGateMatrix.size() << ", Columns: " << quantumGateMatrix[0].size() << endl;
        for (const auto& row : quantumGateMatrix) {
            for (const auto& element : row) {
                cout << element << " ";
            }
            cout << endl;
        }
    }
};

#endif