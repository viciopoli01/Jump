cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DEBUG true)

add_definitions(-std=c++17)


set(CXX_FLAGS "-Wall")
# enable threading
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(PLATFORM_SPECIFIC_LIBS "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

if(DEBUG)
  add_definitions(-DDEBUG)

  message("DEBUG MODE: ON")
  set (CMAKE_BUILD_TYPE Debug)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Og")
else()
  set (CMAKE_BUILD_TYPE Release) 
endif()


project(SnakeGym)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
find_package(SDL2 REQUIRED)
include_directories(include ${SDL2_INCLUDE_DIRS} src)

file(GLOB SOURCE "src/*.cpp")

add_executable(SnakeGym ${SOURCE})
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(SnakeGym ${SDL2_LIBRARIES} ${OpenCV_LIBRARIES})
