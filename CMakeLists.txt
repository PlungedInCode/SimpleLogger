# lib/SimpleLogger/CMakeLists.txt
add_library(SimpleLogger STATIC
    src/Logger.cpp
)

# Include directories for the library
target_include_directories(SimpleLogger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
