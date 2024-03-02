find_package(PkgConfig REQUIRED)
# pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
pkg_check_modules(GTKMM gtkmm-4.0)
find_package(Fontconfig REQUIRED)

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
    ${GTKMM_LIBRARIES}
    Fontconfig::Fontconfig
    draw
    events
    # gui
)

target_include_directories(
  app
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

link_directories(
  ${GTKMM_LIBRARY_DIRS}
)

include_directories(
  ${GTKMM_INCLUDE_DIRS}
)
