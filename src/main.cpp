// src/main.cpp — un hotel de ejemplo: reserva la primera habitación libre.
#include <iostream>
#include "hotel.hpp"
#include "suite.hpp"

int main() {
    Hotel hotel;
    hotel.anadir(std::make_unique<Habitacion>(101, 80.0));
    hotel.anadir(std::make_unique<Habitacion>(102, 95.5));
    hotel.anadir(std::make_unique<Suite>(301, 200.0));

    for (const auto& h : hotel.habitaciones()) {
        std::cout << "  " << h->tipo() << " " << h->getNumero()
                  << " - 7 noches: " << h->precioEstancia(7) << " EUR\n";
    }
    hotel.reservar(101);
    std::cout << "Libres: " << hotel.libres() << " de " << hotel.total() << "\n";
}
