# CMakeLists.txt
cmake_minimum_required(VERSION 3.5)

project(Client LANGUAGES CXX)

# Enable CMake tools
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify Qt installation path
list(APPEND CMAKE_PREFIX_PATH "/home/dihnhuunam/Qt5.13.2/5.13.2/gcc_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

# Add include directories
set(INC_DIR "${CMAKE_SOURCE_DIR}/Includes")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/Sources")

# Collect source files, headers, and UI files
file(GLOB SOURCES
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/Chatbox/*.cpp
)

file(GLOB HEADERS
  ${INC_DIR}/Chatbox/*.h
)

file(GLOB UIS
  ${SRC_DIR}/Chatbox/*.ui
)

# Add executable
add_executable(${PROJECT_NAME}
  ${SOURCES}
  ${HEADERS}
  ${UIS}  
)

# Link with Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Network)

# Ensure that the include directory is correctly set
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR}/Chatbox)
