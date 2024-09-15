#include "include/core/vertex/vbo.h"

#include <glad/glad.h>

namespace gengine::core {

VertexBufferObject::VertexBufferObject():
m_id(0) {
    glGenBuffers(1, &m_id);
}

VertexBufferObject::~VertexBufferObject() {
    clear();
}

VertexBufferObject::IdType VertexBufferObject::getId() const {
    return m_id;
}

void VertexBufferObject::fillImpl(const void* start, SizeType sizeInBytes, const UsageType usage) {
    unsigned int usageValue = 0;
    switch (usage) {
        case UsageType::StaticDraw: {usageValue = GL_STATIC_DRAW; break;}
        case UsageType::DynamicDraw: {usageValue = GL_DYNAMIC_DRAW; break;}
        case UsageType::StreamDraw: {usageValue = GL_STREAM_DRAW; break;}
        case UsageType::StaticRead: {usageValue = GL_STATIC_READ; break;}
        case UsageType::DynamicRead: {usageValue = GL_DYNAMIC_READ; break;}
        case UsageType::StreamRead: {usageValue = GL_STREAM_READ; break;}
        case UsageType::StaticCopy: {usageValue = GL_STATIC_COPY; break;}
        case UsageType::DynamicCopy: {usageValue = GL_DYNAMIC_COPY; break;}
        case UsageType::StreamCopy: {usageValue = GL_STREAM_COPY; break;}
        default: {usageValue = GL_STATIC_DRAW; break;}
    }
    glBufferData(GL_ARRAY_BUFFER, sizeInBytes, start, usageValue);
}

void VertexBufferObject::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBufferObject::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::clear() {
    if (m_id != 0) {
        glDeleteBuffers(1, &m_id);
        m_id = 0;
    }
}

} //! namespace gengine::core
