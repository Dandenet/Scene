#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <GLFW/glfw3.h>

#include "Renderer/Scene.h"
#include "Renderer/Camera.h"

class MainWindow
{
public:
    MainWindow();
    MainWindow(const MainWindow&) = delete;
    MainWindow(MainWindow&&) = delete;
    ~MainWindow();
    MainWindow& operator= (const MainWindow&) = delete;
    MainWindow&& operator= (MainWindow&&) = delete;

    void Show();
private:

    GLFWwindow* m_pWindow;

    Renderer::Scene        m_Scene;
    Renderer::Camera       m_Camera;

    void Init();
    void Update();

    static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
};

#endif
