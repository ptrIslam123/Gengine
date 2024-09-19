#ifndef CORE_SHARED_H
#define CORE_SHARED_H

#include <filesystem>
#include <string>
#include <string_view>

#include "atom/include/utils/result.h"

namespace gengine::core {

class Shader final {
public:
    using PathType = std::filesystem::path;
    using ShaderIdType = unsigned int;

    explicit Shader();
    ~Shader();
    Shader(const Shader& ) = delete;
    Shader& operator=(const Shader& ) = delete;
    atom::utils::DefaultResult<void> loadVertexShader(const PathType& path);
    atom::utils::DefaultResult<void> loadFragmentShader(const PathType& path);
    atom::utils::DefaultResult<void> makeProgram();

    void usePrograme();
    ShaderIdType getProgramId() const;
    void clear();

private:
    std::string loadShaderCode(const PathType& path) const;
    atom::utils::DefaultResult<void> compileShader(ShaderIdType& shaderId, std::string_view shaderCode);

    ShaderIdType m_vertexShaderId;
    ShaderIdType m_fragmentShaderId;
    ShaderIdType m_programId;
};

} //! namespace gengine::core

#endif //! CORE_SHARED_H
