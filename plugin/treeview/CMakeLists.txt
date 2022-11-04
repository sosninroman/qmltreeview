qt5_add_resources(RESOURCES ${CMAKE_CURRENT_LIST_DIR}/${PLUGIN_TARGET_NAME}.qrc)

file(GLOB_RECURSE HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/src/*.h"
)

file(GLOB_RECURSE SOURCE
        "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
)

file(GLOB INSTALL_HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/src/*.h"
)
message(${INSTALL_HEADERS})
list(REMOVE_ITEM ${INSTALL_HEADERS} ${CMAKE_CURRENT_LIST_DIR}/src/plugin.h)

qt5_wrap_cpp(MOC_FILES ${HEADERS})

add_library(
    ${PLUGIN_TARGET_NAME}
    SHARED
    ${HEADERS}
    ${SOURCE}
    ${MOC_FILES}
    ${CMAKE_CURRENT_LIST_DIR}/qmldir
    ${CMAKE_CURRENT_LIST_DIR}/plugin.qmltypes
    ${RESOURCES}
)

target_compile_definitions(${PLUGIN_TARGET_NAME} PRIVATE TREE_VIEW_EXPORT)

target_link_libraries(
    ${PLUGIN_TARGET_NAME}
    PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Qml
)

install(TARGETS ${PLUGIN_TARGET_NAME} RUNTIME DESTINATION ${DEMO_TARGET_NAME})
install(FILES ${CMAKE_CURRENT_LIST_DIR}/qmldir
              ${CMAKE_CURRENT_LIST_DIR}/plugin.qmltypes
        DESTINATION ${DEMO_TARGET_NAME}/${PLUGIN_TARGET_NAME})
install(FILES ${INSTALL_HEADERS} DESTINATION include)
install(TARGETS ${PLUGIN_TARGET_NAME} RUNTIME DESTINATION plugin)
install(FILES ${CMAKE_CURRENT_LIST_DIR}/qmldir
              ${CMAKE_CURRENT_LIST_DIR}/plugin.qmltypes
        DESTINATION plugin/${PLUGIN_TARGET_NAME})
install(TARGETS ${PLUGIN_TARGET_NAME} ARCHIVE DESTINATION lib)
