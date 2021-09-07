#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "KeyMouse.h"
#include "Renderer.h"
#include "glm/glm.hpp"
namespace oogl {

class Window {
  public:
    Window(int width, int height, const char *title, GLFWmonitor *monitor,
           GLFWwindow *share);
    Window(int width, int height, const char *title)
        : Window(width, height, title, NULL, NULL) {}
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

  private: // Callback functions.
    void MouseButton(int button, int action, int mods) {
        m_KeyMouse->MouseButton(button, action, mods);
    }
    void CursorPosition(double x, double y) {
        m_KeyMouse->CursorPosition(x, y);
    }
    void KeyBoards(int key, int scancode, int action, int mode) {
        m_KeyMouse->KeyBoards(key, scancode, action, mode);
    }
    void MouseScroll(double offset) { m_KeyMouse->MouseScroll(offset); }

    void resize(int width, int height);

  public:
    void useThis();
    void setSwapInterval(int interval) { m_swapInterval = interval; }
    void setClearColor(GLclampf red, GLclampf green, GLclampf blue,
                       GLclampf alpha) {
        m_cRed   = red;
        m_cGreen = green;
        m_cBlue  = blue;
        m_cAlpha = alpha;
    }

    void clear();
    void setKeyMouseEvent(std::shared_ptr<KeyMouseItf> itf) {
        m_KeyMouse = itf;
    }
    bool shouldClose() const { return glfwWindowShouldClose(m_window); }

    GLFWwindow *window() { return m_window; }

    void run();
    void swapBuffers() { /* Swap front and back buffers */
        glfwSwapBuffers(m_window);
    }
    int width() { return m_width; }
    int height() { return m_height; }

    ~Window();

    const glm::mat4 &getDrawProj() const { return m_drawProj; }
    const glm::mat4 &getDrawView() const { return m_drawView; }
    const glm::vec3 &getScale() const { return m_scale; }

  private:
    glm::mat4   m_drawProj;
    glm::mat4   m_drawView;
    glm::vec3   m_scale;
    GLFWwindow *m_window;
    int         m_swapInterval;
    GLclampf    m_cRed = 0, m_cGreen = 0, m_cBlue = 1, m_cAlpha = 1;
    Renderer &  m_renderer = Renderer::Instance;
    int         m_width, m_height;
    const int   m_designWidth, m_designHeight;
    std::shared_ptr<KeyMouseItf> m_KeyMouse;
};
} // namespace oogl