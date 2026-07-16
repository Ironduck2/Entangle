#ifndef QuantumComputer_HH
#define QuantumComputer_HH

#include "QuantumGate.hh"
#include <vector>
#include <iostream>
#include <complex>
#include <cmath>

class QuantumComputer{
private:
    int amountQbits_;
    std::vector<std::complex<double>> qbitsList;

public:
    QuantumComputer(int amountQbits) :
        amountQbits_(amountQbits),
        qbitsList(pow(2, amountQbits_), complex<double>(0, 0)){
            qbitsList.front() = complex<double>(1, 0);
        }

    int getAmountQbits() const {
        return amountQbits_;
    }
    int getListSize() const {
        return qbitsList.size();
    }

    void applyGate(const QuantumGate& gate) {
        std::vector<std::complex<double>> qbitsListCopy = qbitsList;
        qbitsList[0] = gate.getQuantumGateMatrix()[0][0] * qbitsListCopy[0] + gate.getQuantumGateMatrix()[0][1] * qbitsListCopy[1];
        qbitsList[1] = gate.getQuantumGateMatrix()[1][0] * qbitsListCopy[0] + gate.getQuantumGateMatrix()[1][1] * qbitsListCopy[1];
    }

    void printQbits() const {
        for (const auto& qbit : qbitsList) {
            std::cout << qbit << " ";
        }
        std::cout << std::endl;
    }
};

#endif