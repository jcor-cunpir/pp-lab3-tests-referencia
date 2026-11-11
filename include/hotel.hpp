// include/hotel.hpp — el hotel guarda sus habitaciones (normales y suites) con unique_ptr.
#pragma once
#include <cstddef>
#include <memory>
#include <vector>
#include "habitacion.hpp"

class Hotel {
public:
    // Lanza std::invalid_argument si ya hay una habitación con ese número.
    void anadir(std::unique_ptr<Habitacion> h);

    // Devuelve la habitación con ese número, o nullptr si no existe.
    Habitacion* buscar(int numero) const;

    // false si ya estaba ocupada. Lanza std::out_of_range si no existe.
    bool reservar(int numero);

    std::size_t total() const;
    int libres() const;
    const std::vector<std::unique_ptr<Habitacion>>& habitaciones() const;

private:
    std::vector<std::unique_ptr<Habitacion>> habitaciones_;
    // Regla del cero: no hace falta escribir destructor, copia ni movimiento.
};
