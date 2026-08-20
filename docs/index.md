# Welcome to Entangle!

**Entangle** is a quantum computer simulator that can calculate the probabilities of applying a variety of quantum gates to a state vector that represents the qubits in a quantum computer.

This page main objective is to explain the capabilities of this project and to explain how the code works.
## About us

Entangle is a quantum computer simulator build by:

- Nicolás Gómez Navarro: Student of Data engineering at UAB

- Adan Gallego Riera: Student of Computer Science at UPC-FIB
## The QuantumComputer class

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
## Quantum gates

With the quantum states definition it is now possible to apply quantum gates to modify this state of the quantum computer.

With only one qubit, there are 4 main quantum gates that can be used. Each of them is represented by a matrix that is multiplied by the state vector to get the new resulting state. 

These 4 quantum gates are:

- Pauli-X Gate : $\begin{bmatrix} 0 & 1 \\ 1 & 0 \end{bmatrix}$
- Pauli-Y Gate : $\begin{bmatrix} 0 & -i \\ i & 0 \end{bmatrix}$
- Pauli-Z Gate : $\begin{bmatrix} 1 & 0 \\ 0 & -1 \end{bmatrix}$
- Hadamard Gate : $\frac{1}{\sqrt{2}} \begin{bmatrix} 1 & 1 \\ 1 & -1 \end{bmatrix}$

To mathematically apply a quantum gate to a single qubit a matrix multiplication must be done between the matrix representing the gate and the state vector. If the state vector starts with state 0 this would be the operation that would be needed:
$$\frac{1}{\sqrt{2}} \begin{bmatrix} 1 & 1 \\ 1 & -1 \end{bmatrix} \begin{bmatrix} 1 \\ 0 \end{bmatrix} = \frac{1}{\sqrt2} \begin{bmatrix} 1 \\ 1\end{bmatrix}$$
The resulting state is a superposition of both 0 and 1 with equal probabilities since $(\frac{1}{\sqrt2})^2 = 0.5$

The rest of the gates are applied the same way, only with different results. So applying gates is just matrix multiplication.

It's different when applying quantum gates to multi-qubit quantum computers. In a two qubit computer the vector would have 4 items and the matrix that describes the quantum gate is a $2 \times 2$ matrix. It's not possible to just multiply them, the matrix has to be expanded to a $4 \times 4$ to be able to multiply it by the vector state. But the transformation that the quantum gates describes has to be conserved when expanding it. The solution to this problem is the **tensor product**.

The tensor product (often called the Kronecker product) is a non-commutative operation between two matrices. Taking the tensor product essentially means copying the second matrix into every element of the first matrix, and then multiplying it by that element's scalar value. As an example, calculating the tensor product of the X gate with the identity would look like this:

The second matrix (the identity) is multiplied by each element of the first matrix (the x gate).

$$X \otimes I = \begin{bmatrix} 0 \begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix} & 1 \begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix} \\ 1 \begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix} & 0 \begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix} \end{bmatrix}$$
Then the resulting elements of the matrix are combined into a new one, creating an expanded matrix that contains the transformation of the X gate.

$$X \otimes I = \begin{bmatrix} 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1 \\ 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \end{bmatrix}$$

This expanded $4 \times 4$ matrix applies an X gate to a two-qubit system, but to which qubit exactly?

Because the operation is non-commutative, the orden of the operation tells us which qubit is the target. If the intention is to apply the quantum gate to the first qubit the tensor product would be in the order $X \otimes I$. It is done in reverse to apply it to the second qubit $I \otimes X$.

To scale this up for any number of qubits the tensor product of the matrices has to be done in a specific order. To apply a quantum gate $U$ to the $n$ qubit in a $m$ qubit system the order of operations is the tensor product of $n-1$ Identity matrices, the $U$ gate and $m - n$ Identity matrices.

$$I^{\otimes(n-1)} \otimes U \otimes I^{\otimes(m-n)}$$
($I^{\otimes (n-1)}$ means the tensor product of $I$ with itself $n-1$ times)

The result of this operation is the matrix that when multiplied by the state vector describes the quantum gate transformation to the n qubit. 

This process works, but some problems arise when applying multi-qubit gates. It works fine when applying the gate to two consecutive qubits, but when applying a gate to non-consecutive qubits the problems start.

An example of a multi-qubit gate is the CNOT. This quantum gate is applied to two qubits and it's described by this matrix.
$$\text{CNOT} = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 0 & 1 \\ 0 & 0 & 1 & 0 \end{bmatrix}$$
If we set qubit 0 as the control and qubit 2 as the target in a 3 qubit system there is no string of tensor products that would lead us to the desired matrix that would define this transformation. Because a CNOT gate is a single $4 \times 4$ matrix spanning two qubits, it's not possible to "split" it in half to tensor an Identity matrix $I$ into the middle for qubit 1.

To force full matrix multiplication to work for non-adjacent qubits, one must either sandwich the gate between **SWAP gates** to temporarily bring the qubits next to each other, or decompose the CNOT gate into a sum of projector tensor products.

While these approaches clarify the linear algebra behind these operations, in our objective to build an efficient quantum computer simulator creating matrices of this magnitude, that grow exponentially with the amount of qubits we are working on, this creates massive bottlenecks in performance and memory. Linear algebra is the math that describes these quantum computer operations, but to simulate these operations faster, there is another method, with **bitwise statevector operations**.

