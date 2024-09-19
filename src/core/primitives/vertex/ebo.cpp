#include "include/core/primitives/vertex/ebo.h"

#include <glad/glad.h>

namespace gengine::core::primitives {

ElementBufferObject::ElementBufferObject():
GlBufferObjectBase(TargetType::ElementArrayBuffer) {}

ElementBufferObject::~ElementBufferObject() {
    clear();
}

void ElementBufferObject::fill(std::span<IndexType> data, UsageType usage) {
    GlBufferObjectBase::fill(data, usage);
}

void ElementBufferObject::fill(std::span<const IndexType> data, UsageType usage) {
    GlBufferObjectBase::fill(data, usage);
}

} //! namespace gengine::core::primitives
