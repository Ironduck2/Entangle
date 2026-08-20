The file *QuantumComputer.hpp* contains the **QuantumComputer** class, this class is defined by two variables; *amountQubits_* and *qubitsList*.

```cpp
int amountQubits_;
vector<complex<double>> qubitsList;
```

The first variable, *amountQubits_* describes the amount of qubits that will be simulated. The second, *qubitsList* contains the state vector of the quantum computer.

The state vector defines the current state of a quantum computer, with each element representing a possible combination of qubits. These elements are complex numbers called **amplitudes**. When the system is measured, the probability of the quantum computer collapsing into a specific state is determined by the *squared magnitude* of its amplitude. The complex number also encodes the **phase**, which is essential for quantum calculations and allows the differentiation between otherwise similar states.

The amount of combinations of qubits that the vector state defines depends on the amount of qubits simulated, always following the formula $2^n$ where $n$ is the amount of qubits.

This exponential growth of the *qubitsList* size creates limits on how many qubits can be simulated. For example, if 30 qubits were to be simulated the size of the *qubitsList* would be $2^{30}$ that is over 1 billion elements. Each element occupies 16 bytes (the complex number is represented by two doubles) that's a total of 16 Gb of space to save the state vector. And this increases exponentially so for 31 qubits it is necessary 32 Gb, for 32 qubits 64Gb...

And to save 40 qubits 8 Terabytes would be needed. That's why it's so hard to simulate large quantities of qubits. This exponential growth is the reason a quantum computer can't be perfectly simulated, but simulating a bunch of qubits is still useful for learning quantum mechanics and testing new algorithms.

One question that may arise is why can't each qubit be described individually, the same way a conventional computer saves bits as 1s or 0s? The answer is **quantum entanglement**. In a classical computer, bits are completely independent. But in a quantum system, qubits can become entangled, meaning their states are linked. For example, a 2 qubit system can exist in a state where there is a 50% probability of measuring `00` and a 50% probability of measuring `11`. If each qubit were saved separately, the information that measuring one collapses the other would be lost. This is why the quantum computer must be described with a state vector.

A summary on the QuantumComputer class:

- It contains two variables, the int *amountQubits_* and the vector of complex numbers *qubitsList* 
- Each element in *qubitsList* describes a possible state the quantum computer can collapse to once measured
- This state is described by a complex number which saves information about probability and phase
- The probability of a state is the squared magnitude of the complex number that defines it
- The size of the vector *qubitsList* depends on the amount of qubits simulated. In total, *qubitsList* will have a total of $2^n$ elements where $n$ is the variable *amountQubits_*
- The size of *qubitsList* grows exponentially as more qubits are simulated. This sets limits on how many qubits can be simulated
- We can't describe individual qubits because of entanglement