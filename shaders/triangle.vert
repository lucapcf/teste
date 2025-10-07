#version 330 core

// Atributos de entrada do vértice
layout (location = 0) in vec3 aPos;   // Posição do vértice
layout (location = 1) in vec3 aColor; // Cor do vértice

// Variável de saída para o fragment shader
out vec3 vertexColor; // Cor que será interpolada

void main()
{
    // Define a posição do vértice no espaço de clipping
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    
    // Passa a cor para o fragment shader
    vertexColor = aColor;
}