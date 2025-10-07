cmake_minimum_required(VERSION 3.16)
project(CarpaDiem)

# Define o padrão do C++ para C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuração para debug/release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Encontra os pacotes necessários
find_package(PkgConfig REQUIRED)
find_package(glfw3 REQUIRED)

# GLAD (será baixado ou você pode usar uma versão local)
# Assumindo que você vai incluir GLAD diretamente no projeto
set(GLAD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/glad/include")
set(GLAD_SOURCE "${CMAKE_SOURCE_DIR}/external/glad/src/glad.c")

# Se GLAD não estiver disponível localmente, você pode baixá-lo
if(NOT EXISTS ${GLAD_SOURCE})
    message(WARNING "GLAD não encontrado. Baixe de https://glad.dav1d.de/ e coloque em external/glad/")
endif()

# Include directories
include_directories(${GLAD_INCLUDE_DIR})
include_directories(src)

# Coleta todos os arquivos fonte
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.h"
    ${GLAD_SOURCE}
)

# Cria o executável
add_executable(${PROJECT_NAME} ${SOURCES})

# Link das bibliotecas
target_link_libraries(${PROJECT_NAME} 
    glfw 
    ${CMAKE_DL_LIBS}
    GL
    X11
    pthread
    Xrandr
    Xi
)

# Copia os shaders para o diretório de build
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})