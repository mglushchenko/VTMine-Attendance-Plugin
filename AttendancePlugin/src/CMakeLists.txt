cmake_minimum_required(VERSION 3.5)

project(AttendancePlugin LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_library(AttendancePlugin SHARED
  AttendancePlugin_global.h
  attendance_plugin.cpp
  attendance_plugin.h
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  person.h
  person.cpp
  attendance_model.h
  attendance_model.cpp
  date_picker.cpp
  date_picker.h
  date_picker.ui
  helpwindow.cpp
  helpwindow.h
  helpwindow.ui
)

#target_link_libraries(TestPlugin PRIVATE Qt5::Core)
target_link_libraries(AttendancePlugin Qt5::Widgets)

target_compile_definitions(AttendancePlugin PRIVATE ATTENDANCE_PLUGIN_LIBRARY)
