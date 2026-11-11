// src/suite.cpp
#include "suite.hpp"

Suite::Suite(int numero, double precioNoche) : Habitacion(numero, precioNoche) {}

double Suite::precioEstancia(int noches) const {
    double precio = Habitacion::precioEstancia(noches);   // valida las noches y multiplica
    if (noches >= 7) {
        precio = precio * 0.9;                             // 10 % de descuento
    }
    return precio;
}

std::string Suite::tipo() const { return "Suite"; }
