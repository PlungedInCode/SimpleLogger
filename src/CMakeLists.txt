
# Add source files to the library
add_library(SimpleLogger
            Logger.cpp
            Logger.tpp)

# Include the "include" directory for header files
target_include_directories(SimpleLogger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
# Link the library with cxx_setup
target_link_libraries(SimpleLogger PUBLIC cxx_setup)
