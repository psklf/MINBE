cmake_minimum_required(VERSION 3.3)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-Wall ")

project(minbe)

# thirdParty
include_directories(thirdparty)
# eigen
include_directories(thirdparty/eigen)

# include dirs
set(DESKTOP_PLATFORM Linux Windows Darwin)
if (CMAKE_SYSTEM_NAME IN_LIST DESKTOP_PLATFORM)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/drivers/gl/thirdparty/glad/include)
  message("glad dir " ${CMAKE_CURRENT_SOURCE_DIR}/drivers/gl/thirdparty/glad/include)
endif ()
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(src)

# lib minbe
set(driver_files drivers/gl/opengl_driver.cc drivers/gl/thirdparty/glad/src/glad.c)
set(engine_srcs src/minbe_api.cc
  src/pass.cc src/renderable.cc src/scene.cc
  src/modules/log/log.cc
  ${driver_files})

add_library(minbe ${engine_srcs})

if (CMAKE_SYSTEM_NAME STREQUAL "Android")
  target_link_libraries(minbe gles3 log)
endif ()

