cmake_minimum_required(VERSION 3.7)

project(qmltreeview)

find_package(Qt5 REQUIRED COMPONENTS Quick Core Qml)

set(DEMO_TARGET_NAME demo)
set(PLUGIN_TARGET_NAME treeview)

add_subdirectory(plugin)
add_subdirectory(demo)
