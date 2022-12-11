#include "app_error.hpp"

using namespace std;
using namespace opengl_engine;

AppError::AppError(const char* message) : BaseException(message) {

}

AppError::AppError(const std::string& message) : BaseException(message) {

}
