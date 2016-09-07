FIND_PATH( SOIL_INCLUDE_DIRS SOIL.h
    $ENV{SOILDIR}/include
    /usr/local/include
    /usr/local/X11R6/include
    /usr/X11R6/include
    /usr/X11/include
    /usr/include/X11
    /usr/include
    /opt/X11/include
    /opt/include
    # FOR WINDOWS
    ${CMAKE_SOURCE_DIR}/external/soil/include)


SET(SOILLIBNAME SOIL)

FIND_LIBRARY( SOIL_LIBRARIES
    NAMES ${SOILLIBNAME} PATHS
    $ENV{SOILDIR}/lib
    /usr/local/lib
    /usr/local/X11R6/lib
    /usr/X11R6/lib
    /usr/X11/lib
    /usr/lib/X11
    /usr/lib
    /opt/X11/lib
    /opt/lib
    # FOR UBUNTU 12.04 LTS
    /usr/lib/x86_64-linux-gnu
    # FOR WINDOWS
    ${CMAKE_SOURCE_DIR}/external/soil/lib)

SET(SOIL_FOUND "NO")
IF(SOIL_LIBRARIES AND SOIL_INCLUDE_DIRS)
    SET(SOIL_FOUND "YES")
ENDIF()
