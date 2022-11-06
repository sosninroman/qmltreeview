cmake_minimum_required(VERSION 3.7)

project(qmltreeview)

find_package(Qt5 REQUIRED COMPONENTS Quick Core Qml)

set(DEMO_TARGET_NAME demo)
set(PLUGIN_TARGET_NAME treeview)
set(GTEST_LOCATION "" CACHE PATH "Google test library location")
set(BUILD_TESTS FALSE CACHE BOOLEAN "Build tests")

add_subdirectory(plugin)
add_subdirectory(demo)

if(${BUILD_TESTS})
    set(INSTALL_GTEST OFF)
    set(GTEST_ROOT ${GTEST_LOCATION})
    add_subdirectory(tests)
endif()

#Post build step
#On this step we copy plugin to build directory of demo and tests

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
