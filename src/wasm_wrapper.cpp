#include <emscripten/bind.h>
#include <string>
#include <vector>
#include <complex>
#include "json.hpp"                 
#include "QuantumComputer.hpp"      
#include "QGatesCollection.hpp"  // <-- Añadimos el catalogo de tu socio

using json = nlohmann::json;

std::string runSimulationFromWeb(std::string json_input) {
    // 1. Leer el JSON que nos envia la web
    json payload = json::parse(json_input);
    int amountQbits = payload["amountQbits"];
    
    // 2. Inicializar el simulador cuantico
    QuantumComputer myQbits(amountQbits);

    // 3. Recorrer las instrucciones y aplicar las puertas del catalogo QGates
    for (auto& inst : payload["instructions"]) {
        std::string gateName = inst["gate"];
        int target = inst["targetQbit"];
        
        // Puertas de 1 Qubit
        if (gateName == "I") myQbits.applyGate(QGates::I, target);
        else if (gateName == "H") myQbits.applyGate(QGates::H, target);
        else if (gateName == "X") myQbits.applyGate(QGates::X, target);
        else if (gateName == "Y") myQbits.applyGate(QGates::Y, target);
        else if (gateName == "Z") myQbits.applyGate(QGates::Z, target);
        else if (gateName == "S") myQbits.applyGate(QGates::S, target);
        else if (gateName == "T") myQbits.applyGate(QGates::T, target);
        
        // Las puertas multiples (CNOT, CZ, SWAP, CCX) las dejamos preparadas 
        // para cuando la web sepa enviar dos 'targets' en el JSON.
    }

    // 4. Obtener el resultado de la simulacion
    std::vector<std::complex<double>> finalState = myQbits.getQbitsList();

    // 5. Empaquetar el resultado para la web
    json resultJson;
    resultJson["status"] = "success";
    resultJson["stateVector"] = json::array();

    // Guardamos la parte "real" de las probabilidades por ahora
    for (const auto& amp : finalState) {
        resultJson["stateVector"].push_back(amp.real());
    }

    return resultJson.dump();
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("runSimulationFromWeb", &runSimulationFromWeb);
}