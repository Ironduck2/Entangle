#ifndef QuantumGate_HH
#define QuantumGate_HH

#include "CondensedToNMatrix.hpp"
#include <vector>
#include <map>
#include <complex>
#include <iostream>
#include <utility>

class QuantumGate{
private:
    CMatrix<std::complex<double>> quantumGateMatrix;
public:
    QuantumGate(std::vector<std::vector<std::complex<double>>> gateMatrix) :
        quantumGateMatrix(gateMatrix) {}

    CMatrix<std::complex<double>> getQuantumGateMatrix() const {
        return quantumGateMatrix;
    }
};

#endif