#include "GraphicsPlotItem.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsView>
namespace ImPlot
{
void ShowDemoWindow(bool *p_open);
}

namespace ImGui
{

}

int main(int argc, char *argv[])
{

    //    GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    //    // Setup Dear ImGui context
    //    IMGUI_CHECKVERSION();
    //    ImGui::CreateContext();
    //    ImGuiIO &io = ImGui::GetIO();
    //    (void)io;
    //    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    //    // Setup Dear ImGui style
    //    ImGui::StyleColorsDark();
    //    // ImGui::StyleColorsClassic();

    //    // Setup Platform/Renderer backends
    //    ImGui_ImplGlfw_InitForOpenGL(window, true);
    //    ImGui_ImplOpenGL3_Init("#version 130");

    //    bool my_tool_active;
    //    //    ImGui::CreateContext();
    //    //    ImGui::NewFrame();
    //    //    ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
    //    //    char buf[100];
    //    //    float f;
    //    //    ImGui::Text("Hello, world %d", 123);
    //    //    //    if (ImGui::Button("Save"))
    //    //    //        MySaveFunction();
    //    //    ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    //    //    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

    //    ImGui::ShowDemoWindow(&my_tool_active);
    // ImGui::EndFrame();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.show2DPolyItem();
    return a.exec();
}
