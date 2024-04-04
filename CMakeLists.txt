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

add_executable(${PROJECT_NAME} ${SOURCES})

if (NOT EXISTS ${cdk_SOURCE_DIR}/build)
    message("cdk not found, will be built")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E echo "Blocking CMake process until this is built"
        COMMAND ./configure --prefix=${cdk_SOURCE_DIR}/build
        WORKING_DIRECTORY ${cdk_SOURCE_DIR}
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
    )
    if(result)
        message(FATAL_ERROR "Configuration step for cdk failed: ${result}")
    else()
        message("Configuration step for cdk succeeded")
    endif()
    execute_process(
        COMMAND make
        WORKING_DIRECTORY ${cdk_SOURCE_DIR}
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
    )
    if(result)
        message(FATAL_ERROR "Build step for cdk failed: ${result}")
    else()
        message("Build step for cdk succeeded")
    endif()
    execute_process(
        COMMAND make install
        WORKING_DIRECTORY ${cdk_SOURCE_DIR}
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
    )
    if(result)
        message(FATAL_ERROR "Install step for cdk failed: ${result}")
    else()
        message("Install step for cdk succeeded")
    endif()
else()
    message("cdk already built")
endif()
list(APPEND LIB "${cdk_SOURCE_DIR}/build/lib/libcdk.a")

find_package(Curses REQUIRED)

list(APPEND INCLUDE ${CURSES_INCLUDE_DIR})
list(APPEND LIB ${CURSES_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE})
target_compile_definitions(${PROJECT_NAME} PRIVATE TERMINFO="${ncurses_SOURCE_DIR}/build/share/terminfo")

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/release
)
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB})
