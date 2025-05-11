#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>

static NSWindow* g_window = nil;
static bool g_windowClosed = false;

void* CreateMacWindow(int width, int height) {
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    [NSApp activateIgnoringOtherApps:YES];

    g_window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, width, height)
                                            styleMask:(NSWindowStyleMaskTitled |
                                                       NSWindowStyleMaskClosable |
                                                       NSWindowStyleMaskResizable)
                                              backing:NSBackingStoreBuffered
                                                defer:NO];
    if (!g_window) {
        NSLog(@"Error: Failed to create NSWindow.");
        return NULL;
    }

    [g_window setTitle:@"GraphicsEngine"];
    [g_window makeKeyAndOrderFront:nil];

    [[NSNotificationCenter defaultCenter] addObserverForName:NSWindowWillCloseNotification
                                                      object:g_window
                                                       queue:nil
                                                  usingBlock:^(NSNotification *note) {
                                                      g_windowClosed = true;
                                                  }];

    // Log window size for debugging
    NSLog(@"Window created with bounds: %@", NSStringFromRect([g_window frame]));

    return (__bridge void*)g_window;
}

void RunMacEventLoopTick() {
    NSEvent* event;
    while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                        untilDate:nil
                                           inMode:NSDefaultRunLoopMode
                                          dequeue:YES])) {
        [NSApp sendEvent:event];
    }
}

bool isWindowClosed() {
    return g_windowClosed;
}
