# sudo apt install libglfw3 libglew-dev glew-utils libglew2.0 assimp-utils libassimp-dev libassimp3v5 freeglut3-dev

cmake_minimum_required(VERSION 3.2)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Og -Wall -Wextra")
project(opengl_assignment)
# include_directories("src/")
add_executable(parkviewer parkviewer.cpp "src/shader.cpp" "src/Camera.cpp" "src/utilities.cpp" "src/mesh.cpp" "src/icosahedron.cpp" "src/sphere.cpp" "src/cube.cpp" "src/cylinder.cpp" "src/monkeybars.cpp" "src/seesaw.cpp" "src/slide.cpp" "src/scene.cpp" "src/grass.cpp")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/ColorFragmentShader.fragmentshader
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/TransformVertexShader.vertexshader
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/swing_frame.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/swing_seat.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/1simple_round.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/coaster_cart.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/coaster_glasses.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/coaster_head.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/coaster_mouth.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/coaster_track1.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/coaster_track2.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/coaster_track3.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(parkviewer ${OPENGL_LIBRARIES} glfw GLEW assimp dl)
add_subdirectory(src)
