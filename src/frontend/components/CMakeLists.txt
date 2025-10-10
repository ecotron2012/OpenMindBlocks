file(GLOB_RECURSE COMPONENTS_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

qt_add_library(components STATIC
    ${COMPONENTS_SOURCES}
)

get_filename_component(PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)

target_include_directories(components  # tu lib/target del módulo
    PUBLIC
        "${PARENT_DIR}/extern/json/single_include"   # queda .../extern/json/single_include
)


target_link_libraries(components PRIVATE Qt6::Core Qt6::Widgets nlohmann_json::nlohmann_json)
target_include_directories(components INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
