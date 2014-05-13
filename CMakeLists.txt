cmake_minimum_required(VERSION 2.8.11)
project(LangProg)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

set(QT_LIBRARIES
	Qt5::Widgets
)

find_package(Qt5Widgets REQUIRED)

set(SFML_STATIC_VARIABLES TRUE)
find_package(SFML 2.1 COMPONENTS system window graphics audio REQUIRED)

find_package(Box2D REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
add_subdirectory(src)
