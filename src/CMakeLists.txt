add_executable(3d 3d.cpp mesh.cpp icosahedron.cpp sphere.cpp cube.cpp cylinder.cpp monkeybars.cpp)
target_link_libraries(3d ${OPENGL_LIBRARIES} glfw)
