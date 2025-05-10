cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("GraphicsEngine")

add_subdirectory(external/glfw-3.4)

file(GLOB SOURCES src/*.h src/*.cpp src/**/*.h src/**/*.cpp external/glad/src/glad.c)

add_executable(GraphicsEngine ${SOURCES})

target_link_libraries(GraphicsEngine PRIVATE glfw)

target_include_directories(GraphicsEngine PRIVATE external/glfw-3.4/include external/glad/include)

set_target_properties(GraphicsEngine PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)
