// include/habitacion.hpp — una habitación del hotel. Es la clase BASE: Suite hereda de ella.
#pragma once
#include <string>

class Habitacion {
public:
    // Lanza std::invalid_argument si el número o el precio por noche no son positivos.
    Habitacion(int numero, double precioNoche);
    virtual ~Habitacion() = default;              // clase base: destructor virtual

    bool reservar();                              // false si ya estaba ocupada
    void liberar();

    int getNumero() const;
    double getPrecioNoche() const;
    bool estaOcupada() const;

    // Precio de una estancia de varias noches.
    // Lanza std::invalid_argument si noches <= 0.
    virtual double precioEstancia(int noches) const;
    virtual std::string tipo() const;             // "Habitacion"

private:
    int numero_;
    double precioNoche_;
    bool ocupada_;
};
