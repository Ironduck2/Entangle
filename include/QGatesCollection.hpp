#include <vector>
#include <complex>
#include <cmath>

namespace QGates {
    using Matrix = std::vector<std::vector<std::complex<double>>>;

    // ==========================================
    // 1-Qubit Gates (2x2 Matrices)
    // ==========================================

    // Identity Gate
    inline const Matrix I = {
        {1, 0},
        {0, 1}
    };

    // Pauli-X Gate (NOT gate)
    inline const Matrix X = {
        {0, 1},
        {1, 0}
    };

    // Pauli-Y Gate
    inline const Matrix Y = {
        {0, -1i},
        {1i, 0}
    };

    // Pauli-Z Gate (Phase flip)
    inline const Matrix Z = {
        {1, 0},
        {0, -1}
    };

    // Hadamard Gate
    inline const Matrix H = {
        {1.0 / std::sqrt(2.0),  1.0 / std::sqrt(2.0)},
        {1.0 / std::sqrt(2.0), -1.0 / std::sqrt(2.0)}
    };

    // S Gate (Phase gate)
    inline const Matrix S = {
        {1, 0},
        {0, 1i}
    };

    // T Gate (pi/8 gate)
    inline const Matrix T = {
        {1, 0},
        {0, 1.0 / std::sqrt(2.0) + (1.0 / std::sqrt(2.0)) * 1i}
    };


    // ==========================================
    // 2-Qubit Gates (4x4 Matrices)
    // ==========================================

    // CNOT / CX Gate (Controlled-NOT)
    inline const Matrix CNOT = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0}
    };

    // CZ Gate (Controlled-Z)
    inline const Matrix CZ = {
        {1, 0, 0,  0},
        {0, 1, 0,  0},
        {0, 0, 1,  0},
        {0, 0, 0, -1}
    };

    // SWAP Gate
    inline const Matrix SWAP = {
        {1, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 1}
    };


    // ==========================================
    // 3-Qubit Gates (8x8 Matrices)
    // ==========================================
    
    // Toffoli / CCX Gate (Controlled-Controlled-NOT)
    inline const Matrix Toffoli = {
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1, 0}
    };
}