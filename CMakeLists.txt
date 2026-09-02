cmake_minimum_required(VERSION 3.14)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
)
FetchContent_MakeAvailable(glm)

add_executable(LearnOpenGL
external/glad/glad.c
 #"src/window.cpp" "src/triangle.cpp" "src/exTriangle.cpp" "src/shaders.cpp" "src/texture.cpp" "src/transformation.cpp"
 #"src/Shader.h" "src/stb_image.h" 
 "src/coordinateSys.cpp")

target_include_directories(LearnOpenGL PRIVATE external/glad/include)
target_link_libraries(LearnOpenGL PRIVATE glfw glm::glm)

add_custom_command(
    TARGET LearnOpenGL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:LearnOpenGL>/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/textures $<TARGET_FILE_DIR:LearnOpenGL>/textures
)