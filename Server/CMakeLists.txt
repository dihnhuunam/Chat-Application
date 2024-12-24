cmake_minimum_required(VERSION 3.5)

project(Server LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "/home/dihnhuunam/Qt5.13.2/5.13.2/gcc_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

set(INC_DIR "${CMAKE_SOURCE_DIR}/Includes")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/Sources")
set(QRC "${CMAKE_SOURCE_DIR}/Resources/Resources.qrc")

file(GLOB SOURCES
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/Server/*.cpp
)

file(GLOB HEADERS
  ${INC_DIR}/Server/*.h
)

file(GLOB UIS
  ${SRC_DIR}/Server/*.ui
)

add_executable(${PROJECT_NAME}
  ${SOURCES}
  ${HEADERS}
  ${UIS}
  ${QRC}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Network)
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR}/Server)
