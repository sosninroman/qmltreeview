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

install(TARGETS ${DEMO_TARGET_NAME} DESTINATION ${DEMO_TARGET_NAME})
