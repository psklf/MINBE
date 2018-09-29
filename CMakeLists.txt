cmake_minimum_required(VERSION 2.8)

set(srcs GlWindow.cpp GlUtils.cpp glad.c)

set(CMAKE_CXX_FLAGS "-Wall ")
add_executable(run.out ${srcs})
target_link_libraries(run.out -lglfw3 GL X11 pthread Xrandr Xxf86vm Xinerama Xcursor Xi dl)

