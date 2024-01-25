file(GLOB_RECURSE EVT_SOURCES "*.cpp")
file(GLOB_RECURSE EVT_HEADERS "*.h")

add_library(
  events SHARED
    ${EVT_SOURCES} ${EVT_HEADERS}
)

set_target_properties(events PROPERTIES LINKER_LANGUAGE CXX)
