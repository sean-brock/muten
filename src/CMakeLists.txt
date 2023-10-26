# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${mutenProject_SOURCE_DIR}/include/muten/*.hpp")

add_library(muten_library SHARED ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(muten_library PUBLIC ../include)
target_link_libraries(muten_library PRIVATE loguru::loguru)
target_compile_features(muten_library PUBLIC cxx_std_20)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
