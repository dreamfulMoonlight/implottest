#include "GL/glut.h"
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

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 160.0);
}
void lineSegment(void)
{

    GLint dataValue[12] = {452, 368, 214, 543, 328, 193, 322, 436, 257, 268, 473, 467};

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);

    glVertex2i(20, 20);  // y轴
    glVertex2i(20, 450);

    //    glVertex2i(15, 15);  // 100
    //    glVertex2i(30, 30);

    //    glVertex2i(30, 30);  // 200
    //    glVertex2i(45, 50);

    //    glVertex2i(45, 50);  // 300
    //    glVertex2i(55, 350);

    glVertex2i(10, 30);  // x轴
    glVertex2i(530, 30);

    glEnd();
    //    glPointSize(4.5);
    //    glColor3f(0.0, 0.0, 0.0);
    //    glBegin(GL_POINTS);

    //    for (int k = 0; k < 6; k++)
    //    {
    //        glVertex2i(120 + k * 70, dataValue[k]);
    //    }
    //    glEnd();

    glColor3f(0, 0, 1);
    glLineWidth(2);
    //绘制折线图
    glBegin(GL_LINE_STRIP);
    {
        for (int i = 0; i < 12; i++)
        {
            glVertex2i(i * 3 + 30, dataValue[i] / 20 + 20);
        }
    }
    glEnd();

    //    //polygon
    //    for (int k = 0; k < 6; k++)
    //    {
    //        glColor3f(0.0, 0.3, 0.7);
    //        glBegin(GL_POLYGON);

    //        glVertex2i(110 + k * 70, 50);
    //        glVertex2i(130 + k * 70, 50);
    //        glVertex2i(130 + k * 70, dataValue[k] - 40);
    //        glVertex2i(110 + k * 70, dataValue[k] - 40);

    //        glEnd();
    //    }

    glFlush();
}

void paintDialog(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(500, 200);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Example OpenGL Program");
    init();
    glutDisplayFunc(lineSegment);
    glutMainLoop();
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

    // paintDialog(argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    // w.showOpenglWidget();
    w.show2DPolyItem();
    w.show();
    return a.exec();
}
