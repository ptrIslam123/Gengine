#include "include/core/primitives/vertex/gl_buffer_obj_base.h"

#include <array>

#include <glad/glad.h>

namespace {

constexpr unsigned int TargetTypeToNative(const gengine::core::GlBufferObjectBase::TargetType targetType)
{
    using TargetType = gengine::core::GlBufferObjectBase::TargetType;
    switch (targetType) {
        case TargetType::ArrayBuffer: return GL_ARRAY_BUFFER;
        case TargetType::ElementArrayBuffer: return GL_ELEMENT_ARRAY_BUFFER;
        default: return GL_ARRAY_BUFFER;
    }
}

constexpr unsigned int UsageTypeToNative(gengine::core::GlBufferObjectBase::UsageType usage)
{
    using UsageType = gengine::core::GlBufferObjectBase::UsageType;
    switch (usage) {
        case UsageType::StaticDraw: return GL_STATIC_DRAW;
        case UsageType::DynamicDraw: return GL_DYNAMIC_DRAW;
        case UsageType::StreamDraw: return GL_STREAM_DRAW;
        case UsageType::StaticRead: return GL_STATIC_READ;
        case UsageType::DynamicRead: return GL_DYNAMIC_READ;
        case UsageType::StreamRead: return GL_STREAM_READ;
        case UsageType::StaticCopy: return GL_STATIC_COPY;
        case UsageType::DynamicCopy: return GL_DYNAMIC_COPY;
        case UsageType::StreamCopy: return GL_STREAM_COPY;
        default: return GL_STATIC_DRAW;
    }
}

} //! namespace

namespace gengine::core {

GlBufferObjectBase::GlBufferObjectBase(const TargetType target):
m_id(0),
m_target(TargetTypeToNative(target)) {
    glGenBuffers(1, &m_id);
}

GlBufferObjectBase::~GlBufferObjectBase() {
    clear();
}

GlBufferObjectBase::IdType GlBufferObjectBase::getId() const {
    return m_id;
}

void GlBufferObjectBase::fillImpl(const void* start, SizeType sizeInBytes, const UsageType usage) {
    glBufferData(m_target, sizeInBytes, start, UsageTypeToNative(usage));
}

void GlBufferObjectBase::bind() {
    glBindBuffer(m_target, m_id);
}

void GlBufferObjectBase::unbind() {
    glBindBuffer(m_target, 0);
}

void GlBufferObjectBase::clear() {
    if (m_id != 0) {
        glDeleteBuffers(1, &m_id);
        m_id = 0;
    }
}

} //! namespace gengine::core
