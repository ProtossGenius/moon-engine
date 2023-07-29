#pragma once
#include <glm/glm.hpp>

namespace oogl {
class View {
  public:
    glm::vec3 &getView() { return _view; }

  private:
    glm::vec3 _view;
};
} // namespace oogl
