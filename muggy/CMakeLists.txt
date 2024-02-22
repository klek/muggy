cmake_minimum_required ( VERSION 3.0...3.20 )
set ( PROJECT_NAME muggy )
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
    set ( OSBitness 64 )
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

# Download all submodules
find_package ( Git REQUIRED )
if ( GIT_FOUND AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../.git")
    # Update submodules as needed
    option ( GIT_SUBMODULE "Check submodules during build" ON )
    if ( GIT_SUBMODULE )
        message ( STATUS "Updating submodules" )
        execute_process( COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive 
                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../
                         RESULT_VARIABLE GIT_SUBMODULE_RESULT  
                        )
        if ( NOT GIT_SUBMODULE_RESULT EQUAL "0" )
            message ( FATAL_ERROR "${GIT_EXECUTABLE} submodule update --init --recursive failed with ${GIT_SUBMODULE_RESULT}" )
        endif ()
    endif ()
endif ()

# Now check that the CMakeLists.txt for each submodule exists
if ( NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw/CMakeLists.txt" )
    message ( FATAL_ERROR "The GLFW submodule was not properly downloaded! GIT_SUBMODULE was turned off or failed?" )
else ()
    set ( GLFW_BUILD_EXAMPLES OFF )
    set ( GLFW_BUILD_TESTS OFF )
    set ( GLFW_BUILD_DOCS OFF )
    add_subdirectory ( thirdparty/glfw )
endif ()


# Find required packages
#find_package ( glfw3 3.3 REQUIRED )
set ( OpenGL_GL_PREFERENCE "GLVND" )
find_package ( OpenGL REQUIRED )
#find_package ( GLEW REQUIRED )

# Set include directories
set ( IncDir ${CMAKE_CURRENT_SOURCE_DIR} )
# For debugging
message( STATUS "****** ${CMAKE_CURRENT_SOURCE_DIR} ******" )

# Include directories
include_directories( ${IncDir} )
#include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/code" )
#include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/code/common" )
#include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/code/core" )
#include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/code/graphics" )
#include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/code/log" )

# Include external headers
#include_directories ( )

# Add source files
file ( GLOB_RECURSE SrcFiles
       ${CMAKE_CURRENT_SOURCE_DIR}/code/*.cpp )
# Add engineAPI files
file ( GLOB_RECURSE apiFiles
       ${CMAKE_CURRENT_SOURCE_DIR}/engineAPI/*.cpp )

# Add the sources to the library
add_library ( ${PROJECT_NAME} 
              SHARED muggy.cpp 
#              STATIC muggy.cpp 
              ${SrcFiles}
              ${apiFiles}
)

# For debugging
message( STATUS "****** ${SrcFiles} ******" )
message( STATUS "****** ${apiFiles} ******" )

# Add target include directories
target_include_directories ( ${PROJECT_NAME}
                             PUBLIC thirdparty/glfw/include 
)

# Add target link directories
#target_link_directories ( ${PROJECT_NAME} 
#                          PRIVATE thirdparty/glfw/src 
#)

# Add target libraries to our this library
target_link_libraries ( ${PROJECT_NAME}
                        PRIVATE glfw
                        PRIVATE OpenGL::GL
#                        PRIVATE GLEW 
)

# Add compile defines such as DEBUG_BUILD etc
target_compile_definitions ( ${PROJECT_NAME}
                             PUBLIC  $<$<CONFIG:Debug>:DEBUG_BUILD>
                             PUBLIC  $<$<CONFIG:Debug>:GLFW>
)

# Add compile defines based on platform
if ( WIN32 )
    # For windows we currently assume MSVC compiler
    target_compile_definitions( ${PROJECT_NAME}
                                PUBLIC $<$<CONFIG:Debug>:MSVC> )
elseif( UNIX )
    # For unix we currently assume GCC compiler
    target_compile_definitions( ${PROJECT_NAME}
                                PUBLIC $<$<CONFIG:Debug>:GCC> )
endif()

if ( WIN32 )
    # Add a suffix to the import library to avoid naming conflicts
    set_target_properties ( ${PROJECT_NAME} PROPERTIES IMPORT_SUFFIX "dll.lib" )
endif ()

set ( CPACK_PROJECT_NAME ${PROJECT_NAME} )
set ( CPACK_PROJECT_VERSION ${PROJECT_VERSION} )
include ( CPack )
