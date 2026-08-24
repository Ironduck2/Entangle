# Entangle

An accessible quantum computing simulator for building circuits, applying logic gates, and exploring multi-qubit states.

* **Live Demo:** [Launch Quantum Simulator](https://ironduck2.github.io/Entangle/simulator/)
* **Documentation:** [Entangle Docs Portal](https://ironduck2.github.io/Entangle/)
---

## Overview

**Entangle** is a high-performance quantum computer simulator written in C++. It simulates multi-qubit statevectors and calculates the probabilities of applying various quantum gates, utilizing bitwise operations to optimize memory usage and performance.

### Key Features

* **Bitwise Statevector Optimization:** Fast gate execution avoiding massive tensor-product matrix bottlenecks.
* **Multi-Qubit Support:** Full support for 1-qubit, 2-qubit, and 3-qubit gates, with custom gate definition capabilities.
* **Quantum Algorithms:** Implements famous quantum algorithms such as **Grover's Search**.

---

## Collection of Quantum Gates

The simulator natively supports the following quantum gates:

| Qubits | Gate Name | Symbol | Matrix Size |
| :---: | :--- | :---: | :---: |
| **1-Qubit** | Identity, Pauli-X, Pauli-Y, Pauli-Z | `I`, `X`, `Y`, `Z` | $2 \times 2$ |
| **1-Qubit** | Hadamard, S Gate, T Gate | `H`, `S`, `T` | $2 \times 2$ |
| **2-Qubit** | CNOT / CX, CZ, SWAP | `CNOT`, `CZ`, `SWAP`| $4 \times 4$ |
| **3-Qubit** | Toffoli / CCX | `Toffoli` | $8 \times 8$ |

Custom gates can easily be defined using standard complex matrices:

```cpp
std::vector<std::vector<std::complex<double>>>
```

## Featured Algorithms: Grover's Search

The objective of Grover's algorithm is to find the unique input $x_0$ to a black-box function $f(x)$ by trial and error in $O(\sqrt{N})$ time.

To achieve the optimal probability of success, the quantum oracle and diffusion operator are iterated $R$ times:

$$R \approx \frac{\pi}{4} \sqrt{2^n}$$

Where $n$ represents the total number of simulated qubits.

---

## Building and Running

### Prerequisites
Ensure you have the following installed before building:
* **C++ Compiler** with C++17 support (`GCC`, `Clang`, or `MSVC`)
* **CMake** (v3.15 or higher recommended)
* **Git**

### Compilation Steps

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


## Documentation
For an in-depth breakdown of the linear algebra, bitwise statevector optimizations, and C++ class architectures, visit the **[Entangle Documentation Site](https://ironduck2.github.io/Entangle/)**.

Developed by Nicolás Gómez Navarro and Adan Gallego Riera.