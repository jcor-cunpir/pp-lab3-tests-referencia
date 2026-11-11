// tests/test_suite.cpp — PRUEBAS UNITARIAS de Suite (CAJA BLANCA).
// Caja blanca: se escriben MIRANDO EL CÓDIGO de Suite::precioEstancia, que tiene un if:
//     if (noches >= 7) { precio = precio * 0.9; }
// Hay que pasar por los DOS caminos (con y sin descuento) y probar justo el LÍMITE (7),
// porque es donde se esconden los errores típicos: escribir > en lugar de >=.
#include <gtest/gtest.h>
#include <memory>
#include "suite.hpp"

TEST(SuiteTest, SinDescuentoConSeisNoches) {          // camino 1: el if NO se cumple
    Suite s(301, 200.0);
    EXPECT_DOUBLE_EQ(s.precioEstancia(6), 1200.0);
}

TEST(SuiteTest, ConDescuentoJustoConSieteNoches) {    // camino 2, en el LÍMITE exacto
    Suite s(301, 200.0);
    EXPECT_DOUBLE_EQ(s.precioEstancia(7), 1260.0);    // 7 * 200 = 1400, menos el 10 %
}

TEST(SuiteTest, ConDescuentoConDiezNoches) {          // camino 2, lejos del límite
    Suite s(301, 200.0);
    EXPECT_DOUBLE_EQ(s.precioEstancia(10), 1800.0);
}

TEST(SuiteTest, CeroNochesLanzaExcepcion) {           // Suite reutiliza la validación de la base
    Suite s(301, 200.0);
    EXPECT_THROW(s.precioEstancia(0), std::invalid_argument);
}

// Polimorfismo: a través de un puntero a la base se llama a la versión de Suite.
TEST(SuiteTest, PolimorfismoDesdeUnPunteroALaBase) {
    std::unique_ptr<Habitacion> h = std::make_unique<Suite>(301, 200.0);
    EXPECT_EQ(h->tipo(), "Suite");
    EXPECT_DOUBLE_EQ(h->precioEstancia(7), 1260.0);
}
