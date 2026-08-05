#include "QuantumComputer.hpp"
#include "CondensedToNMatrix.hpp"
#include "QGatesCollection.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace QGates;
using namespace std;
using namespace std::chrono;

void simpleTest();
void timeTest();
void groverAlgorithm();

int main() {
    bool test = false;
    bool grover = true;

    if (!test && !grover) {
        simpleTest();
    }
    else if (test) {
        timeTest();
    }
    else if (grover){
        groverAlgorithm();
    }

    return 0;
}

void simpleTest(){
    int numQbits = 20;
    QuantumComputer myQbits(numQbits);

    auto start = high_resolution_clock::now();

    // ======= code to test speed here =======

    for (int i = 0; i < numQbits; ++i) {
        myQbits.applyGate(H, i);
    }

    // ======= code to test speed here =======

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;

    myQbits.printQbits(8);
}

void timeTest(){
    int numQbits = 20;
    QuantumComputer myQbits(numQbits);

    for (int i = 0; i < 10; ++i) {
        myQbits.applyGate(H, 10);
    }

    const int iterations = 100;
    std::vector<long long> times;
    times.reserve(iterations);

    for (int i = 0; i < iterations; ++i) {
        auto start = high_resolution_clock::now();
        
        myQbits.applyGate(H, 10);
        
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

void groverAlgorithm() {
    int numQbits = 16; // Not recommended for higher than 20 qbits as number of iterations will grow exponentially. 20 qbits will require 785 iterations, while 21 qbits will require 1110 iterations...
    int targetKey = 0;
    int iterations = static_cast<int>((M_PI / 4) * std::sqrt(std::pow(2, numQbits))); // recommended number of iterations follows the formula: floor((pi/4) * sqrt(2^n)) where n is numQbits.
    cout << "Number of iterations for Grover's algorithm: " << iterations << endl;

    QuantumComputer myQbits(numQbits);


    for (int i = 0; i < numQbits; ++i) {

        myQbits.applyGate(QGates::H, i);
    }

    auto start = high_resolution_clock::now();

    // ======= code to test speed here =======


    for (int i = 0; i < iterations; ++i) {
        myQbits.applyOracle(targetKey);
        myQbits.applyDiffusionOperator();
    }

    // ======= code to test speed here =======

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;


    myQbits.printQbits(8);
}