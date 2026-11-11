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
