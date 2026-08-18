#include <emscripten/bind.h>
#include <string>
#include <vector>
#include <complex>
#include "json.hpp"                 
#include "QuantumComputer.hpp"      

using json = nlohmann::json;

std::string runSimulationFromWeb(std::string json_input) {
    // 1. Leer el JSON que nos envía la web
    json payload = json::parse(json_input);
    int amountQbits = payload["amountQbits"];
    
    // 2. Inicializar el simulador cuántico con la cantidad de Qubits elegida
    QuantumComputer myQbits(amountQbits);

    // 3. Definir las matrices de las puertas lógicas básicas
    std::vector<std::vector<std::complex<double>>> GateH = {
        {1/sqrt(2), 1/sqrt(2)},
        {1/sqrt(2), -1/sqrt(2)}
    };
    std::vector<std::vector<std::complex<double>>> GateX = {
        {0, 1},
        {1, 0}
    };
    std::vector<std::vector<std::complex<double>>> GateZ = {
        {1, 0},
        {0, -1}
    };

    // 4. Recorrer las instrucciones y aplicar las puertas
    for (auto& inst : payload["instructions"]) {
        std::string gateName = inst["gate"];
        int target = inst["targetQbit"];
        
        if (gateName == "H") myQbits.applyGate(GateH, target);
        else if (gateName == "X") myQbits.applyGate(GateX, target);
        else if (gateName == "Z") myQbits.applyGate(GateZ, target);
    }

    // 5. Obtener el resultado de la simulación
    std::vector<std::complex<double>> finalState = myQbits.getQbitsList();

    // 6. Empaquetar el resultado para la web
    json resultJson;
    resultJson["status"] = "success";
    resultJson["stateVector"] = json::array();

    // Guardamos la parte "real" de las probabilidades
    for (const auto& amp : finalState) {
        resultJson["stateVector"].push_back(amp.real());
    }

    return resultJson.dump();
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("runSimulationFromWeb", &runSimulationFromWeb);
}