#include "QuantumComputer.hh"
#include "QuantumGate.hh"
#include <iostream>

using namespace std;

int main() {
    QuantumComputer myQbits(1);
    QuantumGate QGateX({{0, 1}, {1, 0}});
    QuantumGate QGateY({{0, -1i}, {1i, 0}});
    QuantumGate QGateZ({{1, 0}, {0, -1}});
    QuantumGate QGateH({{1/sqrt(2), 1/sqrt(2)}, {1/sqrt(2), -1/sqrt(2)}});
    cout << "Number of qbits: " << myQbits.getAmountQbits() << endl;
    cout << "Size of qbits list: " << myQbits.getListSize() << endl;
    
    //QGateX.printQuantumGateMatrix();
    myQbits.applyGate(QGateH);
    myQbits.printQbits();

    return 0;
}