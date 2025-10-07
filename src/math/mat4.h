#pragma once

#include "vec3.h"

/**
 * Classe Mat4 - Representa uma matriz 4x4
 * Esta é a estrutura básica que será expandida posteriormente
 * para incluir todas as transformações geométricas manuais
 * (rotação, translação, escala, projeção, view matrix, etc.)
 */
class Mat4 {
public:
    // Matriz armazenada em column-major order (compatível com OpenGL)
    float m[16];

    // Construtor padrão - matriz identidade
    Mat4() {
        // Inicializa como matriz identidade
        for (int i = 0; i < 16; i++) {
            m[i] = 0.0f;
        }
        m[0] = m[5] = m[10] = m[15] = 1.0f; // Diagonal principal = 1
    }
    
    // Construtor com valores específicos
    Mat4(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33) {
        m[0] = m00;  m[4] = m01;  m[8]  = m02;  m[12] = m03;
        m[1] = m10;  m[5] = m11;  m[9]  = m12;  m[13] = m13;
        m[2] = m20;  m[6] = m21;  m[10] = m22;  m[14] = m23;
        m[3] = m30;  m[7] = m31;  m[11] = m32;  m[15] = m33;
    }

    // Construtor de cópia
    Mat4(const Mat4& other) {
        for (int i = 0; i < 16; i++) {
            m[i] = other.m[i];
        }
    }

    // Acesso aos elementos da matriz
    float& operator[](int index) { return m[index]; }
    const float& operator[](int index) const { return m[index]; }

    // TODO: Implementar as seguintes operações matemáticas:
    // - Multiplicação de matrizes (*)
    // - Matriz de translação (translate)
    // - Matriz de rotação em X, Y, Z (rotateX, rotateY, rotateZ)
    // - Matriz de escala (scale)
    // - Matriz de projeção perspectiva (perspective)
    // - Matriz de projeção ortográfica (ortho)
    // - Matriz de visualização (lookAt)
    // - Inversa da matriz (inverse)
    // - Transposta da matriz (transpose)
    
private:
    // Reservado para implementações futuras
};