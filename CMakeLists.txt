cmake_minimum_required(VERSION 3.0)

project(qmltreelistview)

find_package(Qt5 REQUIRED COMPONENTS Quick Core Qml)

add_subdirectory(plugin)
add_subdirectory(example)
