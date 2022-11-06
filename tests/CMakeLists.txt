find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS " -static -static-libgcc -static-libstdc++")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()


file(GLOB_RECURSE SOURCES
        "./*.cpp"
        )

file(GLOB_RECURSE HEADERS
        "./*.h"
        )

include_directories(./)

add_executable(treemodel_test ${SOURCES} ${HEADERS})

set_target_properties(treemodel_test PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 17
  COMPILE_OPTIONS "-Wno-c++98-compat;"
)

target_link_libraries(treemodel_test ${GTEST_BOTH_LIBRARIES} treeview)

install(TARGETS treemodel_test RUNTIME DESTINATION tests)

enable_testing()
add_test(NAME treemodel_test COMMAND treemodel_test)
