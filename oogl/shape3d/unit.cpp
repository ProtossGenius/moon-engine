#include "oogl/shape3d/unit.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

namespace oogl {
namespace s3d {
glm::mat4 Unit::getTransform(const glm::vec3 &envScale) {
    glm::mat4 trans = glm::mat4(1.0f);

    trans   = glm::translate(trans, {m_position.x, m_position.y, m_position.z});
    float x = m_rotation.x;
    float y = m_rotation.y;
    float z = m_rotation.z;
    if (x != 0) {
        trans =
            glm::rotate(trans, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (y != 0) {
        trans =
            glm::rotate(trans, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (z != 0) {
        trans =
            glm::rotate(trans, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
    }
    trans = glm::scale(trans, envScale);
    trans = glm::scale(trans, m_scale);

    return trans;
}
} // namespace s3d
} // namespace oogl
