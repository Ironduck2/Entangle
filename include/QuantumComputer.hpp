#ifndef QuantumComputer_HH
#define QuantumComputer_HH

#include "CondensedToNMatrix.hpp"
#include <vector>
#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

class QuantumComputer{
private:
    int amountQbits_;
    vector<complex<double>> qbitsList;

    
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


    void applyGate(std::vector<std::vector<std::complex<double>>> gateMatrix, int targetQbit = 0) {

        size_t statesNum = qbitsList.size();
        size_t halfStates = statesNum / 2;

        complex<double> u00 = gateMatrix[0][0];
        complex<double> u01 = gateMatrix[0][1];
        complex<double> u10 = gateMatrix[1][0];
        complex<double> u11 = gateMatrix[1][1];

        size_t mask = (1ULL << targetQbit) - 1;
        
        for (size_t i = 0; i < halfStates; ++i) {
            
            size_t lowBits = i & mask;
            
            size_t highBits = (i >> targetQbit) << (targetQbit + 1);
            
            size_t index0 = highBits | lowBits;
            
            size_t index1 = index_0 | (1ULL << targetQbit);

            
            complex<double> amp0 = qbitsList[index0];
            complex<double> amp1 = qbitsList[index1];

            qbitsList[index0] = (u00 * amp0) + (u01 * amp1);
            qbitsList[index1] = (u10 * amp0) + (u11 * amp1);
        }
    }
    
    void printQbits() const {
        for (int i = 0; i < 4; ++i) {
            cout << qbitsList[i] << " ";
        }
        cout << endl;
    } 
};

#endif