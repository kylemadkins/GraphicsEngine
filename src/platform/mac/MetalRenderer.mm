#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

#import "MetalRenderer.h"

@interface MetalInternal : NSObject
@property(strong) id<MTLDevice> device;
@property(strong) id<MTLCommandQueue> commandQueue;
@property(strong) CAMetalLayer *layer;
@end

@implementation MetalInternal
@end

void MetalRenderer::init(int width, int height, void *nativeWindowHandle) {
  MetalInternal *m = [[MetalInternal alloc] init];
  m.device = MTLCreateSystemDefaultDevice();
  m.commandQueue = [m.device newCommandQueue];

  // Ensure that nativeWindowHandle is an NSWindow
  NSWindow *window = (__bridge NSWindow *)nativeWindowHandle;
  if (![window isKindOfClass:[NSWindow class]]) {
    // Replaced std::cerr with NSLog for Objective-C
    NSLog(@"Error: nativeWindowHandle is not an NSWindow!");
    return;
  }

  // Get the content view of the window (NSView)
  NSView *view = window.contentView;
  if (![view isKindOfClass:[NSView class]]) {
    // Replaced std::cerr with NSLog for Objective-C
    NSLog(@"Error: contentView is not an NSView!");
    return;
  }

  m.layer = [CAMetalLayer layer];
  m.layer.device = m.device;
  m.layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
  m.layer.framebufferOnly = YES;
  m.layer.frame = view.bounds;

  // Attach the Metal layer to the content view
  view.layer = m.layer;
  view.wantsLayer = YES;

  internal = (__bridge void *)m;
}

void MetalRenderer::render(const Color &clearColor) {
  MetalInternal *m = (__bridge MetalInternal *)internal;

  id<CAMetalDrawable> drawable = [m.layer nextDrawable];
  if (!drawable)
    return;

  MTLRenderPassDescriptor *pass =
      [MTLRenderPassDescriptor renderPassDescriptor];
  pass.colorAttachments[0].texture = drawable.texture;
  pass.colorAttachments[0].loadAction = MTLLoadActionClear;
  pass.colorAttachments[0].storeAction = MTLStoreActionStore;
  pass.colorAttachments[0].clearColor = MTLClearColorMake(
      clearColor.r, clearColor.g, clearColor.b, clearColor.alpha);

  id<MTLCommandBuffer> commandBuffer = [m.commandQueue commandBuffer];
  id<MTLRenderCommandEncoder> encoder =
      [commandBuffer renderCommandEncoderWithDescriptor:pass];
  [encoder endEncoding];
  [commandBuffer presentDrawable:drawable];
  [commandBuffer commit];
}

void MetalRenderer::present() {}

void MetalRenderer::shutdown() {
  CFRelease(internal);
  internal = nullptr;
}