A summary on Quantum gates:
- There are 4 main quantum gates that can be applied to one qubit
- Applying quantum gates is the same as matrix multiplication with the state vector
- Tensor products are used to scale matrices while conserving the transformations they describe
- Following an specific order of tensor products is necessary to apply quantum gates to specific qubits
- This process does not work with multi-qubits quantum gates that are applied to non-consecutive qubits. Although there are solutions to solve this
- Following the math that linear algebra describes with quantum computer operations helps with a better understanding of how it works. But for the simulator to be efficient another method has to be used
- For optimising the use of quantum gates, Entangle uses bitwise statevector operations
## Bitwise statevector operations

When applying a quantum gate, the state vector values only change in those qubits it is applied to. In the state vector this means the gate only mixes amplitudes that describe states differing *only* by that specific qubit.

For example, in a 3-qubit system, if a gate is applied to qubit 0 (the rightmost bit), the state $000$ only mixes with $001$. The state $010$ only mixes with $011$, and so on. It's not necessary to have a $8 \times 8$ matrix to then multiply by the state vector. Only the $2 \times 2$ gate matrix is needed to be applied individually to these specific pairs of amplitudes.

This is what the applyGate function does.

``` cpp
void applyGate(vector<vector<complex<double>>> gateMatrix, int targetQubit = 0) {
	
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
```

This is the code for the entire function. It applies any quantum gate defined by a $2 \times 2$ matrix to a quantum computer of any size. It also does it incredibly fast, taking only around 16 ms to apply a hadamard gate to a 20 qubit system.

So how does it work?

Some variable are defined needed by the following code. Each element of the matrix is also defined in a variable because it's faster than accessing it later.

```cpp
size_t statesNum = qubitsList.size();
size_t halfStates = statesNum / 2;  

complex<double> u00 = gateMatrix[0][0];
complex<double> u01 = gateMatrix[0][1];
complex<double> u10 = gateMatrix[1][0];
complex<double> u11 = gateMatrix[1][1];
```

Then, the mask is defined. This code creates a sequence of 1 in all bits to the right of the target qubit. If the target qubit is 1 (the middle qubit in a 3-qubit system), `1ULL << 1` gives us `010` in binary. Subtracting 1 gives us `001`. This mask helps separate the bits below the target qubit.

```cpp
size_t mask = (1ULL << targetQubit) - 1;
```

Then the loop starts. Because the operations are done in pairs, the loop only has to be done for half the size of the states.
``` cpp
for (size_t i = 0; i < halfStates; ++i) { ... }
```

The objective inside of the loop is to find one of each qubit combination where the target qubit is 0, then this combination will be paired with the same combination but with the target qubit changed to 1. When a pair is complete, it's multiplied by the matrix of the quantum gate and the new values are saved into the state vector.

To build all of these combinations the lower part of the number is constructed first, for it an `&` operation can be done between `i` and the mask created earlier, for the high bits the variable `i` is displaced to the right as many times as the target qubit. This creates 0 on the lower part and preserves the high part of the number. Then the number is moved back to the left but it's moved one place more to leave a 0 in the spot of the target qubit.

```cpp
size_t lowBits = i & mask;
size_t highBits = (i >> targetQubit) << (targetQubit + 1);
```

From this the qubit combination is complete, and it's pair can be created by placing a 1 in the target qubit spot. Then, the values in the vector states with these indexes can be multiplied by the matrix that describes the quantum gate.

```cpp
complex<double> amp0 = qubitsList[index0];
complex<double> amp1 = qubitsList[index1];

qubitsList[index0] = (u00 * amp0) + (u01 * amp1);
qubitsList[index1] = (u10 * amp0) + (u11 * amp1);
```

And with this, a quantum gate can be applied efficiently to a vector state of any size. The problem is that this code only applies quantum gates defined by $2 \times 2$ matrices. Another generalised function is used for applying larger quantum gates.

This function is called *applyMultiQubitGate*.

In the applyGate function, the values in the vector state were grouped in pairs because only one qubit was being affected. In this generalised function the objective is to apply the matrix that defines the quantum gates in groups of $2^n$ where n is the amount of target qubits.

```cpp
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
```

The code starts defining some variables. The number of loops depends on how many targets there are because we do the matrix multiplication in groups that depend on the variable k. 

```cpp
int k = targets.size();
size_t dim = 1ULL << k;
size_t num_states = qubitsList.size();
size_t loops = num_states >> k;
```

Then the targets are sorted for generating the combinations of qubits in order to apply them. Two vectors are also created for the indicies and the amplitudes. Used for applying the matrix operation once to the vector state once the indicies are found.

```cpp
vector<int> sorted_targets = targets;
sort(sorted_targets.begin(), sorted_targets.end());

vector<size_t> indices(dim);
vector<complex<double>> temp_amps(dim);
```

After this the loop starts. A combination of qubits is created for each target qubit the same way the applyGate function did it, but because it is looped as much times as target qubits it creates a combination with always a 0 in all of the target qubits.

```cpp
for (size_t i = 0; i < loops; ++i) {
	
	size_t base_index = i;
	for (int t : sorted_targets) {
		size_t mask = (1ULL << t) - 1;
		size_t low = base_index & mask;
		size_t high = (base_index >> t) << (t + 1);
		base_index = low | high;
	}
. . .
}     
```

With the base index created, the code generates all the other states in this group. Since there are `k` target qubits, there are `2^k` (or `dim`) possible combinations of 0s and 1s for those specific positions.

```cpp
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
```

With the group of combinations saved in the indicies matrix the next code can apply the matrix multiplication and save the results in the state vector.
```cpp
for (size_t row = 0; row < dim; ++row) {
	
	complex<double> new_amp(0.0, 0.0);
	for (size_t col = 0; col < dim; ++col) {
		new_amp += gateMatrix[row][col] * temp_amps[col];
	}
	qubitsList[indices[row]] = new_amp;
}
```

These two functions show how Entangle manages quantum gate application to state vectors.