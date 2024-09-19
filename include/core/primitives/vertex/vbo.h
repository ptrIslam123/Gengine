#ifndef CORE_VERTEXT_BUFFER_OBJECT_H
#define CORE_VERTEXT_BUFFER_OBJECT_H

#include "gl_buffer_obj_base.h"

#include <span>
#include <type_traits>

namespace gengine::core::primitives {

class VertexBufferObject final : public GlBufferObjectBase {
public:
    using VertexType = float;
    using IdType = GlBufferObjectBase::IdType;
    using TargetType = GlBufferObjectBase::TargetType;
    using UsageType = GlBufferObjectBase::UsageType;

    explicit VertexBufferObject();
    ~VertexBufferObject();

    void fill(std::span<VertexType> data, UsageType usage = UsageType::StaticDraw);
    void fill(std::span<const VertexType> data, UsageType usage = UsageType::StaticDraw);
};

} //! namespace gengine::core::primitives

#endif //! CORE_VERTEXT_BUFFER_OBJECT_H
