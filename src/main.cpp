// src/main.cpp — prueba rápida de la clase Habitacion.
#include <iostream>
#include "habitacion.hpp"

int main() {
    Habitacion h(101, 80.0);
    h.reservar();
    std::cout << h.tipo() << " " << h.getNumero() << (h.estaOcupada() ? " (ocupada)" : " (libre)")
              << " - 3 noches: " << h.precioEstancia(3) << " EUR\n";
}
