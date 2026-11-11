// src/hotel.cpp
#include "hotel.hpp"
#include <stdexcept>
#include <string>

void Hotel::anadir(std::unique_ptr<Habitacion> h) {
    if (buscar(h->getNumero()) != nullptr) {
        throw std::invalid_argument("Ya existe la habitacion " + std::to_string(h->getNumero()));
    }
    habitaciones_.push_back(std::move(h));
}

Habitacion* Hotel::buscar(int numero) const {
    for (const auto& h : habitaciones_) {
        if (h->getNumero() == numero) return h.get();
    }
    return nullptr;
}

bool Hotel::reservar(int numero) {
    Habitacion* h = buscar(numero);
    if (h == nullptr) throw std::out_of_range("No existe la habitacion " + std::to_string(numero));
    return h->reservar();
}

std::size_t Hotel::total() const { return habitaciones_.size(); }

int Hotel::libres() const {
    int n = 0;
    for (const auto& h : habitaciones_) {
        if (!h->estaOcupada()) n++;
    }
    return n;
}

const std::vector<std::unique_ptr<Habitacion>>& Hotel::habitaciones() const { return habitaciones_; }
