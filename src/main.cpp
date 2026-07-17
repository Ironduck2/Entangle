#include "QuantumComputer.hpp"
#include "QuantumGate.hpp"
#include <iostream>

using namespace std;

int main() {
    QuantumComputer myQbits(2);
    CMatrix<std::complex<double>> QGateX1({{0, 1}, {1, 0}}, 0);
    CMatrix<std::complex<double>> QGateX2({{0, 1}, {1, 0}}, 0);
    // QuantumGate QGateY({{0, -1i}, {1i, 0}});
    // QuantumGate QGateZ({{1, 0}, {0, -1}});
    CMatrix<std::complex<double>> QGateH({{1/sqrt(2), 1/sqrt(2)}, {1/sqrt(2), -1/sqrt(2)}}, 0);
    // QuantumGate I4x4({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
    //cout << "Number of qbits: " << myQbits.getAmountQbits() << endl;
    //cout << "Size of qbits list: " << myQbits.getListSize() << endl;
    
    QGateX1.IdentityTensoredWithMatrix(2);
    QGateX2.MatrixTensoredWithIdentity(2);
    
    myQbits.applyGate(QGateX1, 0);
    myQbits.applyGate(QGateX2, 0);
    // myQbits.applyGateQueue();
    myQbits.printQbits();

    return 0;
}