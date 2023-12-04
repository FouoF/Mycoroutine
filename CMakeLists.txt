cmake_minimum_required(VERSION 3.8)

project(Mycorutine VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIERED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

macro(add_msvc_options target)
 if(MSVC)
 target_compile_option(${target} PRIVATE
 /W4
 /WX
 /MP
 /permissive-
 )
 endif()
endmacro()

include_directories(.)
include_directories(/Mycorutine/src)
link_directories(/Mycorutine/lib)

set(LIB_SRC
    src/Fiber.cpp
    src/Thread.cpp
    )

add_library(src SHARED ${LIB_SRC})
force_redefine_file_macro_for_source{src}

find_library(PTHREAD pthread)
set(LIBS
    pthread
    )

message("***", ${LIBS})

add_executable(test tests/test.cpp)




