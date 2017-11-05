cmake_minimum_required(VERSION 3.2)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Og -Wall -Wextra")
project(opengl_assignment)
include_directories("src/")
add_executable(3dviewer 3dviewer.cpp shader.cpp "src/utilities.cpp" "src/mesh.cpp" "src/icosahedron.cpp" "src/sphere.cpp" "src/cube.cpp" "src/cylinder.cpp" "src/monkeybars.cpp" "src/seesaw.cpp" "src/scene.cpp")

# add_executable(3dviewer 3dviewer.cpp shader.cpp "src/scene.cpp" )

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS})
target_link_libraries(3dviewer ${OPENGL_LIBRARIES} glfw GLEW assimp dl)
add_subdirectory(src)
