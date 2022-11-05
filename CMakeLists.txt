cmake_minimum_required(VERSION 3.7)

project(qmltreeview)

find_package(Qt5 REQUIRED COMPONENTS Quick Core Qml)

set(DEMO_TARGET_NAME demo)
set(PLUGIN_TARGET_NAME treeview)

add_subdirectory(plugin)
add_subdirectory(demo)

add_custom_target(PostBuild ALL DEPENDS ${DEMO_TARGET_NAME} ${PLUGIN_TARGET_NAME})

get_target_property(PLUGIN_SOURCE_DIR ${PLUGIN_TARGET_NAME} SOURCE_DIR)
get_target_property(DEMO_BINARY_DIR ${DEMO_TARGET_NAME} BINARY_DIR)

add_custom_command(
    TARGET PostBuild
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:treeview>
        ${DEMO_BINARY_DIR}/$<TARGET_FILE_NAME:treeview>
)

add_custom_command(
    TARGET PostBuild
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${PLUGIN_SOURCE_DIR}/qmldir
        ${DEMO_BINARY_DIR}/${PLUGIN_TARGET_NAME}/qmldir
)
