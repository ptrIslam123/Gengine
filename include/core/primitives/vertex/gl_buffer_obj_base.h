#ifndef CORE_GL_BUFFER_OBJ_BASE_H
#define CORE_GL_BUFFER_OBJ_BASE_H

#include <span>
#include <type_traits>

namespace gengine::core {

class GlBufferObjectBase {
public:
    using IdType = unsigned int;

    enum class TargetType {
        ArrayBuffer,
        ElementArrayBuffer,
    };

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

    explicit GlBufferObjectBase(TargetType target);
    ~GlBufferObjectBase();

    IdType getId() const;
    template<typename T>
    void fill(std::span<T> data, UsageType usage = UsageType::StaticDraw);
    template<typename T>
    void fill(std::span<const T> data, UsageType usage = UsageType::StaticDraw);
    void bind();
    void unbind();
    void clear();

private:
    using SizeType = std::span<int>::size_type;
    void fillImpl(const void* start, SizeType sizeInBytes, UsageType usage);

    IdType m_id;
    const unsigned int m_target;
};

template<typename T>
inline void GlBufferObjectBase::fill(std::span<T> data, const UsageType usage) {
    static_assert(std::is_trivial_v<T>, "Data type must be trivial");
    fillImpl(static_cast<const void*>(data.data()), data.size() * sizeof(T), usage);
}

template<typename T>
inline void GlBufferObjectBase::fill(std::span<const T> data, const UsageType usage) {
    static_assert(std::is_trivial_v<T>, "Data type must be trivial");
    fillImpl(static_cast<const void*>(data.data()), data.size() * sizeof(T), usage);
}

} //! namespace gengine::core

#endif //! CORE_GL_BUFFER_OBJ_BASE_H
