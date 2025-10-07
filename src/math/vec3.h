#pragma once

#include <cmath>

/**
 * Classe Vec3 - Representa um vetor 3D
 * Esta é a estrutura básica que será expandida posteriormente
 * para incluir operações matemáticas manuais (sem usar bibliotecas externas)
 */
class Vec3 {
public:
    float x, y, z;

    // Construtor padrão
    Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    
    // Construtor com valores
    Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    
    // Construtor de cópia
    Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) {}

    // TODO: Implementar as seguintes operações matemáticas:
    // - Adição de vetores (+)
    // - Subtração de vetores (-)
    // - Multiplicação por escalar (*)
    // - Produto escalar (dot)
    // - Produto vetorial (cross)
    // - Normalização (normalize)
    // - Magnitude (length)
    // - Distância entre pontos
    
private:
    // Reservado para implementações futuras
};