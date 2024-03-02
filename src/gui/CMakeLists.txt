find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-4.0)

file(GLOB_RECURSE GUI_SOURCES "*.cpp")
file(GLOB_RECURSE GUI_HEADERS "*.h")

add_library(
  gui SHARED
    ${GUI_SOURCES} ${GUI_HEADERS}
)

target_link_libraries(
  gui
  PRIVATE
    ${GTKMM_LIBRARIES}
)

target_include_directories(
  gui
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

link_directories(
    ${GTKMM_LIBRARY_DIRS}  )

include_directories(
    ${GTKMM_INCLUDE_DIRS}  )
