#pragma once

#include "../../common/Renderer.h"

#ifdef __APPLE__

class MetalRenderer : public Renderer {
private:
    void* internal; // Forward-declared Objective-C++ impl
public:
    void init(int width, int height, void* nativeWindowHandle) override;
    void render(const Color& clearColor) override;
    void present() override;
    void shutdown() override;
};

#endif
