file(GLOB_RECURSE COMPONENTS_SOURCES CONFIGURE_DEPENDS
    "./*.cpp"
    "./*.h"
)

qt_add_library(sound_player STATIC
    ${COMPONENTS_SOURCES}
)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network Multimedia)


get_filename_component(PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)

target_link_libraries(sound_player PRIVATE Qt6::Core Qt6::Multimedia)
target_include_directories(sound_player INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
