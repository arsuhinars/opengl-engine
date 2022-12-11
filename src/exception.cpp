#include "exception.hpp"

using namespace std;
using namespace opengl_engine;

BaseException::BaseException(const char* message) {
    msg_ = string(message);
}

BaseException::BaseException(const string& message) {
    msg_ = message;
}

const char* BaseException::what() const {
    return msg_.c_str();
}
