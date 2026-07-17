#ifndef QuantumComputer_HH
#define QuantumComputer_HH

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
    queue<QuantumGate> gateQueue;

    
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


    void applyGate(vector<vector<pair<int, complex<double>>>>& finalGateMatrix, int targetQbit = 0) {

        //IdentityTensoredWithMatrix(finalGateMatrix);    
        // vector<complex<double>> qbitsListCopy = qbitsList;
        // qbitsList[0] = gate.getQuantumGateMatrix()[0][0] * qbitsListCopy[0] + gate.getQuantumGateMatrix()[0][1] * qbitsListCopy[1];
        // qbitsList[1] = gate.getQuantumGateMatrix()[1][0] * qbitsListCopy[0] + gate.getQuantumGateMatrix()[1][1] * qbitsListCopy[1];
    }

    void applyGateQueue() {
        // while (!gateQueue.empty()) {
        //     applyGate(gateQueue.front().getQuantumGateMatrix());
        //     gateQueue.pop();
        // } 
    }

    void gateToQueue(const QuantumGate& gate) {
        gateQueue.push(gate);
    }

    void printQbits() const {
        for (const auto& qbit : qbitsList) {
            cout << qbit << " ";
        }
        cout << endl;
    } 
};

#endif