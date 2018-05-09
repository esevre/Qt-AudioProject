cmake_minimum_required(VERSION 3.11)
project(AudioProject)

set(CMAKE_CXX_STANDARD 17)

# Find components for Qt5
find_package(Qt5 REQUIRED COMPONENTS multimedia widgets)

# set variable to search include dir
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# tell CMake to use Qt's Automoc
set(CMAKE_AUTOMOC ON)

# find specific Qt packages we are using
find_package(Qt5Widgets)
find_package(Qt5Multimedia)

# build the executable
add_executable(AudioProject main.cpp AudioTools/AudioLevel.cpp AudioTools/AudioLevel.hpp)

# set the target link libraries
target_link_libraries(AudioProject Qt5::Widgets Qt5::Multimedia)
