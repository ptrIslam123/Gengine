#ifndef CORE_VERTEXT_BUFFER_OBJECT_H
#define CORE_VERTEXT_BUFFER_OBJECT_H

#include <span>

namespace gengine::core {

class VertexBufferObject final {
public:
    using IdType = unsigned int;

    enum class UsageType {
        StaticDraw, // Данные будут загружены один раз и использоваться много раз(Статические геометрические данные, такие как вершины фигур, которые не меняются).
        DynamicDraw, // Данные будут изменяться много раз и использоваться много раз(Геометрические данные, которые обновляются каждый кадр, например, анимация).
        StreamDraw, // Данные будут загружены один раз и использоваться несколько раз(Данные, которые обновляются каждый кадр, но используются только в текущем кадре).
        StaticRead, // Данные будут загружены один раз и использоваться для чтения(Данные, которые используются для чтения в шейдере, но не изменяются).
        DynamicRead, // Данные будут изменяться много раз и использоваться для чтения(Данные, которые обновляются каждый кадр и используются для чтения в шейдере.).
        StreamRead, // Данные будут загружены один раз и использоваться для чтения несколько раз(Данные, которые обновляются каждый кадр и используются для чтения только в текущем кадре.).
        StaticCopy, // Данные будут загружены один раз и использоваться для копирования(Данные, которые используются для копирования в другой буфер, но не изменяются).
        DynamicCopy, // Данные будут изменяться много раз и использоваться для копирования(Данные, которые обновляются каждый кадр и используются для копирования в другой буфер).
        StreamCopy, // Данные будут загружены один раз и использоваться для копирования несколько раз(Данные, которые обновляются каждый кадр и используются для копирования только в текущем кадре).
    };

    explicit VertexBufferObject();
    ~VertexBufferObject();

    IdType getId() const;
    template<typename T>
    void fill(std::span<T> data, UsageType usage = UsageType::StreamDraw);
    template<typename T>
    void fill(std::span<const T> data, UsageType usage = UsageType::StreamDraw);
    void bind();
    void unbind();
    void clear();

private:
    using SizeType = std::span<int>::size_type;
    void fillImpl(const void* start, SizeType sizeInBytes, UsageType usage);

    IdType m_id;
};

template<typename T>
inline void VertexBufferObject::fill(std::span<T> data, const UsageType usage) {
    fillImpl(data.data(), data.size() * sizeof(T), usage);
}

template<typename T>
inline void VertexBufferObject::fill(std::span<const T> data, const UsageType usage) {
    fillImpl(data.data(), data.size() * sizeof(T), usage);
}

} //! namespace gengine::core

#endif //! CORE_VERTEXT_BUFFER_OBJECT_H
