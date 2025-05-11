cmake_minimum_required(VERSION 3.8)

project("GraphicsEngine")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_subdirectory(external/glfw-3.4)
set(OPEN_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE COMMON_SOURCES src/common/*.cpp src/common/*.h)

# Platform-specific sources and includes
if(APPLE)
  file(GLOB_RECURSE PLATFORM_SOURCES src/platform/mac/*.mm src/platform/mac/*.h)
  file(GLOB_RECURSE PLATFORM_INCLUDES)
else()
  file(GLOB_RECURSE PLATFORM_SOURCES src/platform/gl/*.cpp src/platform/gl/*.h external/glad/src/glad.c)
  file(GLOB_RECURSE PLATFORM_INCLUDES external/glfw-3.4/include external/glad/include)
endif()

add_executable(GraphicsEngine src/Main.cpp ${COMMON_SOURCES} ${PLATFORM_SOURCES})

target_include_directories(GraphicsEngine PRIVATE ${PLATFORM_INCLUDES})

if(APPLE)
  find_library(COCOA_FRAMEWORK Cocoa)
  find_library(QUARTZCORE_FRAMEWORK QuartzCore)
  find_library(METAL_FRAMEWORK Metal)
  find_library(METALKIT_FRAMEWORK MetalKit)

  target_link_libraries(GraphicsEngine PRIVATE
    ${COCOA_FRAMEWORK}
    ${QUARTZCORE_FRAMEWORK}
    ${METAL_FRAMEWORK}
    ${METALKIT_FRAMEWORK}
  )
else()
  target_link_libraries(GraphicsEngine PRIVATE glfw OpenGL::GL)
endif()

set_target_properties(GraphicsEngine PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)

# Ensure Objective-C++ is used for .mm files
if(APPLE)
  set_source_files_properties(${PLATFORM_SOURCES} PROPERTIES
    COMPILE_FLAGS "-x objective-c++"
  )
endif()
