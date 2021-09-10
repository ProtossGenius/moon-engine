#include "init.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "error.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
namespace oogl {

const char *glsl_version = "#version 130";

struct GlfwInit {
    GlfwInit() {
        if (!glfwInit()) {
            throw error(ErrorEnum::ErrInit, "glfwInif");
        }
    }

    ~GlfwInit() {
        //@SMIST console.log("[warn] may cause some error, it should not in here.")
        glfwTerminate();
    }
};

void InitGlfw() { static GlfwInit it; }

struct GlewInit {
    GlewInit() {
        if (GLEW_OK != glewInit()) {
            throw error(ErrorEnum::ErrInit, "glewInit");
        }
    }
};

void InitGlew() { static GlewInit it; }

struct IMGuiInit {
    IMGuiInit() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        // Setup Dear ImGui style
        ImGui_ImplOpenGL3_Init(glsl_version);

#ifdef _WIN32
        ImFontConfig Config;
        Config.MergeMode = true;
        ImGuiIO &io      = ImGui::GetIO();
        io.Fonts->AddFontDefault();
        io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\simsun.ttc", 16.0f,
                                     &Config,
                                     io.Fonts->GetGlyphRangesChineseFull());
#endif // _WIN32
    }

    ~IMGuiInit() {
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
};

void InitImGui() { static IMGuiInit it; }
} // namespace oogl
