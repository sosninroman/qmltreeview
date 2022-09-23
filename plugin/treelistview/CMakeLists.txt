set(PLUGIN_NAME treelistview)

qt5_add_resources(RESOURCES ${CMAKE_CURRENT_LIST_DIR}/tree.qrc)

file(GLOB_RECURSE HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/src/*.h"
)

file(GLOB_RECURSE SOURCE
        "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
)

qt5_wrap_cpp(MOC_FILES ${HEADERS})

add_library(
    ${PLUGIN_NAME}
    SHARED
    ${HEADERS}
    ${SOURCE}
    ${MOC_FILES}
    ${CMAKE_CURRENT_LIST_DIR}/qmldir
    ${CMAKE_CURRENT_LIST_DIR}/plugin.qmltypes
    ${RESOURCES}
)

target_link_libraries(
    ${PLUGIN_NAME}
    PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Qml
)

target_compile_definitions(${PLUGIN_NAME} PRIVATE TREE_LIST_VIEW_EXPORT)
