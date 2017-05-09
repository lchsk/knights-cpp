cmake_minimum_required(VERSION 2.6)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(knights)

# Set version information in a config.h file
#set(myproject_VERSION_MAJOR 1)
#set(myproject_VERSION_MINOR 0)
#configure_file(
#  "${PROJECT_SOURCE_DIR}/config.h.in"
#  "${PROJECT_BINARY_DIR}/config.h"
#  )

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories("${PROJECT_BINARY_DIR}")

message(STATUS "CMAKE_SYSTEM_NAME          = ${CMAKE_SYSTEM_NAME}"         )
message(STATUS "CMAKE_CXX_COMPILER_ID      = ${CMAKE_CXX_COMPILER_ID}"     )
message(STATUS "CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "CMAKE_COMPILER_IS_GNUCXX   = ${CMAKE_COMPILER_IS_GNUCXX}"  )

set(EXECUTABLE_NAME "knights")

add_definitions(-std=c++14 -O0)

add_executable(${EXECUTABLE_NAME}
    src/main.cpp
    src/game.cpp
    src/resource_mgr.cpp
    src/graph.cpp
    src/map.cpp
    src/level.cpp
    src/tile.cpp
    src/game_window.cpp
    src/animation.cpp
    src/spritesheet.cpp
    src/object_template.cpp
    src/object_library.cpp
    src/object.cpp
    src/unit_template.cpp
    src/unit_library.cpp
    # src/map_object.h
    src/unit.cpp
    src/nation.cpp
    src/data_loader.cpp
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
