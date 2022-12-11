#pragma once

#include <memory>

#include <SDL.h>

namespace opengl_engine
{
    class App {
    public:
        explicit App();
        ~App();

        /// Получить синглтон приложения
        static App& getInstance();

        /**
         * @brief Метод запуска приложения. Должен вызываться единожды в main
         * @throws opengl_engine::AppError если приложение уже было запущено
         * @throws opengl_engine::AppError если произошла ошибка при
         * инициализации SDL
         */
        void run();

        /// Метод принудительной остановки работы приложения
        void quit();
        
        /// Запущено ли приложение
        bool isRunning() const;

    private:
        bool is_running_ = false;
        SDL_Window* window_ = nullptr;
        SDL_GLContext gl_context_ = nullptr;

        /**
         * @brief Метод, вызывающийся при запуске приложения
         * @throws opengl_engine::AppError если произошла ошибка при 
         * инициализации SDL
         */
        void onStart();
        /// Метод, вызывающийся при обновлении приложения каждый кадр.
        void onUpdate();
        /// Метод, вызывающийся при прекращении работы приложения
        void onStop();
    };
}   // namespace opengl_engine
