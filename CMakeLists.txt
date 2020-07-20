cmake_minimum_required(VERSION 3.9.5)
project(MyFileInfo VERSION 0.0.2)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Gui Core)

set(project_headers
  include/MyFileInfo/TextWindow.hpp
  include/MyFileInfo/File.hpp
  include/MyFileInfo/MainWindow.hpp
)

# moc the ui
qt5_wrap_ui(ui_wrap resources/MainWindow.ui)

# moc the headers
foreach(header "${project_headers}")
  qt5_wrap_cpp(moc_sources "${header}")
endforeach()

# add icon
qt5_add_resources(qt_resources resources/icon.qrc)

set(project_sources
  src/File.cpp
  src/main.cpp
  src/MainWindow.cpp
  src/TextWindow.cpp
)

include_directories(include ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}
  ${project_sources}
  ${project_headers}
  ${ui_wrap}
  ${moc_sources}
  ${qt_resources}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC Qt5::Widgets Qt5::Gui Qt5::Core
)
