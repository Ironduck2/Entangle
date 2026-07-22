#include "QuantumComputer.hpp"
#include "QuantumGate.hpp"
#include "CondensedToNMatrix.hpp"
#include "ArrayMatrix.hpp"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main() {

    auto start =
        high_resolution_clock::now();


    QuantumComputer myQbits(20); // aqui pones los qbits que quieres simular

    // estas dos lineas son para hacer el test con AMatrix (la que guarda 0)
    //AMatrix<std::complex<double>> QGateHA({{1/sqrt(2), 1/sqrt(2)}, {1/sqrt(2), -1/sqrt(2)}});
    //myQbits.applyGate(QGateHA, 7); // el segundo numero es el qbit al que le aplicas la puerta logica
    
    // estas dos lineas son para hacer el test con CMatrix (la que comprime 0)
    CMatrix<std::complex<double>> QGateHC({{1/sqrt(2), 1/sqrt(2)}, {1/sqrt(2), -1/sqrt(2)}}, 0);
    myQbits.applyGate(QGateHC, 10); // el segundo numero es el qbit al que le aplicas la puerta logica

    //si haces el test con un timpo de matriz comenta lo otro. Que no se hagan los dos a la vez


    myQbits.printQbits();

    auto stop =
        high_resolution_clock::now();

    auto duration =
        duration_cast<microseconds>(
            stop - start);

    cout << "Execution time: " << duration.count() << " microseconds" << endl;

    return 0;
}