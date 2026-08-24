When applying a quantum gate, the state vector values only change in those qubits it is applied to. In the state vector this means the gate only mixes amplitudes that describe states differing *only* by that specific qubit.

For example, in a 3-qubit system, if a gate is applied to qubit 0 (the rightmost bit), the state `000` only mixes with `001`. The state `010` only mixes with `011`, and so on. It's not necessary to have a $8 \times 8$ matrix to then multiply by the state vector. Only the $2 \times 2$ gate matrix is needed to be applied individually to these specific pairs of amplitudes.

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