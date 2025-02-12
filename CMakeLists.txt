cmake_minimum_required(VERSION 3.16)
project(hyperscan-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable position-independent code for shared libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Option to build shared or static library
option(BUILD_SHARED_LIBS "Build as shared library" ON)

# Locate Hyperscan Manually
find_library(HYPERSCAN_LIBRARY NAMES hs)
find_path(HYPERSCAN_INCLUDE_DIR NAMES hs/hs.h)

# If not found, print error
if (NOT HYPERSCAN_LIBRARY OR NOT HYPERSCAN_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find Hyperscan library. Install it and set HYPERSCAN_LIBRARY and HYPERSCAN_INCLUDE_DIR")
endif()

# Show found paths
message(STATUS "Hyperscan Library: ${HYPERSCAN_LIBRARY}")
message(STATUS "Hyperscan Include: ${HYPERSCAN_INCLUDE_DIR}")

# Source files for the wrapper library
set(HYPERSCAN_CPP_SOURCES
        src/PlatformInfo.cpp
        src/Pattern.cpp
        src/Literal.cpp
        src/MultiPattern.cpp
        src/MultiPatternExtended.cpp
        src/MultiLiteral.cpp
        src/ExpressionInfo.cpp
        src/Database.cpp
        src/Scratch.cpp
        src/ExtendedExpressionContext.cpp
        src/Scanner.cpp
        src/Stream.cpp
)

# Create the wrapper library
add_library(hyperscan-cpp ${HYPERSCAN_CPP_SOURCES})

# Set library type dynamically based on BUILD_SHARED_LIBS
set_target_properties(hyperscan-cpp PROPERTIES
        OUTPUT_NAME "hyperscan-cpp"
        VERSION 1.0.0
        SOVERSION 1
)

# Link against the Hyperscan shared library
target_link_libraries(hyperscan-cpp PUBLIC ${HYPERSCAN_LIBRARY})

# Include directories
target_include_directories(hyperscan-cpp PUBLIC
        ${HYPERSCAN_INCLUDE_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
        $<INSTALL_INTERFACE:include/hyperscan-cpp>
)

# Enable multi-threading
target_compile_options(hyperscan-cpp PRIVATE -pthread)

# Installation rules
install(TARGETS hyperscan-cpp
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

install(DIRECTORY includes/
        DESTINATION include/hyperscan-cpp
        FILES_MATCHING PATTERN "*.h"
)

# Build example programs
option(BUILD_EXAMPLES "Build example executables" ON)
if(BUILD_EXAMPLES)
    # Single pattern test
    add_executable(single_pattern_test examples/SinglePatternSearch.cpp)
    target_link_libraries(single_pattern_test PRIVATE hyperscan-cpp)

    # Multi pattern test
    add_executable(multi_pattern_test examples/MultiPatternSearch.cpp)
    target_link_libraries(multi_pattern_test PRIVATE hyperscan-cpp)

    # Stream test
    add_executable(single_pattern_stream_test examples/SinglePatternStream.cpp)
    target_link_libraries(single_pattern_stream_test PRIVATE hyperscan-cpp)
endif()