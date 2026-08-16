cmake_minimum_required(VERSION 4.1)
project(3grav)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)

include_directories(
        include
        tracy/public
)

option( TRACY_ENABLE "" ON)
add_subdirectory(tracy)

add_executable(3grav
        tracy/public/TracyClient.cpp
        src/main.cpp
        src/glad.c

        src/engine/window/window.cpp
        src/engine/window/fps.cpp
        src/engine/window/win_io.cpp
        src/engine/window/cursor_ctx.cpp

        src/engine/gfx/renderer.cpp

        src/engine/gfx/buffer/mesh_buffer.cpp
        src/engine/gfx/buffer/instances_buffer.cpp

        src/engine/geometry/camera.cpp
        src/engine/geometry/mesh.cpp

        src/engine/scene/camera.cpp
        src/engine/scene/instances.cpp
)

target_include_directories(3grav PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(3grav
        Tracy::TracyClient
        ${GLFW3_LIBRARY} OpenGL::GL
)

target_compile_definitions(3grav PRIVATE
        SOURCE_DIR="${CMAKE_SOURCE_DIR}/"
)