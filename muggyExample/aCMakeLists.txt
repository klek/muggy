cmake_minimum_required ( VERSION 3.0...3.20 )
set ( PROJECT_NAME muggyExample )
project ( ${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX )

include ( CTest )
enable_testing ()

# CMAKE flags
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror") 
set ( CMAKE_CXX_STANDARD 17 )
set ( CMAKE_CXX_STANDARD_REQUIRED TRUE )

# Determine OS Bitness ie 32 or 64
set ( OSbitness 32 )
if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    message ( STATUS "CMake compiling for 64-bit" )
    set (OSBitness 64)
else ()
    message ( STATUS "CMake compiling for 32-bit" )
endif ()

# Setup output directory for binaries
set ( OutputDir "${CMAKE_CURRENT_SOURCE_DIR}/../bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}" )
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OutputDir} )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OutputDir} )
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OutputDir} )
set ( BinaryDir "${CMAKE_CURRENT_SOURCE_DIR}/build" )
set ( CMAKE_BINARY_DIR ${BinaryDir} )

# Set include directories
set ( IncDir ${CMAKE_CURRENT_SOURCE_DIR} )
# For debugging
#message( STATUS "****** ${CMAKE_CURRENT_SOURCE_DIR} ******")

# Include directories
include_directories ( ${IncDir} )
include_directories ( ${IncDir}/tests )

# Include external headers (such as muggy)
include_directories ( ${CMAKE_CURRENT_SOURCE_DIR}/../muggy )

# Add subdirectories (such as muggy) and also specify
# the binary folder (reusing muggy here)
# This will call that folders CMakeLists.txt and build
# Note that this will add target "muggy"
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../muggy 
                  ${CMAKE_CURRENT_SOURCE_DIR}/../muggy/build 
)

# Add source files
file ( GLOB_RECURSE exampleSrcFiles
       ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp )

# Set the sources for the executable
add_executable ( ${PROJECT_NAME} 
                 main.cpp 
                 ${exampleSrcFiles}
)

# Add target libraries
target_link_libraries ( ${PROJECT_NAME} 
                        PRIVATE muggy
)

set ( CPACK_PROJECT_NAME ${PROJECT_NAME} )
set ( CPACK_PROJECT_VERSION ${PROJECT_VERSION} )
include ( CPack )
