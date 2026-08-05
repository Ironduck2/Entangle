#include <emscripten/bind.h>
#include <string>
#include <iostream>

// Esta es la función que JavaScript llamará directamente
std::string runSimulationFromWeb(std::string json_input) {
    // 1. Aquí recibiremos el JSON de la web.
    std::cout << "C++ ha recibido: " << json_input << std::endl;
    
    // 2. (Más adelante, aquí parsearemos el JSON y llamaremos a QuantumComputer)
    
    // 3. Devolvemos un JSON simulado de prueba
    return "{\"status\": \"success\", \"message\": \"Simulación completada desde C++\"}";
}

// EMSCRIPTEN BINDINGS: Esto le dice al compilador qué funciones exponer a JavaScript
EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("runSimulationFromWeb", &runSimulationFromWeb);
}