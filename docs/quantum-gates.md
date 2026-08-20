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

$$
I^{\otimes(n-1)} \otimes U \otimes I^{\otimes(m-n)}
$$
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