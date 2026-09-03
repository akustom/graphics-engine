cmake_minimum_required(VERSION 4.1)
project(3grav)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_Declare(
        boost
        URL https://archives.boost.io/release/1.92.0/source/boost_1_92_0.tar.gz
)
FetchContent_MakeAvailable(boost)


option( TRACY_ENABLE "" ON)

FetchContent_Declare(
        tracy
        GIT_REPOSITORY https://github.com/wolfpld/tracy.git
        GIT_TAG v0.14.1
)
FetchContent_MakeAvailable(tracy)


FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.5.1
)
FetchContent_MakeAvailable(glfw)


add_executable(3grav
        src/main.cpp
        src/glad.c

        src/engine/engine.cpp

        src/engine/window/window.cpp
        src/engine/window/fps.cpp
        src/engine/window/win_io.cpp
        src/engine/window/cursor_ctx.cpp

        src/engine/gfx/render_state.cpp
        src/engine/gfx/buffer/mesh_buffer.cpp
        src/engine/gfx/buffer/instances_buffer.cpp

        src/engine/geometry/camera.cpp
        src/engine/geometry/mesh.cpp

        src/engine/scene/camera.cpp
        src/engine/scene/instances.cpp
)


include_directories(include)

target_include_directories(3grav PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${boost_SOURCE_DIR})

target_link_libraries(3grav
        glfw
        Tracy::TracyClient
        OpenGL::GL
)

target_compile_definitions(3grav PRIVATE
        SOURCE_DIR="${CMAKE_SOURCE_DIR}/"
)