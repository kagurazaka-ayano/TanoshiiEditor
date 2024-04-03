cmake_minimum_required(VERSION 3.27)
project(TanoshiiEditor)
include(FetchContent)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "src/*.cpp")
set(INCLUDE "include")

FetchContent_Declare(
    cdk 
    URL https://invisible-island.net/datafiles/release/cdk.tar.gz
)
FetchContent_MakeAvailable(cdk)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(fmt)
list(APPEND LIB fmt::fmt)
list(APPEND INCLUDE ${cdk_SOURCE_DIR}/build/include)
list(APPEND INCLUDE ${fmt_SOURCE_DIR}/include)

list(APPEND LIB "${cdk_SOURCE_DIR}/build/lib/libcdk.a")
add_executable(${PROJECT_NAME} ${SOURCES})

if (NOT EXISTS ${cdk_SOURCE_DIR}/build)
    message("cdk not found, will be built")
    add_custom_target(cdk ALL
        COMMAND ./configure --prefix=${cdk_SOURCE_DIR}/build
        COMMAND make
        COMMAND make install
        WORKING_DIRECTORY ${cdk_SOURCE_DIR}
    )
    add_dependencies(${PROJECT_NAME} cdk)
else()
    message("cdk already built")
endif()

find_package(Curses REQUIRED)

list(APPEND INCLUDE ${CURSES_INCLUDE_DIR})
list(APPEND LIB ${CURSES_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE})
target_compile_definitions(${PROJECT_NAME} PRIVATE TERMINFO="${ncurses_SOURCE_DIR}/build/share/terminfo")

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB})

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/release
)
