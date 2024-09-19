#include "include/core/primitives/texture/texture.h"

#include <glad/glad.h>

namespace {

constexpr auto FormatTypeToNative(const gengine::core::primitives::Texture::FormatType format) {
    using FormatType = gengine::core::primitives::Texture::FormatType;
    switch (format) {
        case FormatType::RGB: return GL_RGB;
        case FormatType::RGBA: return GL_RGBA;
        default: return GL_RGB;
    }
}

} //! namespace

namespace gengine::core::primitives {

Texture::Texture(const TextureType type):
m_id(0),
m_type(type == TextureType::Texture2D ? GL_TEXTURE_2D : GL_TEXTURE_3D){
    glGenTextures(1, &m_id);
}

Texture::~Texture() {
    clear();
}

Texture::IdType Texture::getId() const {
    return m_id;
}

void Texture::setUp(std::initializer_list<std::pair<ParamNameType, ParamValueType>> nativeParams) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

void Texture::fill(
        const unsigned char* texture,
        WidthType width,
        HeightType height,
        FormatType internalFormat,
        FormatType format
) {
    glTexImage2D(GL_TEXTURE_2D, 0, FormatTypeToNative(internalFormat), width.get(), height.get(), 0, FormatTypeToNative(format), GL_UNSIGNED_BYTE, texture);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::clear() {
    if (m_id != 0) {
        glDeleteTextures(1, &m_id);
    }
}

} //! namespace gengine::core::primitives
