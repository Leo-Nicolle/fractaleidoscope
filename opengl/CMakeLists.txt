cmake_minimum_required(VERSION 2.8)

project(fractal)
add_executable(fractal main.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package( OpenCV REQUIRED )
find_package(GLEW REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
target_link_libraries(fractal ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${OpenCV_LIBS} ${GLEW_LIBRARIES})