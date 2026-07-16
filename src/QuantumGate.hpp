#ifndef QuantumGate_HH
#define QuantumGate_HH

#include <vector>
#include <complex>
#include <iostream>

using namespace std;

class QuantumGate{
private:
    vector<vector<complex<double>>> quantumGateMatrix;
    //añadir cosa que dice los bits a los que se aplica 

public:
    QuantumGate(vector<vector<complex<double>>> gateMatrix) :
        quantumGateMatrix(gateMatrix) {}

    vector<vector<complex<double>>> getQuantumGateMatrix() const {
        return quantumGateMatrix;
    }

    void printQuantumGateMatrix() const {
        cout << "Quantum Gate Matrix:" << endl;
        cout << "Rows: " << quantumGateMatrix.size() << ", Columns: " << quantumGateMatrix[0].size() << endl;
        for (int i = 0; i < quantumGateMatrix.size(); ++i) {
            for (int j = 0; j < quantumGateMatrix[i].size(); ++j) {
                cout << quantumGateMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

#endif