// tests/test_hotel.cpp — PRUEBAS UNITARIAS de Hotel con un FIXTURE (TEST_F).
// Un fixture es una clase que prepara los mismos datos para varios tests: así no se repite
// el PREPARAR en cada uno. Cada TEST_F empieza con un hotel NUEVO (los tests no se afectan
// entre sí): 101 y 102 normales, 301 suite.
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include "hotel.hpp"
#include "suite.hpp"

class HotelTest : public ::testing::Test {
protected:
    void SetUp() override {                       // se ejecuta ANTES de cada TEST_F
        hotel.anadir(std::make_unique<Habitacion>(101, 80.0));
        hotel.anadir(std::make_unique<Habitacion>(102, 95.5));
        hotel.anadir(std::make_unique<Suite>(301, 200.0));
    }
    Hotel hotel;
};

TEST_F(HotelTest, TotalCuentaTodasLasHabitaciones) {
    EXPECT_EQ(hotel.total(), 3u);                 // 3u: total() devuelve un size_t (sin signo)
    EXPECT_EQ(hotel.libres(), 3);
}

TEST_F(HotelTest, BuscarUnaQueExisteLaDevuelve) {
    Habitacion* h = hotel.buscar(301);
    ASSERT_NE(h, nullptr);                        // ASSERT: si falla, el test PARA aquí
    EXPECT_EQ(h->getNumero(), 301);               // (sin el ASSERT, h-> con nullptr rompería todo)
    EXPECT_EQ(h->tipo(), "Suite");
}

TEST_F(HotelTest, BuscarUnaQueNoExisteDevuelveNullptr) {
    EXPECT_EQ(hotel.buscar(999), nullptr);
}

TEST_F(HotelTest, AnadirUnNumeroRepetidoLanzaExcepcion) {
    EXPECT_THROW(hotel.anadir(std::make_unique<Habitacion>(101, 50.0)), std::invalid_argument);
    EXPECT_EQ(hotel.total(), 3u);                 // y no se ha añadido
}

TEST_F(HotelTest, ReservarReduceLasLibres) {
    EXPECT_TRUE(hotel.reservar(102));
    EXPECT_EQ(hotel.libres(), 2);
    EXPECT_TRUE(hotel.buscar(102)->estaOcupada());
}

TEST_F(HotelTest, ReservarUnaQueNoExisteLanzaExcepcion) {
    EXPECT_THROW(hotel.reservar(999), std::out_of_range);
}
