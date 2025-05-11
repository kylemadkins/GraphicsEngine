#pragma once

#include "../../common/Renderer.h"

class OpenGLRenderer : public Renderer {
public:
    void init(int width, int height, void* nativeWindowHandle) override;
    void render(const Color& clearColor) override;
    void present() override;
    void shutdown() override;
};
