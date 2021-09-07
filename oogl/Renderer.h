#pragma once

#include <GL/glew.h>
#include <iostream>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

namespace oogl {

#define ASSERT(x)                                                              \
    if (!(x)) exit(-1);

#define GLCall(x)                                                              \
    CLClearError();                                                            \
    x;                                                                         \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void CLClearError();

bool GLLogCall(const char *function, const char *file, int line);

class Renderer {
  private:
  public:
    void            Clear() const;
    void            Draw(const VertexArray &va, const IndexBuffer &ib,
                         const Shader &shader) const;
    static Renderer Instance;
};

} // namespace oogl
