file(GLOB_RECURSE COMPONENTS_SOURCES CONFIGURE_DEPENDS
    "./*.cpp"
    "./*.h"
)

qt_add_library(graphics STATIC
    ${COMPONENTS_SOURCES}
)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)


get_filename_component(PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)

target_link_libraries(graphics PRIVATE Qt6::Core Qt6::Widgets Qt6::Network Qt6::Gui)
target_include_directories(graphics INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
