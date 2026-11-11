// src/habitacion.cpp
#include "habitacion.hpp"
#include <stdexcept>

Habitacion::Habitacion(int numero, double precioNoche)
    : numero_(numero), precioNoche_(precioNoche), ocupada_(false) {
    if (numero <= 0) throw std::invalid_argument("El numero de habitacion debe ser positivo");
    if (precioNoche <= 0) throw std::invalid_argument("El precio por noche debe ser positivo");
}

bool Habitacion::reservar() {
    if (ocupada_) return false;
    ocupada_ = true;
    return true;
}

void Habitacion::liberar() { ocupada_ = false; }

int Habitacion::getNumero() const { return numero_; }
double Habitacion::getPrecioNoche() const { return precioNoche_; }
bool Habitacion::estaOcupada() const { return ocupada_; }

double Habitacion::precioEstancia(int noches) const {
    if (noches <= 0) throw std::invalid_argument("El numero de noches debe ser positivo");
    return noches * precioNoche_;
}

std::string Habitacion::tipo() const { return "Habitacion"; }
