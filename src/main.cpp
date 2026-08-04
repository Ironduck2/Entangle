#include "QuantumComputer.hpp"
#include "CondensedToNMatrix.hpp"
#include <chrono>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void timeTest();

vector<vector<complex<double>>> generateOracle(int secretKey, int numStates) {
    vector<vector<complex<double>>> oracle(numStates, vector<complex<double>>(numStates, 0.0));
    for (int i = 0; i < numStates; ++i) {
        if (i == secretKey) {
            oracle[i][i] = -1.0;
        } else {
            oracle[i][i] =  1.0;
        }
    }
    return oracle;
}

vector<vector<complex<double>>> generateDiffuser(int numStates) {
    vector<vector<complex<double>>> diffuser(numStates, vector<complex<double>>(numStates, 0.0));
    for (int row = 0; row < numStates; ++row) {
        for (int col = 0; col < numStates; ++col) {
            if (row == col) {
                diffuser[row][col] = (2.0 / numStates) - 1.0;
            } else {
                diffuser[row][col] = (2.0 / numStates);
            }
        }
    }
    return diffuser;
}

int main() {
    bool test = false;

    if (!test){
        int numQubits = 4;
        int numStates = pow(2, numQubits); 
    
        QuantumComputer myQbits(numQubits);

        std::vector<std::vector<std::complex<double>>> QGateH = {
            {1/sqrt(2), 1/sqrt(2)},
            {1/sqrt(2), -1/sqrt(2)}
        };

        std::vector<std::vector<std::complex<double>>> CNOT = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 1},
            {0, 0, 1, 0}
        };


        
        auto start = high_resolution_clock::now();

        int mySecretKey = 5;

        vector<vector<complex<double>>> Oracle = generateOracle(mySecretKey, numStates);
        vector<vector<complex<double>>> Diffuser = generateDiffuser(numStates);

        for (int i = 0; i < myQbits.getAmountQbits(); ++i) {
            myQbits.applyGate(QGateH, i);
        }

        int iterations = 3;
        vector<int> allQubits = {0, 1, 2, 3};

        for (int i = 0; i < iterations; ++i) {
            myQbits.applyMultiQubitGate(Oracle, allQubits);
            
            myQbits.applyMultiQubitGate(Diffuser, allQubits); 
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Execution time: " << duration.count() << " microseconds" << endl;

        myQbits.printQbits(8);
    }
    else {
        timeTest();
    }

    return 0;
}

void timeTest(){
    QuantumComputer myQbits(20);
    std::vector<std::vector<std::complex<double>>> QGateH = {
            {1/sqrt(2), 1/sqrt(2)},
            {1/sqrt(2), -1/sqrt(2)}
        };

    for (int i = 0; i < 10; ++i) {
        myQbits.applyGate(QGateH, 10);
    }

    const int iterations = 100;
    std::vector<long long> times;
    times.reserve(iterations);

    for (int i = 0; i < iterations; ++i) {
        auto start = high_resolution_clock::now();
        
        myQbits.applyGate(QGateH, 10);
        
        auto stop = high_resolution_clock::now();
        times.push_back(duration_cast<microseconds>(stop - start).count());
    }

    std::sort(times.begin(), times.end());

    long long min_time = times.front();
    long long max_time = times.back();
    long long median_time = times[times.size() / 2];
    
    long long sum = 0;
    for (long long t : times) sum += t;
    long long avg_time = sum / times.size();

    cout << "--- Benchmark Results (" << iterations << " iterations) ---" << endl;
    cout << "Minimum time: " << min_time << " us" << endl;
    cout << "Median time:  " << median_time << " us" << endl;
    cout << "Average time: " << avg_time << " us" << endl;
    cout << "Maximum time: " << max_time << " us (Usually an OS interrupt)" << endl;
}