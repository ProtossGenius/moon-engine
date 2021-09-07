#include "Window.h"
#include "error.h"
#include "glm/gtc/matrix_transform.hpp"
#include "init.h"
#include <imgui/imgui_impl_glfw.h>
#include <map>
namespace oogl {
static std::map<uint64_t, Window *> winRegs;

Window::Window(int width, int height, const char *title, GLFWmonitor *monitor,
               GLFWwindow *share)
    : m_drawProj(
          glm::ortho(0.0f, float(width), 0.0f, float(height), -1.0f, 1.0f))
    , m_drawView(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
    , m_scale(1.0f, 1.0f, 1.0f)
    , m_window(nullptr)
    , m_swapInterval(1)
    , m_width(width)
    , m_height(height)
    , m_designWidth(width)
    , m_designHeight(height)
    , m_KeyMouse(smgame::nil<KeyMouseItf>()) {
    InitGlfw();
    m_window = glfwCreateWindow(width, height, title, monitor, share);

    if (!m_window) {
        throw error(ErrorEnum::ErrInit, "glfwCreateWindow");
    }
    winRegs[ uint64_t(m_window) ] = this;
    m_KeyMouse->CursorPosition(1, 2);
    winRegs[ uint64_t(m_window) ]->CursorPosition(1, 2);
    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);
    glfwSetWindowSizeCallback(m_window,
                              [](GLFWwindow *win, int width, int height) {
                                  auto window = winRegs[ uint64_t(win) ];
                                  window->resize(width, height);
                              });
    glfwSetMouseButtonCallback(
        m_window, [](GLFWwindow *win, int button, int action, int mods) {
            auto window = winRegs[ uint64_t(win) ];
            window->MouseButton(button, action, mods);
        });
    glfwSetCursorPosCallback(m_window, [](GLFWwindow *win, double x, double y) {
        auto window = winRegs[ uint64_t(win) ];
        window->CursorPosition(x, y);
    });
    glfwSetKeyCallback(m_window, [](GLFWwindow *win, int key, int scancode,
                                    int action, int mode) {
        auto window = winRegs[ uint64_t(win) ];
        window->KeyBoards(key, scancode, action, mode);
    });

    glfwSetScrollCallback(m_window,
                          [](GLFWwindow *win, double, double offsetY) {
                              auto window = winRegs[ uint64_t(win) ];
                              window->MouseScroll(offsetY);
                          });

    InitGlew();
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    useThis();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
}
void Window::useThis() {
    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    glfwSwapInterval(m_swapInterval);
}
void Window::clear() {
    GLCall(glClearColor(m_cRed, m_cGreen, m_cBlue, m_cAlpha));
    m_renderer.Clear();
}
void Window::run() {
    while (!shouldClose()) {
        this->clear();
        m_KeyMouse->Update();
        swapBuffers();
        /* Poll for and process events */
        glfwPollEvents();
    }
}

void Window::resize(int width, int height) {
    m_width  = width;
    m_height = height;
    using namespace std;
    cout << " resize (" << width << ", " << height << ")" << endl;
    m_drawProj =
        glm::ortho(0.0f, float(width), 0.0f, float(height), -1.0f, 1.0f);
    m_scale = {float(width) / float(m_designWidth),
               float(height) / float(m_designHeight), 1.0f};
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}
Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
}

} // namespace oogl
