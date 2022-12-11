#include <iostream>

#include <glad/glad.h>

#include "app.hpp"
#include "exception.hpp"

using namespace std;
using namespace opengl_engine;

App::App() {

}

App::~App() {
    if (is_running_) {
        onStop();
    }
}

App& App::getInstance() {
    static auto instance = make_unique<App>();
    return *instance.get();
}

void App::run() {
    if (is_running_) {
        throw AppError("App is already running");
    }

    onStart();

    // Создаем главный цикл приложения
    while (is_running_) {
        onUpdate();
    }

    onStop();
}

void App::quit() {
    is_running_ = false;
}

bool App::isRunning() const {
    return is_running_;
}

void App::onStart() {
    is_running_ = true;
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        auto err = "SDL init error: \n"s + SDL_GetError();
        SDL_ClearError();
        throw AppError(err);
    }

    // Указываем аттрибуты OpenGL для окна
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Создаем окно приложения
    window_ = SDL_CreateWindow(
        "SDL App example",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_OPENGL
    );
    if (window_ == NULL) {
        auto err = "SDL window creating error: \n"s + SDL_GetError();
        SDL_ClearError();
        throw AppError(err);
    }

    // Загружаем OpenGL
    if (SDL_GL_LoadLibrary(NULL)) {
        auto err = "SDL OpenGL loading error: \n"s + SDL_GetError();
        SDL_ClearError();
        throw AppError(err);
    }
    
    // Создаем контекст OpenGL
    gl_context_ = SDL_GL_CreateContext(window_);
    if (gl_context_ == NULL) {
        auto err = "SDL context creating error: \n"s + SDL_GetError();
        SDL_ClearError();
        throw AppError(err);
    }

    // Загружаем функции библиотеки OpenGL
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        throw AppError("GLAD OpenGL loading error: \n"s);
    }

    // Включаем вертикальную синхронизацию
    SDL_GL_SetSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    cout << "App has started" << endl;
}

void App::onUpdate() {
    SDL_Event ev;

    // Обрабатываем входящие события SDL
    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
            // Событие закрытия приложения
            case SDL_EventType::SDL_QUIT:
                quit();
                break;
        }
    }

    // Выполняем отрисовку
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Выводим графику на экран
    SDL_GL_SwapWindow(window_);
}

void App::onStop() {
    // Освобождаем ресурсы
    if (window_ != NULL) {
        SDL_DestroyWindow(window_);
    }
    SDL_GL_DeleteContext(gl_context_);
    SDL_GL_UnloadLibrary();
    SDL_Quit();

    window_ = nullptr;
    is_running_ = false;

    cout << "App has stopped" << endl;
}
