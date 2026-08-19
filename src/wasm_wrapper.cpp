#include <emscripten/bind.h>
#include <string>
#include <vector>
#include <complex>
#include "json.hpp"                 
#include "QuantumComputer.hpp"      
#include "QGatesCollection.hpp"  // Asegúrate de que el nombre coincide con tu archivo

using json = nlohmann::json;

std::string runSimulationFromWeb(std::string json_input) {
    // 1. Leer el JSON que nos envía la web
    json payload = json::parse(json_input);
    int amountQbits = payload["amountQbits"];
    
    // 2. Inicializar el simulador cuántico
    QuantumComputer myQbits(amountQbits);

    // 3. Recorrer las instrucciones
    for (auto& inst : payload["instructions"]) {
        std::string gateName = inst["gate"];
        int target = inst["targetQbit"];
        
        // --- Puertas de 1 Qubit ---
        if (gateName == "I") myQbits.applyGate(QGates::I, target);
        else if (gateName == "H") myQbits.applyGate(QGates::H, target);
        else if (gateName == "X") myQbits.applyGate(QGates::X, target);
        else if (gateName == "Y") myQbits.applyGate(QGates::Y, target);
        else if (gateName == "Z") myQbits.applyGate(QGates::Z, target);
        else if (gateName == "S") myQbits.applyGate(QGates::S, target);
        else if (gateName == "T") myQbits.applyGate(QGates::T, target);
        
        // --- Puertas de 2 Qubits (Control + Target) ---
        else if (gateName == "CX" || gateName == "CNOT") {
            int control = inst["controlQbit"];
            std::vector<int> targets = {control, target};
            myQbits.applyMultiQubitGate(QGates::CNOT, targets);
        }
        else if (gateName == "CZ") {
            int control = inst["controlQbit"];
            std::vector<int> targets = {control, target};
            myQbits.applyMultiQubitGate(QGates::CZ, targets);
        }
        else if (gateName == "SWP" || gateName == "SWAP") {
            int control = inst["controlQbit"];
            std::vector<int> targets = {control, target};
            myQbits.applyMultiQubitGate(QGates::SWAP, targets);
        }
        
        // --- Puerta de 3 Qubits (Toffoli: Control 1 + Control 2 + Target) ---
        else if (gateName == "CCX") {
            int control1 = inst["control1"];
            int control2 = inst["control2"];
            std::vector<int> targets = {control1, control2, target};
            myQbits.applyMultiQubitGate(QGates::Toffoli, targets);
        }
    }

    // 4. Obtener y empaquetar el resultado
    std::vector<std::complex<double>> finalState = myQbits.getQbitsList();

    json resultJson;
    resultJson["status"] = "success";
    resultJson["stateVector"] = json::array();

    for (const auto& amp : finalState) {
        resultJson["stateVector"].push_back(amp.real());
    }

    return resultJson.dump();
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("runSimulationFromWeb", &runSimulationFromWeb);
}



// #include <emscripten/bind.h>
// #include <string>
// #include <vector>
// #include <complex>
// #include "json.hpp"                 
// #include "QuantumComputer.hpp"      
// #include "QGatesCollection.hpp"

// using json = nlohmann::json;

// std::string runSimulationFromWeb(std::string json_input) {
//     // 1. Leer el JSON que nos envia la web
//     json payload = json::parse(json_input);
//     int amountQbits = payload["amountQbits"];
    
//     // 2. Inicializar el simulador cuantico
//     QuantumComputer myQbits(amountQbits);

//     // 3. Recorrer las instrucciones y aplicar las puertas del catalogo QGates
//     for (auto& inst : payload["instructions"]) {
//         std::string gateName = inst["gate"];
//         int target = inst["targetQbit"];
        
//         // Puertas de 1 Qubit
//         if (gateName == "I") myQbits.applyGate(QGates::I, target);
//         else if (gateName == "H") myQbits.applyGate(QGates::H, target);
//         else if (gateName == "X") myQbits.applyGate(QGates::X, target);
//         else if (gateName == "Y") myQbits.applyGate(QGates::Y, target);
//         else if (gateName == "Z") myQbits.applyGate(QGates::Z, target);
//         else if (gateName == "S") myQbits.applyGate(QGates::S, target);
//         else if (gateName == "T") myQbits.applyGate(QGates::T, target);
        
//         // Las puertas multiples (CNOT, CZ, SWAP, CCX) las dejamos preparadas 
//         // para cuando la web sepa enviar dos 'targets' en el JSON.
//     }

//     // 4. Obtener el resultado de la simulacion
//     std::vector<std::complex<double>> finalState = myQbits.getQbitsList();

//     // 5. Empaquetar el resultado para la web
//     json resultJson;
//     resultJson["status"] = "success";
//     resultJson["stateVector"] = json::array();

//     // Guardamos la parte "real" de las probabilidades por ahora
//     for (const auto& amp : finalState) {
//         resultJson["stateVector"].push_back(amp.real());
//     }

//     return resultJson.dump();
// }

// EMSCRIPTEN_BINDINGS(my_module) {
//     emscripten::function("runSimulationFromWeb", &runSimulationFromWeb);
// }