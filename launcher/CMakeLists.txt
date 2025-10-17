# <repo>/launcher/CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
project(Launcher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/AppIcon.ico")
add_executable(launcher LauncherMain.cpp ${app_icon_resource_windows})
target_link_libraries(launcher PRIVATE Qt6::Core Qt6::Network)

# El launcher debe terminar en la MISMA carpeta que frontend.exe
set_target_properties(launcher PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist"
)

if(WIN32)
  set_target_properties(launcher PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

set(OUT_DIR "$ENV{APP_OUT}")
if(NOT OUT_DIR)
  set(OUT_DIR "${CMAKE_SOURCE_DIR}/dist/release")
endif()

add_custom_command(TARGET launcher POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "${OUT_DIR}"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "$<TARGET_FILE:launcher>"  "${OUT_DIR}/launcher.exe"
)
