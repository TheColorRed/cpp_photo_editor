cmake_minimum_required(VERSION 3.16)
project(draw VERSION 1.0.0 LANGUAGES CXX C)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY bin)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
  BEFORE
  SYSTEM
    "C:\\msys64\\ucrt64\\include\\c++\\13.2.0"
)

# Shared libraries
add_subdirectory(src/lib)
add_subdirectory(src/gui)
add_subdirectory(src/events)

# Applications
add_subdirectory(src/cli)
add_subdirectory(src/app)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
set(CPACK_CMAKE_GENERATOR "NSIS")
include(CPack)
