#include "include/core/vertex/vao.h"

#include <glad/glad.h>

namespace gengine::core {

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
        const unsigned int index,
        const unsigned int componetSize,
        const unsigned int stride,
        const Type type
) {
    unsigned int typeValue = 0;
    switch (type) {
        case Type::Float: { typeValue = GL_FLOAT; break; }
        case Type::Integer: { typeValue = GL_INT; break; }
        case Type::UnsignedInteger: { typeValue = GL_UNSIGNED_INT; break; }
        default: { typeValue = GL_FLOAT; break; }
    }

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, componetSize, typeValue, GL_FALSE, stride, nullptr);
}

void VertexArrayObject::clear() {
    if (m_id != 0) {
        glDeleteVertexArrays(1, &m_id);
        m_id = 0;
    }
}

} //! namespace gengine::core
