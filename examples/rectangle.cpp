#include <SDL2/SDL.h>
#include "glad/glad.h"

#include "include/core/primitives/shader/shader.h"
#include "include/core/primitives/vertex/vbo.h"
#include "include/core/primitives/vertex/ebo.h"
#include "include/core/primitives/vertex/vao.h"

#include <exception>
#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <sstream>

using namespace gengine;

int main() {
    // Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return -1;
    }

    // Установка атрибутов OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Создание окна с поддержкой OpenGL
    SDL_Window *window = SDL_CreateWindow("OpenGL with SDL",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window) {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return -1;
    }

    // Создание контекста OpenGL
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cout << "Failed to create OpenGL context\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Инициализация GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Проверка версии OpenGL
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    /** Создание шейдерной программы **/
    core::Shader shader;
    auto result = shader.loadVertexShader(core::Shader::PathType{"/home/islam/cpp/Gengine/examples/shaders/rectangle_vertex.shader"});
    if (!result) {
        std::cerr << result.error() << std::endl;
        return EXIT_FAILURE;
    }

    result = shader.loadFragmentShader(core::Shader::PathType{"/home/islam/cpp/Gengine/examples/shaders/rectangle_fragment.shader"});
    if (!result) {
        std::cerr << result.error() << std::endl;
        return EXIT_FAILURE;
    }

    result = shader.makeProgram();
    if (!result) {
        std::cerr << result.error() << std::endl;
        return EXIT_FAILURE;
    }

    /** Генерация буфера на GPU и заполнения буфера данными о вершинах **/
    using VertexArrayObjectType = core::primitives::VertexArrayObject;
    using VertexBufferObjectType = core::primitives::VertexBufferObject;
    using ElementBufferObjectType = core::primitives::ElementBufferObject;

    VertexArrayObjectType vertexesAttr;
    vertexesAttr.bind();

    VertexBufferObjectType vertexes;
    {
        const std::array vertexesData = {
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
        };

        vertexes.bind();
        vertexes.fill(vertexesData);
        vertexesAttr.setVertexeAttributes<float>(
                    VertexArrayObjectType::IndexType{0u},
                    VertexArrayObjectType::ComponentSizeType{3u},
                    VertexArrayObjectType::StrideType{static_cast<unsigned int>(sizeof(float) * 3)});
        vertexes.unbind();
    }

    VertexBufferObjectType colors;
    {
        const std::array colorsData = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 0.0f
        };

        colors.bind();
        colors.fill(colorsData);
        vertexesAttr.setVertexeAttributes<float>(
                    VertexArrayObjectType::IndexType{1u},
                    VertexArrayObjectType::ComponentSizeType{3u},
                    VertexArrayObjectType::StrideType{static_cast<unsigned int>(sizeof(float) * 3)});
        colors.unbind();
    }

    ElementBufferObjectType indices;
    {
        const std::array indicesData = {
            2u, 3u, 0u,
            0u, 1u, 2u
        };

        indices.bind();
        indices.fill(indicesData);
        indices.unbind();
    }

    vertexesAttr.unbind();

    // Основной цикл приложения
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e) > 0) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    // Обработка нажатия клавиши
                    std::cout << "Key pressed: " << e.key.keysym.sym << std::endl;
                    break;
                case SDL_MOUSEMOTION:
                    // Обработка перемещения мыши
                    std::cout << "Mouse moved to: (" << e.motion.x << ", " << e.motion.y << ")" << std::endl;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // Обработка нажатия кнопки мыши
                    std::cout << "Mouse button " << e.button.button << " pressed at: (" << e.button.x << ", " << e.button.y << ")" << std::endl;
                    break;
                case SDL_MOUSEBUTTONUP:
                    // Обработка отпускания кнопки мыши
                    std::cout << "Mouse button " << e.button.button << " released at: (" << e.button.x << ", " << e.button.y << ")" << std::endl;
                    break;
            }
        }

        // Очистка буфера цвета
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Активация шейдерной программы
        shader.usePrograme();

        // Привязка вершинного массива
        vertexesAttr.bind();
        indices.bind();

        // Рендеринг треугольников
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Обновление окна
        SDL_GL_SwapWindow(window);
    }

    // Освобождение ресурсов
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
