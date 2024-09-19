#include "include/core/primitives/vertex/vao.h"

#include <glad/glad.h>

namespace gengine::core::primitives {

VertexArrayObject::VertexArrayObject(): m_id(0) {
    glGenVertexArrays(1, &m_id);
}

VertexArrayObject::~VertexArrayObject() {
    clear();
}

void VertexArrayObject::bind() {
    glBindVertexArray(m_id);
}

void VertexArrayObject::unbind() {
    glBindVertexArray(0);
}

VertexArrayObject::IdType VertexArrayObject::getId() const {
    return m_id;
}

void VertexArrayObject::setVertexeAttributesImpl(
        const IndexType& index,
        const ComponentSizeType& componetSize,
        const StrideType& stride,
        const void* offset,
        const Type type
) {
    auto indexValue = index.get();
    auto componentSizeValue = componetSize.get();
    auto strideValue = stride.get();
    auto typeValue = 0;
    switch (type) {
    case Type::Float: { typeValue = GL_FLOAT; break; }
    case Type::Integer: { typeValue = GL_INT; break; }
    case Type::UnsignedInteger: { typeValue = GL_UNSIGNED_INT; break; }
        default: { typeValue = GL_FLOAT; break; }
    }

    glEnableVertexAttribArray(indexValue);
    glVertexAttribPointer(indexValue, componentSizeValue, typeValue, GL_FALSE, strideValue, offset);
}

void VertexArrayObject::clear() {
    if (m_id != 0) {
        glDeleteVertexArrays(1, &m_id);
        m_id = 0;
    }
}

} //! namespace gengine::core::primitives
