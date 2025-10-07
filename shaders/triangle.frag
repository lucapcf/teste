#version 330 core

// Variável de entrada do vertex shader
in vec3 vertexColor; // Cor interpolada do vértice

// Cor de saída final do fragmento
out vec4 FragColor;

void main()
{
    // Define a cor final do fragmento
    FragColor = vec4(vertexColor, 1.0);
}