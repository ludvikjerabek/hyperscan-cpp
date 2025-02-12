cmake_minimum_required(VERSION 3.16)
project(hyperscan-cpp LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build both shared and static by default
option(BUILD_SHARED_LIBS "Build shared library" ON)
option(BUILD_STATIC_LIBS "Build static library" ON)

# Locate Intel Hyperscan manually
find_library(HYPERSCAN_LIBRARY NAMES hs)
find_path(HYPERSCAN_INCLUDE_DIR NAMES hs/hs.h)

if(NOT HYPERSCAN_LIBRARY OR NOT HYPERSCAN_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find Intel Hyperscan library. Install it and set HYPERSCAN_LIBRARY and HYPERSCAN_INCLUDE_DIR")
endif()

message(STATUS "Hyperscan Library: ${HYPERSCAN_LIBRARY}")
message(STATUS "Hyperscan Include: ${HYPERSCAN_INCLUDE_DIR}")

# Source files
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

# Create shared library if enabled
if(BUILD_SHARED_LIBS)
    add_library(hyperscan-cpp SHARED ${HYPERSCAN_CPP_SOURCES})
    set_target_properties(hyperscan-cpp PROPERTIES
            OUTPUT_NAME "hyperscan-cpp"
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR}
    )
    target_include_directories(hyperscan-cpp PUBLIC
            ${HYPERSCAN_INCLUDE_DIR}
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
            $<INSTALL_INTERFACE:include/hyperscan-cpp>
    )
    target_link_libraries(hyperscan-cpp PUBLIC ${HYPERSCAN_LIBRARY})
    target_compile_options(hyperscan-cpp PRIVATE -pthread)
endif()

# Create static library if enabled
if(BUILD_STATIC_LIBS)
    add_library(hyperscan-cpp-static STATIC ${HYPERSCAN_CPP_SOURCES})
    set_target_properties(hyperscan-cpp-static PROPERTIES
            OUTPUT_NAME "hyperscan-cpp"
            POSITION_INDEPENDENT_CODE ON
    )
    target_include_directories(hyperscan-cpp-static PUBLIC
            ${HYPERSCAN_INCLUDE_DIR}
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
            $<INSTALL_INTERFACE:include/hyperscan-cpp>
    )
    target_link_libraries(hyperscan-cpp-static PUBLIC ${HYPERSCAN_LIBRARY})
    target_compile_options(hyperscan-cpp-static PRIVATE -pthread)
endif()

# Install headers
install(DIRECTORY includes/
        DESTINATION include/hyperscan-cpp
        FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY src/
        DESTINATION include/hyperscan-cpp
        FILES_MATCHING PATTERN "*.h"
)

# Install libraries
if(BUILD_SHARED_LIBS)
    install(TARGETS hyperscan-cpp
            EXPORT hyperscan-cppTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            INCLUDES DESTINATION include/hyperscan-cpp
    )
endif()

if(BUILD_STATIC_LIBS)
    install(TARGETS hyperscan-cpp-static
            EXPORT hyperscan-cppTargets
            ARCHIVE DESTINATION lib
            INCLUDES DESTINATION include/hyperscan-cpp
    )
endif()

# Installation & Versioning
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/hyperscan-cppConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

install(EXPORT hyperscan-cppTargets
        FILE hyperscan-cppTargets.cmake
        DESTINATION lib/cmake/hyperscan-cpp
)

# Build example programs
option(BUILD_EXAMPLES "Build example executables" ON)

if(BUILD_EXAMPLES)
    # Function to add example with both static and dynamic versions
    function(add_example_executable NAME SOURCE)
        if(BUILD_SHARED_LIBS)
            add_executable(${NAME} ${SOURCE})
            target_link_libraries(${NAME} PRIVATE hyperscan-cpp)
        endif()

        if(BUILD_STATIC_LIBS)
            add_executable(${NAME}_static ${SOURCE})
            target_link_libraries(${NAME}_static PRIVATE hyperscan-cpp-static)
        endif()
    endfunction()

    # Add examples with both static and dynamic versions
    add_example_executable(single_pattern_test examples/SinglePatternSearch.cpp)
    add_example_executable(multi_pattern_test examples/MultiPatternSearch.cpp)
    add_example_executable(single_pattern_stream_test examples/SinglePatternStream.cpp)

    # Print status message
    if(BUILD_SHARED_LIBS)
        message(STATUS "Building dynamic examples")
    endif()
    if(BUILD_STATIC_LIBS)
        message(STATUS "Building static examples")
    endif()
endif()

# Create uninstall target
if(NOT TARGET uninstall)
    configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
            IMMEDIATE @ONLY)

    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()