# LAB 3 · Pruebas con GoogleTest — repositorio de REFERENCIA (Hotel)

![CI](https://github.com/jcor-cunpir/pp-lab3-tests-referencia/actions/workflows/ci.yml/badge.svg)

Un proyecto pequeño **con todas las pruebas hechas**, para usarlo como **modelo**. En la práctica no se modifica:
se lee, se compila, se ejecutan sus tests y se **copian y adaptan** sus tests al repositorio de ejercicio
**[pp-lab3-tests-ejercicio](https://github.com/jcor-cunpir/pp-lab3-tests-ejercicio)** (una biblioteca con la misma estructura).

La estructura es la misma que la de la plantilla del proyecto (`include/` + `src/` + `tests/` + `CMakeLists.txt` + CI).

## Las clases

| Clase | Qué hace |
| --- | --- |
| `Habitacion` | Número, precio por noche y si está ocupada. `reservar()`, `liberar()` y `precioEstancia(noches)`. Valida los datos con excepciones |
| `Suite` | Hereda de `Habitacion`. 10 % de descuento en estancias de **7 noches o más** |
| `Hotel` | Guarda las habitaciones en un `vector<unique_ptr<Habitacion>>`. `anadir`, `buscar` (devuelve `nullptr` si no existe), `reservar`, `libres` |
| `almacen` | `guardarHotel` y `cargarHotel`: persistencia en `hotel.txt` (`tipo;numero;precio;ocupada`) |

## Compilar y pasar los tests

| | Windows (PowerShell) | Mac (Terminal) |
| --- | --- | --- |
| Descargar | `git clone https://github.com/jcor-cunpir/pp-lab3-tests-referencia.git` | igual |
| Entrar | `cd pp-lab3-tests-referencia` | igual |
| Configurar (1.ª vez; descarga GoogleTest) | `cmake -S . -B build -G Ninja` | `cmake -S . -B build` |
| Compilar | `cmake --build build` | `cmake --build build` |
| Pasar los tests | `cd build`, `ctest --output-on-failure`, `cd ..` | igual |
| Ver cada test | `.\build\tests_gestor.exe` | `./build/tests_gestor` |
| Ejecutar el programa | `.\build\gestor.exe` | `./build/gestor` |

Deberías ver `[  PASSED  ] 24 tests.`

## El mapa de las pruebas

| Fichero | Tipo de prueba | Qué enseña |
| --- | --- | --- |
| `tests/test_habitacion.cpp` (9 tests) | **Unitaria, caja negra** | Probar lo que promete el `.hpp`: casos normales y **valores límite**. `EXPECT_EQ`, `EXPECT_DOUBLE_EQ`, `EXPECT_TRUE`/`FALSE`, `EXPECT_THROW`, `EXPECT_NO_THROW` |
| `tests/test_suite.cpp` (5 tests) | **Unitaria, caja blanca** | Mirar el `if` del código y pasar por **los dos caminos**, justo en el límite (6 y 7 noches). Polimorfismo con `unique_ptr<Habitacion>` |
| `tests/test_hotel.cpp` (6 tests) | **Unitaria con fixture** | `TEST_F`: los mismos datos preparados para varios tests. `ASSERT_NE(p, nullptr)` antes de usar un puntero |
| `tests/test_almacen.cpp` (3 tests) | **Integración** | Varias piezas juntas (Hotel + Suite + fichero): guardar, cargar y comprobar que todo vuelve igual |
| `tests/test_rendimiento.cpp` (1 test) | **Rendimiento** | Medir cuánto tarda con muchos datos (`std::chrono`) y `EXPECT_LT` con un límite generoso |

## GoogleTest en una tabla

| Quiero comprobar… | Macro |
| --- | --- |
| Que dos valores son iguales (`int`, `string`, `bool`, punteros…) | `EXPECT_EQ(real, esperado)` |
| Que dos `double` son iguales | `EXPECT_DOUBLE_EQ(real, esperado)` |
| Que algo es verdadero / falso | `EXPECT_TRUE(cond)` / `EXPECT_FALSE(cond)` |
| Que algo es menor que un valor | `EXPECT_LT(a, b)` |
| Que una llamada lanza una excepción de un tipo | `EXPECT_THROW(llamada, tipo)` |
| Que una llamada NO lanza | `EXPECT_NO_THROW(llamada)` |
| Lo mismo, pero **parando el test** si falla (p. ej., antes de usar un puntero) | `ASSERT_EQ`, `ASSERT_NE`, `ASSERT_TRUE`… |

Un test nuevo: `TEST(Grupo, NombreDelTest) { preparar; actuar; comprobar; }`. Un fichero de tests nuevo hay que
añadirlo a `add_executable(tests_gestor ...)` en el `CMakeLists.txt`.
