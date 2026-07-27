#ifndef QuantumComputer_HH
#define QuantumComputer_HH

#include "CondensedToNMatrix.hpp"
#include "QuantumGate.hpp"
#include <vector>
#include <iostream>
#include <complex>
#include <cmath>
#include <queue>

using namespace std;

class QuantumComputer{
private:
    int amountQbits_;
    vector<complex<double>> qbitsList;
    queue<CMatrix<std::complex<double>>> gateQueue;

    
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


    void applyGate(CMatrix<std::complex<double>> gateMatrix, int targetQbit = 0) {

        targetQbit = amountQbits_ - 1 - targetQbit;
        if(targetQbit < 0 || targetQbit >= amountQbits_) {
            cerr << "Error: Target qubit index is out of range." << endl;
            return;
        }

        if(targetQbit > 0) {
            gateMatrix.IdentityTensoredWithMatrix(pow(2, targetQbit));
        }
        if(amountQbits_ - 1 - targetQbit > 0) {
            gateMatrix.MatrixTensoredWithIdentity(pow(2, amountQbits_ - 1 - targetQbit));
        }
        
        vector<complex<double>> newQbitsList(qbitsList.size(), complex<double>(0, 0));
        gateMatrix.MultiplyMatrixVector(qbitsList, newQbitsList);
        qbitsList = newQbitsList;
    }

    void applyGateQueue() {
        // while (!gateQueue.empty()) {
        //     applyGate(gateQueue.front().getQuantumGateMatrix());
        //     gateQueue.pop();
        // } 
    }

    void gateToQueue(const QuantumGate& gate) {
        //gateQueue.push(gate);
    }

    void printQbits() const {
        for (const auto& qbit : qbitsList) {
            cout << qbit << " ";
        }
        cout << endl;
    } 
};

#endif