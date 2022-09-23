set(CMAKE_AUTOMOC ON)

qt5_add_resources(RESOURCES ${CMAKE_CURRENT_LIST_DIR}/example.qrc)

file(GLOB_RECURSE HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/*.h"
)

file(GLOB_RECURSE SOURCE
        "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
)

message(${CMAKE_BINARY_DIR}/plugin/treelistview/)

include_directories(${PROJECT_SOURCE_DIR}/plugin/treelistview/)
include_directories(${PROJECT_SOURCE_DIR}/test)
link_directories(${CMAKE_BINARY_DIR}/plugin/treelistview/)

add_executable(example ${HEADERS} ${SOURCE} ${RESOURCES})

target_link_libraries(example treelistview Qt5::Core Qt5::Quick Qt5::Qml)

