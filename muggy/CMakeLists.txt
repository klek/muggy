cmake_minimum_required ( VERSION 3.0.0 )
project ( muggy VERSION 0.1.0 LANGUAGES C CXX )

include ( CTest )
enable_testing ()

# CMAKE flags
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror") 

# Determine OS Bitness ie 32 or 64
set ( OSbitness 32 )
if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    message ( STATUS "CMake compiling for 64-bit" )
    set ( OSBitness 64 )
else ()
    message ( STATUS "CMake compiling for 32-bit" )
endif ()

# Setup output directory for binaries
set ( OutputDir "${CMAKE_SOURCE_DIR}/../bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}" )
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OutputDir} )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OutputDir} )
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OutputDir} )

# Find required packages
find_package ( glfw3 3.3 REQUIRED )
find_package ( OpenGL REQUIRED )
find_package ( GLEW REQUIRED )

# Set include directories
set ( IncDir ${CMAKE_SOURCE_DIR} )
# For debugging
#message( STATUS "****** ${CMAKE_SOURCE_DIR} ******" )

# Include directories
include_directories( IncDir )

# Include external headers
#include_directories ( )

# Add the source to the library
add_library ( ${PROJECT_NAME} 
              SHARED muggy.cpp 
)
#add_library ( "${PROJECT_NAME}static" 
#              STATIC muggy.cpp 
#)

# Add target libraries to our this library
target_link_libraries ( ${PROJECT_NAME}
                        PRIVATE glfw
                        PRIVATE OpenGL::GL
                        PRIVATE GLEW 
)


set ( CPACK_PROJECT_NAME ${PROJECT_NAME} )
set ( CPACK_PROJECT_VERSION ${PROJECT_VERSION} )
include ( CPack )
