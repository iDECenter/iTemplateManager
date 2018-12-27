cmake_minimum_required(VERSION 3.1.0)

project(iTemplateManager)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

aux_source_directory(. SRC)

add_executable(iTemplateManager WIN32 ${SRC})
target_link_libraries(iTemplateManager Qt5::Core Qt5::Widgets)
