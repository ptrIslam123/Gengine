#ifndef CORE_TEXTURE_H
#define CORE_TEXTURE_H

#include <initializer_list>
#include "type_safe/integer.hpp"

namespace gengine::core::primitives {

class Texture final {
public:
    using IdType = unsigned int;
    using ParamNameType = unsigned int;
    using ParamValueType = unsigned int;
    using WidthType = type_safe::integer<unsigned int>;
    using HeightType = type_safe::integer<unsigned int>;

    enum class TextureType {
        Texture2D, Texture3D,
    };

    enum class FormatType {
        RGB, RGBA,
    };

    explicit Texture(TextureType type = TextureType::Texture2D);
    ~Texture();

    IdType getId() const;
    void setUp(std::initializer_list<std::pair<ParamNameType, ParamValueType>> nativeParams);
    void fill(
            const unsigned char* texture,
            WidthType width,
            HeightType height,
            FormatType internalFormat = FormatType::RGB,
            FormatType format = FormatType::RGB
    );
    void bind();
    void unbind();
    void clear();

private:
    IdType m_id;
    const unsigned int m_type;
};

} //! namespace gengine::core::primitives

#endif //! CORE_TEXTURE_H
