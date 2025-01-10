cmake_minimum_required(VERSION 3.10)

project(projekt_inf_2024)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

set(SOURCES
    src/main.cpp
    src/Game.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

target_include_directories(${PROJECT_NAME} PRIVATE /opt/homebrew/Cellar/sfml/2.6.1/include)
