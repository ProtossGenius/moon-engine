#pragma once
namespace oogl {
class VertexBuffer {
  private:
    unsigned int m_RendererID;

  public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};

} // namespace oogl