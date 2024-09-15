#include "include/core/shader/shader.h"

#include <array>
#include <fstream>

#include <glad/glad.h>

namespace gengine::core {

Shader::Shader():
m_vertexShaderId(0),
m_fragmentShaderId(0),
m_programId(0)
{}

Shader::~Shader() {
    clear();
}

void Shader::clear() {
    for (auto shaderId : { &m_programId, &m_vertexShaderId, &m_fragmentShaderId }) {
        if ((*shaderId) != 0) {
            glDeleteShader(*shaderId);
            *shaderId = 0;
        }
    }
}

atom::utils::DefaultResult<void> Shader::loadVertexShader(const PathType& path) {
    std::string vertexShaderCode = loadShaderCode(path);
    if (vertexShaderCode.empty()) {
        return atom::utils::DefaultResult<void>::onError("Could not open/read file: " + path.string());
    }

    m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    return compileShader(m_vertexShaderId, vertexShaderCode);
}

atom::utils::DefaultResult<void> Shader::loadFragmentShader(const PathType& path) {
    const std::string fragmentShaderCode = loadShaderCode(path);
    if (fragmentShaderCode.empty()) {
        return atom::utils::DefaultResult<void>::onError("Could not open/read file: " + path.string());
    }

    m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    return compileShader(m_fragmentShaderId, fragmentShaderCode);
}

atom::utils::DefaultResult<void> Shader::makeProgram() {
    int isSuccess = 1;
    std::array<char, 512> infoLog = {0};

    m_programId = glCreateProgram();
    for (const auto shaderId : { m_vertexShaderId, m_fragmentShaderId }) {
        glAttachShader(m_programId, shaderId);
    }

    glLinkProgram(m_programId);
    glGetShaderiv(m_programId, GL_LINK_STATUS,  &isSuccess);

    if (!isSuccess) {
        glGetShaderInfoLog(m_programId, infoLog.size(), NULL, infoLog.data());
        return atom::utils::DefaultResult<void>::onError("Link error in a shader program: " + std::string{infoLog.data()});
    } else {
        glDeleteShader(m_vertexShaderId);
        glDeleteShader(m_fragmentShaderId);
        m_vertexShaderId = 0;
        m_fragmentShaderId = 0;
        return atom::utils::DefaultResult<void>::onOk();
    }
}

std::string Shader::loadShaderCode(const PathType& path) const {
    std::ifstream file(path.string());
    if (!file.is_open()) {
        return std::string{};
    } else {
        return std::string{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
    }
}

atom::utils::DefaultResult<void> Shader::compileShader(ShaderIdType& shaderId, const std::string_view shaderCode) {
    int isSuccess = 1;
    std::array<char, 512> infoLog = {0};

    const char *const codeStr = shaderCode.data();

    glShaderSource(shaderId, 1, &codeStr, nullptr);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isSuccess);

    if (!isSuccess) {
        glGetShaderInfoLog(shaderId, infoLog.size(), nullptr, infoLog.data());
        return atom::utils::DefaultResult<void>::onError("Compile error in a vertext shader: " + std::string{infoLog.data()});
    } else {
        return atom::utils::DefaultResult<void>::onOk();
    }
}

Shader::ShaderIdType Shader::getProgramId() const
{
    return m_programId;
}

} //! namespace gengine::core
