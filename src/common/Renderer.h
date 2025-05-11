#pragma once

#include "Color.h"

class Renderer {
public:
    virtual void init(int width, int height, void* nativeWindowHandle) = 0;
    virtual void render(const Color& clearColor) = 0;
    virtual void present() = 0;
    virtual void shutdown() = 0;
    virtual ~Renderer() {}
};
