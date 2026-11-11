// include/suite.hpp — una suite es una habitación con descuento en las estancias largas.
#pragma once
#include "habitacion.hpp"

class Suite : public Habitacion {
public:
    Suite(int numero, double precioNoche);

    // Como la de Habitacion, pero con un 10 % de descuento si la estancia es de
    // 7 noches o más (7 incluido).
    double precioEstancia(int noches) const override;
    std::string tipo() const override;            // "Suite"
};
