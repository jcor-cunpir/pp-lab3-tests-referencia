// src/main.cpp — carga el hotel (o crea uno de ejemplo), reserva la primera habitación libre y guarda.
#include <iostream>
#include "almacen.hpp"
#include "suite.hpp"

int main() {
    const std::string ruta = "hotel.txt";
    Hotel hotel;
    try {
        hotel = cargarHotel(ruta);
        std::cout << "Cargadas " << hotel.total() << " habitaciones de " << ruta << "\n";
    } catch (const FicheroException& e) {
        std::cout << "Aviso: " << e.what() << ". Empiezo con un hotel de ejemplo.\n";
        hotel.anadir(std::make_unique<Habitacion>(101, 80.0));
        hotel.anadir(std::make_unique<Habitacion>(102, 95.5));
        hotel.anadir(std::make_unique<Suite>(301, 200.0));
    }

    for (const auto& h : hotel.habitaciones()) {
        std::cout << "  " << h->tipo() << " " << h->getNumero()
                  << (h->estaOcupada() ? " (ocupada)" : " (libre)")
                  << " - 7 noches: " << h->precioEstancia(7) << " EUR\n";
    }

    bool reservada = false;
    for (const auto& h : hotel.habitaciones()) {
        if (!h->estaOcupada()) {
            hotel.reservar(h->getNumero());
            std::cout << "Reservada la " << h->getNumero() << "\n";
            reservada = true;
            break;
        }
    }
    if (!reservada) std::cout << "No quedan habitaciones libres\n";

    guardarHotel(hotel, ruta);
    std::cout << "Libres: " << hotel.libres() << " de " << hotel.total() << "\n";
}
