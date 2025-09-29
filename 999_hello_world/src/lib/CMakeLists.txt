# Create the header-only library FIRST
add_library(Vec3Lib INTERFACE)
target_include_directories(Vec3Lib INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

