find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

file(GLOB_RECURSE SRC_FILES "*.cpp")
file(GLOB_RECURSE H_FILES "*.h")

add_executable(
  app
    resources.c
    ${SRC_FILES}
    ${H_FILES}
)

target_link_libraries(
  app
  PRIVATE
    PkgConfig::GTK4
    gui
    draw
)

target_include_directories(
  app
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
