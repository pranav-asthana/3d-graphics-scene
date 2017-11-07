cmake_minimum_required(VERSION 3.2)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Og -Wall -Wextra")
project(opengl_assignment)
include_directories("src/")
add_executable(3dviewer 3dviewer.cpp shader.cpp "src/utilities.cpp" "src/mesh.cpp" "src/icosahedron.cpp" "src/sphere.cpp" "src/cube.cpp" "src/cylinder.cpp" "src/monkeybars.cpp" "src/seesaw.cpp" "src/slide.cpp" "src/scene.cpp")
# configure_file("../ColorFragmentShader.fragmentshader" "./ColorFragmentShader.fragmentshader" COPYONLY)
# configure_file("../TransformVertexShader.vertexshader" "./TransformVertexShader.vertexshader" COPYONLY)
# add_executable(3dviewer 3dviewer.cpp shader.cpp "src/scene.cpp" )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ColorFragmentShader.fragmentshader
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/TransformVertexShader.vertexshader
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/swing_frame.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/swing_seat.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/1simple_round.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS})
target_link_libraries(3dviewer ${OPENGL_LIBRARIES} glfw GLEW assimp dl)
add_subdirectory(src)
