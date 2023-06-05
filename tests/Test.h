#pragma once
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "oogl/Window.h"
namespace test {

class Test {
  public:
    Test(std::shared_ptr<oogl::Window> window)
        : m_win(window) {}
    virtual ~Test() {}

    virtual void                  OnUpdate(float daltaTime) {}
    virtual void                  OnRender() {}
    virtual void                  OnImGuiRender() {}
    std::shared_ptr<oogl::Window> getWindow() { return m_win; }

  private:
    std::shared_ptr<oogl::Window> m_win;
};

class TestMenu : public Test {
  public:
    TestMenu(Test *&currentTestPointer, std::shared_ptr<oogl::Window> window);

    void OnImGuiRender() override;

    template <typename T> void RegisterTest(const std::string &name);

  private:
    Test                                                       *&m_currentTest;
    std::vector<std::pair<std::string, std::function<Test *()>>> m_Tests;
    std::shared_ptr<oogl::Window>                                m_win;
};

template <typename T>
inline void TestMenu::RegisterTest(const std::string &name) {
    std::shared_ptr<oogl::Window> win = getWindow();
    std::cout << "Registering test " << name << std::endl;
    m_Tests.push_back(std::make_pair(name, [ win ]() { return new T(win); }));
}

} // namespace test