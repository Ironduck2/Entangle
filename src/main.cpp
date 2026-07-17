#include "QuantumComputer.hpp"
#include "QuantumGate.hpp"
#include <iostream>

using namespace std;

int main() {
    QuantumComputer myQbits(4);
    CMatrix<std::complex<double>> QGateX({{0, 1}, {1, 0}}, 0);
    CMatrix<std::complex<double>> QGateY({{0, -1i}, {1i, 0}}, 0);
    CMatrix<std::complex<double>> QGateZ({{1, 0}, {0, -1}}, 0);
    CMatrix<std::complex<double>> QGateH({{1/sqrt(2), 1/sqrt(2)}, {1/sqrt(2), -1/sqrt(2)}}, 0);
    
    
    myQbits.applyGate(QGateH, 0);
    // myQbits.applyGateQueue();
    myQbits.printQbits();

    return 0;
}