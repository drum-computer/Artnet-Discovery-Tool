cmake_minimum_required(VERSION 3.16)

project(artnet_discovery_tool VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.2 COMPONENTS Quick Network QuickControls2 REQUIRED)

add_subdirectory(src/app)
