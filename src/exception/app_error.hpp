#pragma once
#include "../exception.hpp"

namespace opengl_engine {
    /// Класс для общих ошибок в проекте
    class AppError : public BaseException {
    public:
        /// @brief Конструктор класса исключения
        /// @param message сообщение, описывающее ошибку
        explicit AppError(const char* message);

        /// @brief Конструктор класса исключения
        /// @param message сообщение, описывающее ошибку
        explicit AppError(const std::string& message);
    };
}
