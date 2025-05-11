#include <random>
#include <memory>
#include <iostream>

#include "common/Color.h"
#include "common/Renderer.h"
#include "common/Time.h"

#ifdef __APPLE__
#include "platform/mac/MetalRenderer.h"
#include "platform/mac/MacWindow.h"
#else
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "platform/gl/OpenGLRenderer.h"
#endif

template <typename T>
T lerp(T a, T b, float t) {
    return a + t * (b - a);
}

int main() {
    const int width = 640;
    const int height = 480;

    void* nativeHandle = nullptr;

#ifdef __APPLE__
    nativeHandle = CreateMacWindow(width, height);
#else
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(width, height, "Graphics Engine", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create window\n";
        return -1;
    }

    glfwMakeContextCurrent(window);
    nativeHandle = window;
#endif

    std::unique_ptr<Renderer> renderer;

#ifdef __APPLE__
    renderer = std::make_unique<MetalRenderer>();
#else
    renderer = std::make_unique<OpenGLRenderer>();
#endif

    renderer->init(width, height, nativeHandle);

    float duration = 2.0f;
	double startTime = GetTimeSeconds();

    Color fromColor = Color::random();
    Color toColor = Color::random();

    while (
#ifdef __APPLE__
        true
#else
        !glfwWindowShouldClose(window)
#endif
    ) {
		double currentTime = GetTimeSeconds();
        float t = static_cast<float>((currentTime - startTime) / duration);
        if (t > 1.0f) t = 1.0f;

        Color interpolated{
            lerp(fromColor.r, toColor.r, t),
            lerp(fromColor.g, toColor.g, t),
            lerp(fromColor.b, toColor.b, t),
            1.0f
        };

        renderer->render(interpolated);
        renderer->present();

        if (t >= 1.0f) {
            fromColor = toColor;
            toColor = Color::random();
            startTime = currentTime;
        }

#ifdef __APPLE__
        RunMacEventLoopTick();
#else
        glfwPollEvents();
#endif
    }

    renderer->shutdown();

#ifndef __APPLE__
    glfwDestroyWindow(window);
    glfwTerminate();
#endif

    return 0;
}
