#pragma once
#include <exception>
#include <string>

namespace opengl_engine {
    /// Базовый класс для всех исключений проекта
    class BaseException : public std::exception {
    public:
        /// @brief Конструктор класса исключения
        /// @param message сообщение, описывающее ошибку
        explicit BaseException(const char* message);

        /// @brief Конструктор класса исключения
        /// @param message сообщение, описывающее ошибку
        explicit BaseException(const std::string& message = "");

        /// Метод, возвращающий описание исключения
        const char* what() const override;
    
    private:
        std::string msg_;
    };
}

#include "exception/app_error.hpp"
