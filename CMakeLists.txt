cmake_minimum_required(VERSION 3.20)

project(triangulation)
include(FetchContent)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#find_package(SFML REQUIRED graphics system window)

set(SFML_VERSION 2.6.1)

# It's nice to get stripped-down release zips instead of cloning
# a repo and checking out a tag
FetchContent_Declare(
  SFML
  URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)
FetchContent_MakeAvailable(sfml)


file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

add_executable(triangulation_app main.cpp ${SOURCES} ${HEADERS})
target_include_directories(triangulation_app PUBLIC ./src)

target_link_libraries(triangulation_app sfml-graphics sfml-window sfml-system)
