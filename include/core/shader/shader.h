#ifndef CORE_SHARED_H
#define CORE_SHARED_H

#include <string>

namespace gengine::core {

class Shader final {
public:
    explicit Shader();

private:
    std::string m_vertexCode;
    std::string m_fragmentCode;
};

} //! namespace gengine::core

#endif //! CORE_SHARED_H
