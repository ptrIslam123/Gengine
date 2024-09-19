#include "include/core/primitives/vertex/vbo.h"

#include <glad/glad.h>

namespace gengine::core::primitives {

VertexBufferObject::VertexBufferObject():
GlBufferObjectBase(TargetType::ArrayBuffer) {}

VertexBufferObject::~VertexBufferObject() {
    clear();
}

void VertexBufferObject::fill(std::span<VertexType> data, UsageType usage) {
    GlBufferObjectBase::fill(data, usage);
}

void VertexBufferObject::fill(std::span<const VertexType> data, UsageType usage) {
    GlBufferObjectBase::fill(data, usage);
}

} //! namespace gengine::core::primitives
