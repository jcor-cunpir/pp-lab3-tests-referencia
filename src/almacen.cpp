// src/almacen.cpp — guardar y cargar con <fstream>.
#include "almacen.hpp"
#include <fstream>
#include <sstream>
#include "suite.hpp"

void guardarHotel(const Hotel& hotel, const std::string& ruta) {
    std::ofstream f(ruta);                                   // si ya existe, lo SOBRESCRIBE
    if (!f.is_open()) throw FicheroException("No se puede escribir en " + ruta);
    for (const auto& h : hotel.habitaciones()) {
        f << h->tipo() << ';' << h->getNumero() << ';' << h->getPrecioNoche() << ';'
          << h->estaOcupada() << '\n';
    }
}

Hotel cargarHotel(const std::string& ruta) {
    std::ifstream f(ruta);
    if (!f.is_open()) throw FicheroException("No se puede abrir " + ruta);

    Hotel hotel;
    std::string linea;
    int numLinea = 0;
    while (std::getline(f, linea)) {
        numLinea++;
        if (linea.empty()) continue;
        std::stringstream ss(linea);                         // trocear la línea por los ';'
        std::string tipo, numero, precio, ocupada;
        std::getline(ss, tipo, ';');
        std::getline(ss, numero, ';');
        std::getline(ss, precio, ';');
        std::getline(ss, ocupada, ';');
        try {
            std::unique_ptr<Habitacion> h;
            if (tipo == "Suite") {
                h = std::make_unique<Suite>(std::stoi(numero), std::stod(precio));
            } else if (tipo == "Habitacion") {
                h = std::make_unique<Habitacion>(std::stoi(numero), std::stod(precio));
            } else {
                throw std::invalid_argument("tipo desconocido");
            }
            if (ocupada == "1") h->reservar();
            hotel.anadir(std::move(h));
        } catch (const std::invalid_argument&) {   // stoi/stod sin número, precio <= 0, tipo o número repetido
            throw FicheroException(ruta + ", linea " + std::to_string(numLinea) + ": formato incorrecto");
        }
    }
    return hotel;
}
