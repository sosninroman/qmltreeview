set(CMAKE_AUTOMOC ON)

qt5_add_resources(RESOURCES ${CMAKE_CURRENT_LIST_DIR}/${DEMO_TARGET_NAME}.qrc)

file(GLOB_RECURSE HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/*.h"
)

file(GLOB_RECURSE SOURCE
        "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
)

include_directories(${PROJECT_SOURCE_DIR}/plugin/treeview/)
link_directories(${CMAKE_BINARY_DIR}/plugin/treeview/)

add_executable(${DEMO_TARGET_NAME} ${HEADERS} ${SOURCE} ${RESOURCES})

target_link_libraries(${DEMO_TARGET_NAME} ${PLUGIN_TARGET_NAME} Qt5::Core Qt5::Quick Qt5::Qml)

add_custom_command(
    TARGET ${DEMO_TARGET_NAME}
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:treeview>
        $<TARGET_FILE_DIR:demo>/$<TARGET_FILE_NAME:treeview>
)

get_target_property(PLUGIN_SOURCE_DIR ${PLUGIN_TARGET_NAME} SOURCE_DIR)

add_custom_command(
    TARGET ${DEMO_TARGET_NAME}
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${PLUGIN_SOURCE_DIR}/qmldir
        $<TARGET_FILE_DIR:demo>/${PLUGIN_TARGET_NAME}/qmldir
)

install(TARGETS ${DEMO_TARGET_NAME} DESTINATION ${DEMO_TARGET_NAME})
