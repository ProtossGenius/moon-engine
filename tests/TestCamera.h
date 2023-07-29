#pragma once

#include "Test.h"

namespace test {
class TestCamera : public Test {
  public:
    TestCamera(std::shared_ptr<oogl::Window> window);
    ~TestCamera();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;

  private:
    float m_ClearColor[ 4 ];
};
} // namespace test
