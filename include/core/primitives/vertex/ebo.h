#ifndef CORE_ELEMENT_BUFFER_OBJECT_H
#define CORE_ELEMENT_BUFFER_OBJECT_H

#include "gl_buffer_obj_base.h"

#include <span>
#include <type_traits>

namespace gengine::core::primitives {

class ElementBufferObject final : public GlBufferObjectBase {
public:
    using IndexType = unsigned int;
    using IdType = GlBufferObjectBase::IdType;
    using TargetType = GlBufferObjectBase::TargetType;
    using UsageType = GlBufferObjectBase::UsageType;

    explicit ElementBufferObject();
    ~ElementBufferObject();

    void fill(std::span<IndexType> data, UsageType usage = UsageType::StaticDraw);
    void fill(std::span<const IndexType> data, UsageType usage = UsageType::StaticDraw);
};

} //! namespace gengine::core::primitives

#endif //! CORE_ELEMENT_BUFFER_OBJECT_H
