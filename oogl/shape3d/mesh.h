#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "oogl/IndexBuffer.h"
#include "oogl/Renderer.h"
#include "oogl/VertexArray.h"
#include "oogl/VertexBuffer.h"
#include <memory>

namespace oogl {
class Window;
class Texture;
class Shader;

namespace s3d {
class Mesh {

  public:
    void add_trangel();
    void add_mesh(Mesh &&mesh);

  private:
};
} // namespace s3d

} // namespace oogl
