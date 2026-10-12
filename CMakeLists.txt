cmake_minimum_required(VERSION 3.21)
project(AIPlayer VERSION 0.2.0 LANGUAGES CXX)

# Build this project with a matching Geode SDK installed by Geode CLI.
# GEODE_SDK is supplied by the Geode build environment.
add_subdirectory(${GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
setup_geode_mod(${PROJECT_NAME})
