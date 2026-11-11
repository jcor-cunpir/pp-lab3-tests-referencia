// tests/test_almacen.cpp — PRUEBAS DE INTEGRACIÓN: Hotel + Habitacion + Suite + fichero.
// No prueban una clase sola, sino que varias piezas funcionan JUNTAS: se guarda un hotel
// en un fichero de verdad y se vuelve a cargar.
// Los ficheros se crean en la carpeta desde la que se ejecutan los tests (build/) y se borran al final.
#include <gtest/gtest.h>
#include <cstdio>
#include <fstream>
#include <memory>
#include "almacen.hpp"
#include "suite.hpp"

TEST(AlmacenTest, GuardarYCargarDevuelveLoMismo) {
    Hotel original;
    original.anadir(std::make_unique<Habitacion>(101, 80.0));
    original.anadir(std::make_unique<Suite>(301, 200.0));
    original.reservar(301);
    guardarHotel(original, "test_hotel.txt");

    Hotel cargado = cargarHotel("test_hotel.txt");
    ASSERT_EQ(cargado.total(), 2u);
    Habitacion* suite = cargado.buscar(301);
    ASSERT_NE(suite, nullptr);
    EXPECT_EQ(suite->tipo(), "Suite");            // se ha vuelto a crear como Suite, no como Habitacion
    EXPECT_DOUBLE_EQ(suite->getPrecioNoche(), 200.0);
    EXPECT_TRUE(suite->estaOcupada());
    EXPECT_FALSE(cargado.buscar(101)->estaOcupada());
    std::remove("test_hotel.txt");
}

TEST(AlmacenTest, FicheroQueNoExisteLanzaExcepcion) {
    EXPECT_THROW(cargarHotel("no_existe.txt"), FicheroException);
}

TEST(AlmacenTest, LineaMalEscritaLanzaExcepcion) {
    {
        std::ofstream f("test_roto.txt");
        f << "Habitacion;101;80;0\nHabitacion;102;abc;0\n";
    }   // aquí se cierra el fichero: ya se puede leer
    EXPECT_THROW(cargarHotel("test_roto.txt"), FicheroException);
    std::remove("test_roto.txt");
}
