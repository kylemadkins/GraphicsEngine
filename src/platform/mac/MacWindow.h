#pragma once

#ifdef __APPLE__

void* CreateMacWindow(int width, int height);
void  RunMacEventLoopTick();
bool isWindowClosed();

#endif
