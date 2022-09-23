cmake_minimum_required(VERSION 3.0)

project(qmltreeview)

find_package(Qt5 REQUIRED COMPONENTS Quick Core Qml)

add_subdirectory(plugin)
add_subdirectory(test)
add_subdirectory(example)
