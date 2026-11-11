// src/main.cpp — prueba rápida de Habitacion y Suite, a través de punteros a la base.
#include <iostream>
#include <memory>
#include <vector>
#include "suite.hpp"

int main() {
    std::vector<std::unique_ptr<Habitacion>> habitaciones;
    habitaciones.push_back(std::make_unique<Habitacion>(101, 80.0));
    habitaciones.push_back(std::make_unique<Suite>(301, 200.0));
    for (const auto& h : habitaciones) {
        std::cout << h->tipo() << " " << h->getNumero()
                  << " - 7 noches: " << h->precioEstancia(7) << " EUR\n";
    }
}
