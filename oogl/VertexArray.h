#pragma once

#include "VertexBuffer.h"
namespace oogl {
class VertexBufferLayout;

class VertexArray {
  private:
    unsigned int m_RedererID;

  public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

    void Bind() const;
    void Unbind() const;
};

} // namespace oogl