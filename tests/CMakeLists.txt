find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES
        "./*.cpp"
        )

file(GLOB_RECURSE HEADERS
        "./*.h"
        )

get_target_property(PLUGIN_SOURCE_DIR ${PLUGIN_TARGET_NAME} SOURCE_DIR)
include_directories(${PLUGIN_SOURCE_DIR})
include_directories(./)

add_executable(treemodel_test ${SOURCES} ${HEADERS})

set_target_properties(treemodel_test PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 17
  COMPILE_OPTIONS "-Wno-c++98-compat;"
)

target_link_libraries(treemodel_test ${GTEST_BOTH_LIBRARIES} treeview Qt5::Core Qt5::Quick Qt5::Qml)

install(TARGETS treemodel_test RUNTIME DESTINATION tests)

enable_testing()
add_test(NAME treemodel_test COMMAND treemodel_test)
