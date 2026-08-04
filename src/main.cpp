#include "QuantumComputer.hpp"
#include "CondensedToNMatrix.hpp"
#include <chrono>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void timeTest();

int main() {
    bool test = false;

    if (!test){
        QuantumComputer myQbits(15);

        std::vector<std::vector<std::complex<double>>> QGateH = {
            {1/sqrt(2), 1/sqrt(2)},
            {1/sqrt(2), -1/sqrt(2)}
        };
    
        auto start = high_resolution_clock::now();
        myQbits.applyGate(QGateH, 1);
        auto stop = high_resolution_clock::now();
    
    
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Execution time: " << duration.count() << " microseconds" << endl;

        myQbits.printQbits();
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