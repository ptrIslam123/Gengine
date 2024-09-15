#ifndef CORE_VERTEXT_ARRAY_OBJECT_H
#define CORE_VERTEXT_ARRAY_OBJECT_H

#include <span>

namespace gengine::core {

class VertexArrayObject final {
public:
    using IdType = unsigned int;

    explicit VertexArrayObject();
    ~VertexArrayObject();

    IdType getId() const;
    template<typename T>
    void setVertexeAttributes(
            unsigned int index,
            unsigned int componetSize,
            unsigned int stride = 0
    );
    void bind();
    void unbind();
    void clear();

private:
    enum class Type {
        Float, Integer, UnsignedInteger,
    };

    void setVertexeAttributesImpl(
            unsigned int index,
            unsigned int componetSize,
            unsigned int stride,
            Type type
    );

    IdType m_id;
};

template<>
inline void VertexArrayObject::setVertexeAttributes<int>(unsigned int index, unsigned int componetSize, unsigned int stride) {
    setVertexeAttributesImpl(index, componetSize, stride, Type::Integer);
}

template<>
inline void VertexArrayObject::setVertexeAttributes<unsigned int>(unsigned int index, unsigned int componetSize, unsigned int stride) {
    setVertexeAttributesImpl(index, componetSize, stride, Type::UnsignedInteger);
}

template<>
inline void VertexArrayObject::setVertexeAttributes<float>(unsigned int index, unsigned int componetSize, unsigned int stride) {
    setVertexeAttributesImpl(index, componetSize, stride, Type::Float);
}

} //! namespace gengine::core

#endif //! CORE_VERTEXT_ARRAY_OBJECT_H
