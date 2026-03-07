cmake_minimum_required(VERSION 3.20)
project(Dispro C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ==========================
# AUTO: agarrar TODOS los .c comunes
# ==========================
file(GLOB COMMON_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/Funciones Principales/**/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/Circuitos Secuenciales Digitales/**/*.c"
)

# ==========================
# Include dirs comunes
# ==========================
set(COMMON_INCLUDES
        "${CMAKE_CURRENT_SOURCE_DIR}/Funciones Principales"
        "${CMAKE_CURRENT_SOURCE_DIR}/Circuitos Secuenciales Digitales"
)

# ==========================
# Punto Taller 1
# ==========================
file(GLOB PUNTO1_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/SolucionTaller/Punto1/*.c"
)

add_executable(Run_Punto_Taller1
        ${PUNTO1_SOURCES}
        ${COMMON_SOURCES}

        "Circuitos Secuenciales Digitales/Contadores Bits/Contadores_4Bit.c"
        "Circuitos Secuenciales Digitales/Flip Flops/FlipFlop_gate.c"
)

target_include_directories(Run_Punto_Taller1 PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/SolucionTaller/Punto1"

        "${CMAKE_CURRENT_SOURCE_DIR}/Funciones Principales/Compuertas Logicas"
        "${CMAKE_CURRENT_SOURCE_DIR}/Funciones Principales/WaveDrom Format"
        "${CMAKE_CURRENT_SOURCE_DIR}/Funciones Principales/CambiosDeBase_Bus"

        "${CMAKE_CURRENT_SOURCE_DIR}/Circuitos Secuenciales Digitales/Contadores Bits"
        "${CMAKE_CURRENT_SOURCE_DIR}/Circuitos Secuenciales Digitales/Clocks"
        "${CMAKE_CURRENT_SOURCE_DIR}/Circuitos Secuenciales Digitales/Flip Flops"

        ${COMMON_INCLUDES}
)


# ==========================
# Punto Taller 3
# ==========================
file(GLOB PUNTO3_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/SolucionTaller/Punto4/*.c"
)

add_executable(Run_Punto_Taller3
        ${PUNTO3_SOURCES}
        ${COMMON_SOURCES}
)

target_include_directories(Run_Punto_Taller3 PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/SolucionTaller/Punto4"
        ${COMMON_INCLUDES}
)