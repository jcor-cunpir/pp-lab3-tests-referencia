// tests/test_habitacion.cpp — PRUEBAS UNITARIAS de Habitacion (CAJA NEGRA).
// Caja negra: se escriben mirando solo lo que PROMETE la clase (los comentarios del .hpp),
// sin mirar cómo está programada. Se prueban los casos normales y los VALORES LÍMITE
// (el 0, el primer valor válido, el primer valor no válido...).
//
// Cada test sigue tres pasos: PREPARAR (crear objetos), ACTUAR (llamar al método)
// y COMPROBAR (EXPECT_...).
#include <gtest/gtest.h>
#include <stdexcept>
#include "habitacion.hpp"

// ---- Construcción --------------------------------------------------------------
TEST(HabitacionTest, ConstructorGuardaLosDatos) {
    Habitacion h(101, 80.0);                      // PREPARAR
    EXPECT_EQ(h.getNumero(), 101);                // COMPROBAR: enteros y texto -> EXPECT_EQ
    EXPECT_DOUBLE_EQ(h.getPrecioNoche(), 80.0);   // double -> EXPECT_DOUBLE_EQ
    EXPECT_FALSE(h.estaOcupada());                // una habitación nueva está libre
}

TEST(HabitacionTest, PrecioCeroLanzaExcepcion) {             // valor límite: 0 NO es válido
    EXPECT_THROW(Habitacion(101, 0.0), std::invalid_argument);
}

TEST(HabitacionTest, PrecioMinimoPositivoNoLanza) {          // valor límite: el primero válido
    EXPECT_NO_THROW(Habitacion(101, 0.01));
}

TEST(HabitacionTest, NumeroNegativoLanzaExcepcion) {
    EXPECT_THROW(Habitacion(-5, 80.0), std::invalid_argument);
}

// ---- Reservar y liberar ----------------------------------------------------------
TEST(HabitacionTest, ReservarCambiaElEstado) {
    Habitacion h(101, 80.0);
    EXPECT_TRUE(h.reservar());                    // ACTUAR y COMPROBAR a la vez
    EXPECT_TRUE(h.estaOcupada());
}

TEST(HabitacionTest, ReservarDosVecesDevuelveFalse) {
    Habitacion h(101, 80.0);
    h.reservar();
    EXPECT_FALSE(h.reservar());                   // la segunda vez ya estaba ocupada
    EXPECT_TRUE(h.estaOcupada());
}

TEST(HabitacionTest, LiberarDejaLaHabitacionLibre) {
    Habitacion h(101, 80.0);
    h.reservar();
    h.liberar();
    EXPECT_FALSE(h.estaOcupada());
}

// ---- Precio de la estancia ---------------------------------------------------------
TEST(HabitacionTest, PrecioEstanciaMultiplicaPorLasNoches) {
    Habitacion h(101, 80.0);
    EXPECT_DOUBLE_EQ(h.precioEstancia(3), 240.0);
}

TEST(HabitacionTest, PrecioEstanciaConCeroNochesLanzaExcepcion) {   // valor límite
    Habitacion h(101, 80.0);
    EXPECT_THROW(h.precioEstancia(0), std::invalid_argument);
}
