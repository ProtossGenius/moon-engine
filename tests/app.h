#include "oogl/init.h"

#include "oogl/Managers.h"
#include "oogl/Window.h"
#include "tests/TestCamera.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include <fstream>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <iostream>
#include <sstream>
#include <string>
namespace test {
int run(int argc, const char *argv[]) {
    using namespace std;
    auto owin = std::shared_ptr<oogl::Window>(
        new oogl::Window(960, 540, "Hello World"));
    auto &mgr     = oogl::getTextureMgr();
    auto  texture = std::make_shared<oogl::Texture>("res/textures/text.jpg",
                                                   true, 0xfff6f6f6, 30);
    mgr.set("res/textures/text.jpg", texture);
    {
        std::cout << glGetString(GL_VERSION) << std::endl;

        ImGui::StyleColorsDark();

        Test     *currentTest = nullptr;
        TestMenu *testMenu    = new TestMenu(currentTest, owin);
        currentTest           = testMenu;

        testMenu->RegisterTest<TestClearColor>("Clear Color");
        testMenu->RegisterTest<TestTexture2D>("Texture2D");
        testMenu->RegisterTest<TestCamera>("Camera");
        /* Loop until the user closes the window */
        while (!owin->shouldClose()) {
            owin->clear();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (currentTest) {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("123");
                if (currentTest != testMenu && ImGui::Button("<-")) {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }

            // Rendering
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            owin->swapBuffers();

            /* Poll for and process events */
            glfwPollEvents();
        }
        if (currentTest != testMenu) {
            delete testMenu;
        }
        delete currentTest;
    }

    return 0;
}
} // namespace test
