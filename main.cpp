#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include "structures/s_azestar.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int, char**)
{
    //error callback
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) return 1;

    //creating window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Aze Star Simulator", nullptr, nullptr);
    ImVec4 clear_color = ImColor(114, 144, 154);
    glfwMakeContextCurrent(window);
    glewInit();
    ImGui_ImplGlfwGL3_Init(window, true);


    auto c = s_azestar();

    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplGlfwGL3_NewFrame();

        c.run_base();

        //rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();

    return 0;
}
