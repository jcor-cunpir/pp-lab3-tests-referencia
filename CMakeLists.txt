# ============================================================================
#  CMakeLists.txt — LAB 3, repositorio de REFERENCIA (Hotel)
#  Misma estructura que la plantilla pp-plantilla-proyecto.
#  Lo único que tendréis que tocar normalmente está marcado con  >>> AQUÍ <<<
# ============================================================================
cmake_minimum_required(VERSION 3.15)

project(HotelReferencia VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ----------------------------------------------------------------------------
# 1. Los .cpp de las clases (todos menos main.cpp).
#    >>> AQUÍ <<<  Cada vez que creéis un .cpp nuevo en src/, añadidlo a esta lista.
# ----------------------------------------------------------------------------
set(FUENTES
    src/habitacion.cpp
    src/suite.cpp
)

# Warnings activados: el compilador como aliado.
if(MSVC)
    set(WARNINGS /W4)
else()
    set(WARNINGS -Wall -Wextra -Wpedantic)
endif()

# ----------------------------------------------------------------------------
# 2. El programa principal: main.cpp + las clases.
# ----------------------------------------------------------------------------
add_executable(gestor src/main.cpp ${FUENTES})
target_include_directories(gestor PRIVATE include)
target_compile_options(gestor PRIVATE ${WARNINGS})

# ----------------------------------------------------------------------------
# 3. Los tests con GoogleTest (se descarga solo la primera vez que se configura).
# ----------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)   # necesario en Windows con Visual Studio
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)                # no usamos gmock: compila más rápido
FetchContent_MakeAvailable(googletest)

enable_testing()

# >>> AQUÍ <<<  Cada vez que creéis un fichero de tests nuevo en tests/, añadidlo aquí.
add_executable(tests_gestor
    tests/test_habitacion.cpp
    tests/test_suite.cpp
    ${FUENTES}
)
target_include_directories(tests_gestor PRIVATE include)
target_compile_options(tests_gestor PRIVATE ${WARNINGS})
target_link_libraries(tests_gestor PRIVATE GTest::gtest_main)

add_test(NAME GestorTests COMMAND tests_gestor)
