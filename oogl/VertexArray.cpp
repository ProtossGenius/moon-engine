#include "VertexArray.h"
#include "GL/glew.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
namespace oogl {
VertexArray::VertexArray() { GLCall(glGenVertexArrays(1, &m_RedererID)); }

VertexArray::~VertexArray() { GLCall(glDeleteVertexArrays(1, &m_RedererID)); }

void VertexArray::AddBuffer(const VertexBuffer &      vb,
                            const VertexBufferLayout &layout) {
    Bind();
    vb.Bind();
    const auto & elements = layout.GetElements();
    unsigned int offset   = 0;
    for (unsigned int i = 0; i < elements.size(); ++i) {
        const auto &element = elements[ i ];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type,
                                     element.normalized, layout.GetStride(),
                                     (const void *) (unsigned long) offset));
        offset +=
            element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const { GLCall(glBindVertexArray(m_RedererID)); }

void VertexArray::Unbind() const {}
} // namespace oogl
