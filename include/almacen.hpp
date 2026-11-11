// include/almacen.hpp — guardar y cargar el hotel en un fichero de texto.
// Formato: una habitación por línea, con los campos separados por ';'
//     tipo;numero;precioNoche;ocupada          por ejemplo:   Suite;301;200;1
#pragma once
#include <stdexcept>
#include <string>
#include "hotel.hpp"

// Error al leer o escribir el fichero: no se puede abrir, una línea mal escrita...
class FicheroException : public std::runtime_error {
public:
    explicit FicheroException(const std::string& msg) : std::runtime_error(msg) {}
};

void guardarHotel(const Hotel& hotel, const std::string& ruta);   // lanza FicheroException
Hotel cargarHotel(const std::string& ruta);                        // lanza FicheroException
