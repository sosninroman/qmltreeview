file(GLOB_RECURSE HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/*.h"
)

file(GLOB_RECURSE SOURCE
        "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
)



add_library(foo SHARED ${HEADERS} ${SOURCE})

target_compile_definitions(foo PRIVATE FOO_EXPORT)
