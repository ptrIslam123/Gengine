#ifndef CORE_VERTEXT_ARRAY_OBJECT_H
#define CORE_VERTEXT_ARRAY_OBJECT_H

#include "type_safe/index.hpp"

#include <span>

namespace gengine::core::primitives {

class VertexArrayObject final {
public:
    using IndexType = type_safe::integer<unsigned int>;
    using ComponentSizeType = type_safe::integer<unsigned int>;
    using StrideType = type_safe::integer<unsigned int>;
    using IdType = unsigned int;

    explicit VertexArrayObject();
    ~VertexArrayObject();

    IdType getId() const;
    template<typename T>
    void setVertexeAttributes(
            const IndexType& index,
            const ComponentSizeType& componentSize,
            const StrideType& strideInBytes,
            const void* offset = nullptr
    );
    void bind();
    void unbind();
    void clear();

private:
    enum class Type {
        Float, Integer, UnsignedInteger,
    };

    void setVertexeAttributesImpl(
            const IndexType& index,
            const ComponentSizeType& componentSize,
            const StrideType& stride,
            const void* offset,
            Type type
    );

    IdType m_id;
};

template<>
inline void VertexArrayObject::setVertexeAttributes<int>(
        const IndexType& index,
        const ComponentSizeType& componentSize,
        const StrideType& stride,
        const void* offset
) {
    setVertexeAttributesImpl(index, componentSize, stride, offset, Type::Integer);
}

template<>
inline void VertexArrayObject::setVertexeAttributes<unsigned int>(
        const IndexType& index,
        const ComponentSizeType& componentSize,
        const StrideType& stride,
        const void* offset
) {
    setVertexeAttributesImpl(index, componentSize, stride, offset, Type::UnsignedInteger);
}

template<>
inline void VertexArrayObject::setVertexeAttributes<float>(
        const IndexType& index,
        const ComponentSizeType& componentSize,
        const StrideType& stride,
        const void* offset
) {
    setVertexeAttributesImpl(index, componentSize, stride, offset, Type::Float);
}

} //! namespace gengine::core::primitives

#endif //! CORE_VERTEXT_ARRAY_OBJECT_H
