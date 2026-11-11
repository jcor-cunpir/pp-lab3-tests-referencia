// tests/test_rendimiento.cpp — PRUEBA DE RENDIMIENTO.
// No comprueba QUÉ devuelve el programa, sino CUÁNTO TARDA con muchos datos.
// El límite es muy generoso a propósito: el CI se ejecuta en máquinas compartidas y sin
// optimizar (Debug). Sirve para detectar que algo se ha vuelto MUCHO más lento, no para medir.
#include <gtest/gtest.h>
#include <chrono>
#include <memory>
#include "hotel.hpp"

TEST(RendimientoTest, BuscarEnUnHotelGrandeTardaMenosDeUnSegundo) {
    Hotel hotel;
    for (int n = 1; n <= 2000; n++) {
        hotel.anadir(std::make_unique<Habitacion>(n, 50.0));
    }

    auto inicio = std::chrono::steady_clock::now();
    int encontradas = 0;
    for (int n = 1; n <= 1000; n++) {
        if (hotel.buscar(n * 2) != nullptr) encontradas++;
    }
    auto fin = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();

    EXPECT_EQ(encontradas, 1000);
    EXPECT_LT(ms, 1000) << "La busqueda ha tardado " << ms << " ms";   // << añade un mensaje si falla
}
