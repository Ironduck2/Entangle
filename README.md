# Entangle

An accessible quantum computing simulator for building circuits, applying logic gates, and exploring multi-qubit states.

## Prerequisites

Before building the project, ensure you have the following installed:

* **C++ Compiler** with C++17 support (GCC, Clang, or MSVC)
* **CMake** (v3.15 or higher recommended)
* **Git**

## Running the Project

1. **Configure CMake:**
  ```bash
  cmake -S . -B build
  ```

2. **Compile the binary:**
  ```bash
  cd build
  make
  ```

3. **Execute the program:**
    ```bash
   ./Entangle
    ```

## Grover's algorithm

The objective of Grover's algorithm can be simply described as finding the solution of any function f(x) by trial and error in $O(\sqrt{x})$ time.

To get the optimal result the algorithm has to be run a total of $R_M \approx \frac{\pi}{4} \sqrt{2^n}$ times. Where n is the amount of qbits simulated.

## Collection of quantum gates

The quantum gates already contained in this simulation are:

### 1-Qubit Gates (2x2 Matrices)

* Identity Gate - $I$
* Pauli-X Gate - $X$
* Pauli-Y Gate - $Y$
* Pauli-Z Gate  - $Z$
* Hadamard Gate - $H$
* S Gate - $S$
* T Gate - $T$

### 2-Qubit Gates (4x4 Matrices)

* CNOT / CX Gate - $CNOT$
* CZ Gate - $CZ$
* SWAP Gate - $\text{SWAP}$

### 3-Qubit Gates (8x8 Matrices)

* Toffoli / CCX Gate - $Toffoli$

More quantum gates can be created easily by defining it with the type:

```cpp
std::vector<std::vector<std::complex<double>>>
```

The quantum gate must be square and it's size must be $2^n$ where n is the number of qbits the quantum gate is applied to.
