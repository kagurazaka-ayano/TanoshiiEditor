cmake_minimum_required(VERSION 3.27)
project(TanoshiiEditor)
include(FetchContent)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)



file(GLOB SOURCES "src/*.cpp")
set(INCLUDE "include")
FetchContent_Declare(
    ncurses
    GIT_REPOSITORY https://github.com/mirror/ncurses.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(ncurses)

FetchContent_Declare(
    cdk 
    URL https://invisible-island.net/datafiles/release/cdk.tar.gz
)
FetchContent_MakeAvailable(cdk)

list(APPEND CMAKE_PREFIX_PATH "${cdk_SOURCE_DIR}/build")
list(APPEND CMAKE_PREFIX_PATH "${ncurses_SOURCE_DIR}/build")



list(APPEND INCLUDE ${cdk_SOURCE_DIR}/build/include)
list(APPEND INCLUDE ${ncurses_SOURCE_DIR}/build/include)

file(GLOB LIB "${ncurses_SOURCE_DIR}/build/lib/*.a")
list(APPEND LIB "${cdk_SOURCE_DIR}/build/lib/libcdk.a")

include_directories(${INCLUDE})

add_executable(${PROJECT_NAME} ${SOURCES})

if (NOT EXISTS ${cdk_SOURCE_DIR}/build)
    message("Building cdk")
    add_custom_target(cdk ALL
        COMMAND ./configure --prefix=${cdk_SOURCE_DIR}/build
        COMMAND make
        COMMAND make install
        WORKING_DIRECTORY ${cdk_SOURCE_DIR}
    )
    add_dependencies(${PROJECT_NAME} cdk)
endif()

if (NOT EXISTS ${ncurses_SOURCE_DIR}/build)
    message("Building ncurses")
    add_custom_target(ncurses ALL
        COMMAND ./configure --prefix=${ncurses_SOURCE_DIR}/build --enable-widec
        COMMAND make
        COMMAND make install
        WORKING_DIRECTORY ${ncurses_SOURCE_DIR}
    )
    add_dependencies(${PROJECT_NAME} ncurses)
endif()

set(RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin/debug)
set(RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/release)


link_libraries(${LIB})
