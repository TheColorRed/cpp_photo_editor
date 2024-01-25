find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

file(GLOB_RECURSE GUI_SOURCES "*.cpp")
file(GLOB_RECURSE GUI_HEADERS "*.h")

add_library(
  gui SHARED
    ${GUI_SOURCES} ${GUI_HEADERS}
)

target_link_libraries(
  gui
  PRIVATE
    PkgConfig::GTK4
)

target_include_directories(
  gui
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
