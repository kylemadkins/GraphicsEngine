#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLRenderer.h"

void OpenGLRenderer::init(int width, int height, void* nativeWindowHandle) {
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, width, height);
}

void OpenGLRenderer::render(const Color& clearColor) {
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::present() {
    glfwSwapBuffers(static_cast<GLFWwindow*>(glfwGetCurrentContext()));
}

void OpenGLRenderer::shutdown() {}
