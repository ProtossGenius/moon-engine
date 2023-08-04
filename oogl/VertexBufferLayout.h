#pragma once
#include "Renderer.h"
#include <GL/glew.h>
#include <vector>
namespace oogl {
struct VertexBufferElement {
    unsigned int  type;
    unsigned int  count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        }
        ASSERT(false);
        return 0;
    }
};
namespace PushHelper {
template <typename T>
inline void Push(unsigned int                      count,
                 std::vector<VertexBufferElement> &m_Elements,
                 unsigned int                     &m_Stride) {
    throw std::runtime_error("should not call default Push function");
}
template <>
inline void Push<float>(unsigned int                      count,
                        std::vector<VertexBufferElement> &m_Elements,
                        unsigned int                     &m_Stride) {
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template <>
inline void Push<unsigned int>(unsigned int                      count,
                               std::vector<VertexBufferElement> &m_Elements,
                               unsigned int                     &m_Stride) {
    m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template <>
inline void Push<unsigned char>(unsigned int                      count,
                                std::vector<VertexBufferElement> &m_Elements,
                                unsigned int                     &m_Stride) {
    m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}
} // namespace PushHelper

class VertexBufferLayout {
  private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int                     m_Stride;

  public:
    VertexBufferLayout()
        : m_Stride(0) {}
    ~VertexBufferLayout() {}

    template <typename T> void Push(unsigned int count) {
        PushHelper::Push<T>(count, m_Elements, m_Stride);
    }
    inline const std::vector<VertexBufferElement> GetElements() const {
        return m_Elements;
    }
    inline unsigned int GetStride() const { return m_Stride; }
};

} // namespace oogl
