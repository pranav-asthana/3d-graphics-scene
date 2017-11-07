add_executable(3d 3d.cpp utilities.cpp mesh.cpp icosahedron.cpp sphere.cpp cube.cpp cylinder.cpp monkeybars.cpp seesaw.cpp slide.cpp scene.cpp)
add_executable(tst test.cpp utilities.cpp mesh.cpp icosahedron.cpp sphere.cpp cube.cpp cylinder.cpp monkeybars.cpp seesaw.cpp slide.cpp scene.cpp)
target_link_libraries(3d ${OPENGL_LIBRARIES} glfw)
target_link_libraries(tst ${OPENGL_LIBRARIES} glfw)
