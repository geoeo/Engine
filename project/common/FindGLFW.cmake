# Locate the GLFW library (version 2.0)
# This module defines the following variables:
# GLFW_LIBRARIES, the name of the library;
# GLFW_INCLUDE_DIRS, where to find GLFW include files.
# GLFW_FOUND, true if library path was resolved
#
# Usage example to compile an "executable" target to the glfw library:
#
# FIND_PACKAGE (GLFW REQUIRED)
# INCLUDE_DIRECTORIES (${GLFW_INCLUDE_DIRS})
# ADD_EXECUTABLE (executable ${YOUR_EXECUTABLE_SRCS})
# TARGET_LINK_LIBRARIES (executable ${GLFW_LIBRARIES})
#
# TODO:
# Lookup for windows
# Allow the user to select to link to a shared library or to a static library.
#
# SEE:
# - https://raw.github.com/progschj/OpenGL-Examples/master/cmake_modules/FindGLFW.cmake
#

FIND_PATH( GLFW_INCLUDE_DIRS GLFW/glfw3.h
    /usr/local/include
    /usr/local/X11R6/include
    /usr/X11R6/include
    /usr/X11/include
    /usr/include/X11
    /usr/include
    /opt/X11/include
    /opt/include
    ${CMAKE_SOURCE_DIR}/external/glfw/include)

if(WIN32)
    SET(GLFWLIBNAME glfw3)
else()
    # IMPORTANT: uppercase otherwise problem on linux
    SET(GLFWLIBNAME glfw)
endif()

FIND_LIBRARY( GLFW_LIBRARIES NAMES ${GLFWLIBNAME} PATHS
    /usr/local/lib
    /usr/local/X11R6/lib
    /usr/lib/x86_64-linux-gnu/
    /usr/X11R6/lib
    /usr/X11/lib
    /usr/lib/X11
    /usr/lib
    /opt/X11/lib
    /opt/lib
    ${CMAKE_SOURCE_DIR}/external/glfw/lib)

SET(GLFW_FOUND "NO")

IF(GLFW_LIBRARIES AND GLFW_INCLUDE_DIRS)
    SET(GLFW_FOUND "YES")
ENDIF(GLFW_LIBRARIES AND GLFW_INCLUDE_DIRS)
