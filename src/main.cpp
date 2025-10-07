#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "math/vec3.h"
#include "math/mat4.h"

// Configurações da janela
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "Carpa Diem - Trabalho FCG";

// Variáveis globais para OpenGL
unsigned int VBO, VAO, EBO;
unsigned int shaderProgram;

// Função para processar entrada do usuário
void processInput(GLFWwindow *window) {
    // ESC para fechar a janela
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Callback para redimensionamento da janela
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Função para carregar e ler arquivo de shader
std::string loadShaderSource(const std::string& filePath) {
    std::ifstream shaderFile;
    std::stringstream shaderStream;
    
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try {
        shaderFile.open(filePath);
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        return shaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERRO: Falha ao ler arquivo de shader: " << filePath << std::endl;
        return "";
    }
}

// Função para compilar shader
unsigned int compileShader(unsigned int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    
    // Verificar erros de compilação
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERRO: Compilação do shader falhou\n" << infoLog << std::endl;
    }
    
    return shader;
}

// Função para criar programa de shader
unsigned int createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
    // Carregar código fonte dos shaders
    std::string vertexCode = loadShaderSource(vertexPath);
    std::string fragmentCode = loadShaderSource(fragmentPath);
    
    // Compilar shaders
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);
    
    // Criar programa e linkar shaders
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    // Verificar erros de linkagem
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERRO: Linkagem do programa de shader falhou\n" << infoLog << std::endl;
    }
    
    // Deletar shaders (já estão linkados no programa)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return program;
}

// Função para configurar os buffers e objetos de vértice
void setupTriangle() {
    // Vértices do triângulo (posição + cor)
    float vertices[] = {
        // Posições        // Cores
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Topo - Vermelho
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Esquerda - Verde
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Direita - Azul
    };
    
    // Gerar e configurar VAO e VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // Bind VAO
    glBindVertexArray(VAO);
    
    // Bind e configurar VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Configurar atributos de posição (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Configurar atributos de cor (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Unbind VAO (boa prática)
    glBindVertexArray(0);
}

// Função para renderizar o triângulo
void renderTriangle() {
    // Usar o programa de shader
    glUseProgram(shaderProgram);
    
    // Bind VAO e desenhar
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

// Função para limpeza de recursos
void cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

int main() {
    // Inicializar GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Criar janela
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (window == NULL) {
        std::cout << "ERRO: Falha ao criar janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Inicializar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERRO: Falha ao inicializar GLAD" << std::endl;
        return -1;
    }

    // Configurar viewport inicial
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Criar programa de shader
    shaderProgram = createShaderProgram("shaders/triangle.vert", "shaders/triangle.frag");
    
    // Configurar geometria do triângulo
    setupTriangle();

    // Configurar cor de fundo
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    std::cout << "=== Carpa Diem - Base do Projeto Iniciada ===" << std::endl;
    std::cout << "Versão OpenGL: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Controles:" << std::endl;
    std::cout << "  ESC - Fechar aplicação" << std::endl;
    std::cout << "=============================================" << std::endl;

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        // Processar entrada
        processInput(window);

        // Renderização
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Desenhar triângulo
        renderTriangle();

        // Trocar buffers e processar eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Limpeza
    cleanup();
    glfwTerminate();
    
    std::cout << "Aplicação encerrada com sucesso!" << std::endl;
    return 0;
}