# <repo>/launcher/CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
project(Launcher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

set(LAUNCHER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/LauncherMain.cpp
)

if (WIN32)
  enable_language(RC)
  list(APPEND LAUNCHER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/AppIcon.rc)
  set(WIN32_ARG WIN32)
endif()

qt_add_executable(launcher ${WIN32_ARG} ${LAUNCHER_SOURCES})
target_link_libraries(launcher PRIVATE Qt6::Core Qt6::Network)

if (WIN32)
  if (TARGET Qt6::EntryPoint)
    target_link_libraries(launcher PRIVATE Qt6::EntryPoint)
  else()
    target_link_options(launcher PRIVATE -mwindows)
  endif()
endif()

qt_finalize_executable(launcher)

# El launcher debe terminar en la MISMA carpeta que frontend.exe
set(DEFAULT_OUT_DIR "${CMAKE_SOURCE_DIR}/dist/release")

if(DEFINED ENV{APP_OUT} AND NOT "$ENV{APP_OUT}" STREQUAL "")
  set(OUT_DIR "$ENV{APP_OUT}")
else()
  set(OUT_DIR "${DEFAULT_OUT_DIR}")
endif()

set_target_properties(launcher PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY                "${OUT_DIR}"
  RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${OUT_DIR}"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${OUT_DIR}"
  RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${OUT_DIR}"
  RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     "${OUT_DIR}"
)
