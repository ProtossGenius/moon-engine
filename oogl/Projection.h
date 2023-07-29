#pragma once
#include <glm/glm.hpp>
namespace oogl {
class Projection {

  public:
    glm::vec3 &getProj() { return _proj; }

  private:
    glm::vec3 _proj;
};
} // namespace oogl
