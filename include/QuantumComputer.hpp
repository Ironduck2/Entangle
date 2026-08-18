#ifndef QuantumComputer_HH
#define QuantumComputer_HH

#include "CondensedToNMatrix.hpp"
#include <vector>
#include <iostream>
#include <complex>
#include <algorithm>
#include <cmath>

using namespace std;

class QuantumComputer{
private:
    int amountQubits_;
    vector<complex<double>> qubitsList;

    
public:
    QuantumComputer(int amountQubits) :
    amountQubits_(amountQubits),
    qubitsList(pow(2, amountQubits_), complex<double>(0, 0)){
        qubitsList.front() = complex<double>(1, 0);
    }

    int getAmountQubits() const {
        return amountQubits_;
    }
    int getListSize() const {
        return qubitsList.size();
    }

    // =========== APPLYING QUANTUM GATES ===========
    void applyGate(std::vector<std::vector<std::complex<double>>> gateMatrix, int targetQubit = 0) {

        size_t statesNum = qubitsList.size();
        size_t halfStates = statesNum / 2;

        complex<double> u00 = gateMatrix[0][0];
        complex<double> u01 = gateMatrix[0][1];
        complex<double> u10 = gateMatrix[1][0];
        complex<double> u11 = gateMatrix[1][1];

        size_t mask = (1ULL << targetQubit) - 1;
        
        for (size_t i = 0; i < halfStates; ++i) {
            
            size_t lowBits = i & mask;
            
            size_t highBits = (i >> targetQubit) << (targetQubit + 1);
            
            size_t index0 = highBits | lowBits;
            
            size_t index1 = index0 | (1ULL << targetQubit);

            
            complex<double> amp0 = qubitsList[index0];
            complex<double> amp1 = qubitsList[index1];

            qubitsList[index0] = (u00 * amp0) + (u01 * amp1);
            qubitsList[index1] = (u10 * amp0) + (u11 * amp1);
        }
    }

    // =========== APPLYING MULTI-QUBIT GATES ===========
    void applyMultiQubitGate(const vector<vector<complex<double>>>& gateMatrix, const vector<int>& targets) {
        int k = targets.size();
        size_t dim = 1ULL << k;
        size_t num_states = qubitsList.size();
        size_t loops = num_states >> k;

        vector<int> sorted_targets = targets;
        sort(sorted_targets.begin(), sorted_targets.end());

        vector<size_t> indices(dim);
        vector<complex<double>> temp_amps(dim);

        for (size_t i = 0; i < loops; ++i) {
            
            size_t base_index = i;
            
            for (int t : sorted_targets) {
                size_t mask = (1ULL << t) - 1;
                size_t low = base_index & mask;
                size_t high = (base_index >> t) << (t + 1);
                base_index = low | high;
            }

            for (size_t m = 0; m < dim; ++m) {
                size_t final_index = base_index;
                
                for (size_t j = 0; j < k; ++j) {
                    if ((m >> j) & 1) {
                        final_index |= (1ULL << targets[j]);
                    }
                }
                indices[m] = final_index;
                temp_amps[m] = qubitsList[final_index];
            }

            for (size_t row = 0; row < dim; ++row) {
                complex<double> new_amp(0.0, 0.0);
                for (size_t col = 0; col < dim; ++col) {
                    new_amp += gateMatrix[row][col] * temp_amps[col];
                }
                qubitsList[indices[row]] = new_amp;
            }
        }
    }

    // =========== GROVER'S ALGORITHM OPTIMIZATIONS ===========
    void applyOracle(int targetKey){
        qubitsList[targetKey] *= -1.0;
    }

    void applyDiffusionOperator() {
        size_t numStates = qubitsList.size();
        std::complex<double> sum(0.0, 0.0);
    
        for (size_t i = 0; i < numStates; ++i) {
            sum += qubitsList[i];
        }
        
        std::complex<double> mean = sum / static_cast<double>(numStates);
        std::complex<double> two_times_mean = 2.0 * mean;
        
        for (size_t i = 0; i < numStates; ++i) {
            qubitsList[i] = two_times_mean - qubitsList[i];
        }
    }
    
    void printQbits() const {
        for (int i = 0; i < qubitsList.size(); ++i) {
            cout << qubitsList[i] << " ";
        }
        cout << endl;
    } 

    void printQbits(int n) const {
        for (int i = 0; i < n; ++i) {
            cout << qubitsList[i] << " ";
        }
        cout << endl;
    } 
};

#endif