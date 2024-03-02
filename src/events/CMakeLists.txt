find_package(PkgConfig REQUIRED)
# pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
pkg_check_modules(GTKMM gtkmm-4.0)

file(GLOB_RECURSE EVENT_FILES "*.h" "*.cpp")

add_library(
  events SHARED
    ${EVENT_FILES}
)

target_link_libraries(
  events
  PRIVATE
    ${GTKMM_LIBRARIES}
)

set_target_properties(events PROPERTIES LINKER_LANGUAGE CXX)

link_directories(
  ${GTKMM_LIBRARY_DIRS}
)

include_directories(
  ${GTKMM_INCLUDE_DIRS}
)
