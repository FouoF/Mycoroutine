cmake_minimum_required(VERSION 2.8)

project(Mycoroutine)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -g -std=c++17 -Wall -Wno-deprecated -Werror -Wno-unused-function")

MESSAGE(STATUS "Project: SERVER")

include_directories(.)
include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(LIB_SRC
    src/fiber.cpp
    src/thread.cpp
    src/scheduler.cpp
    src/IOmanager.cpp
)

add_library(mycoroutine SHARED ${LIB_SRC})

find_library(PTHREAD pthread)

set(LIBS
    ${PTHREAD}
)

add_executable(test tests/test.cpp)
add_dependencies(test mycoroutine)
target_link_libraries(test mycoroutine ${LIBS})

add_executable(test_thread tests/test_thread.cpp)
add_dependencies(test_thread mycoroutine)
target_link_libraries(test_thread mycoroutine ${LIBS})

add_executable(test_fiber tests/test_fiber.cpp)
add_dependencies(test_fiber mycoroutine)
target_link_libraries(test_fiber mycoroutine ${LIBS})

add_executable(test_scheduler tests/test_scheduler.cpp)
add_dependencies(test_scheduler mycoroutine)
target_link_libraries(test_scheduler mycoroutine ${LIBS})

add_executable(test_IOmanager tests/test_IOmanager.cpp)
add_dependencies(test_IOmanager mycoroutine)
target_link_libraries(test_IOmanager mycoroutine ${LIBS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)