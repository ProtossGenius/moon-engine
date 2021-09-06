#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "error.h"
namespace oogl {

	void InitGlfw();
	void InitGlew();
	void InitImGui();
}
