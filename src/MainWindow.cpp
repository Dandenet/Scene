#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "MainWindow.h"
#include "Renderer/ResourceManager.h"

MainWindow::MainWindow()
{
    Init();

    try {

        Renderer::ResourceManager& manager = Renderer::ResourceManager::GetResourceManager();
        auto shader = manager.GetShaderProgram("res/shaders/shader.vert",
                                               "res/shaders/shader.frag");

        shader->Use();
        shader->SetMat4(glm::perspective(45.0f, (GLfloat)1280 / (GLfloat)720, 1.0f, 150.0f), "u_proj");
        m_Scene.SetShader(shader);
        m_Scene.SetCamera(&m_Camera);

        auto model = manager.GetModel("res/objects/shop.obj");

        m_Scene.AddModel(model);

    }  catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        std::exit(0);
    }

    glEnable(GL_DEPTH_TEST);
}

MainWindow::~MainWindow()
{
    glfwDestroyWindow(m_pWindow);
    glfwTerminate();
}

void MainWindow::Show()
{
    while (!glfwWindowShouldClose(m_pWindow)) {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Scene.Update();

        Update();

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }
}

void MainWindow::Init()
{
    glfwInit();

    m_pWindow = glfwCreateWindow(1280, 720, "Scene", nullptr, nullptr);

    glfwMakeContextCurrent(m_pWindow);


    if(!gladLoadGL())
        throw std::runtime_error("Error in gladLoadGL()...");

    glfwSetWindowUserPointer(m_pWindow, this);
    glfwSetCursorPosCallback(m_pWindow, &MainWindow::CursorPositionCallback);
    glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void MainWindow::Update()
{
    if (glfwGetKey(m_pWindow, GLFW_KEY_A) == GLFW_PRESS)
        m_Camera.MoveLeft();

    if (glfwGetKey(m_pWindow, GLFW_KEY_D) == GLFW_PRESS)
        m_Camera.MoveRight();

    if (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS)
        m_Camera.MoveForward();

    if (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS)
        m_Camera.MoveBackward();

    if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_pWindow, true);

}

void MainWindow::CursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
{
    MainWindow* win = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));
    win->m_Camera.Rotate(xpos, ypos);
}

