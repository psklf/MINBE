cmake_minimum_required(VERSION 3.3)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-Wall ")

project(pcexe)

# third party
# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/glfw/)
include_directories(thirdparty/glfw/include)

# minbe library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ minbe_binary)

# exe program
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../drivers/gl/thirdparty/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

find_package(OpenGL REQUIRED)

set(srcs pc_exe.cc)
add_executable(run.out ${srcs})

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_link_libraries(run.out minbe glfw GL X11 pthread Xrandr Xxf86vm Xinerama Xcursor Xi dl)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  target_link_libraries(run.out minbe glfw pthread dl)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_link_libraries(run.out minbe glfw dl)
endif ()



