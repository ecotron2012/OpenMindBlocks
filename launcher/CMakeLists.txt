# <repo>/launcher/CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
project(Launcher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/AppIcon.rc")
add_executable(launcher LauncherMain.cpp ${app_icon_resource_windows})
target_link_libraries(launcher PRIVATE Qt6::Core Qt6::Network)

# El launcher debe terminar en la MISMA carpeta que frontend.exe
set_target_properties(launcher PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist"
)

if(WIN32)
  set_target_properties(launcher PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
