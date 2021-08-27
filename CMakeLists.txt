cmake_minimum_required(VERSION 3.7)
project(Jump)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set this flag to true if you want to paly jumping with yourself
set(BODY_CONTROL true)
# Set this flag to true if you want to debug the code
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

if(BODY_CONTROL)
  add_definitions(-DBODY_CONTROL)
  message("BODY_CONTROL MODE: ON")
endif()

if(DEBUG)
  add_definitions(-DDEBUG)
  message("DEBUG MODE: ON")
  set (CMAKE_BUILD_TYPE Debug)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Og")
else()
  set (CMAKE_BUILD_TYPE Release) 
endif()


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
message("OpenCV found")
endif()

find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
message("SDL2 found")
endif()
include_directories(include ${SDL2_INCLUDE_DIRS} src)

file(GLOB SOURCE "src/*.cpp")

add_executable(Jump ${SOURCE})
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(Jump ${SDL2_LIBRARIES} ${OpenCV_LIBRARIES})
