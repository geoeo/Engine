FIND_PATH( LEAP_INCLUDE_DIRS Leap.h
    $ENV{LEAPDIR}/include
    /usr/local/include
    /usr/local/X11R6/include
    /usr/X11R6/include
    /usr/X11/include
    /usr/include/X11
    /usr/include
    /opt/X11/include
    /opt/include
    # FOR WINDOWS
    ${CMAKE_SOURCE_DIR}/external/leap/include)

FIND_LIBRARY( LEAP_LIBRARIES
    NAMES LEAP PATHS
    $ENV{LEAPDIR}/lib/x64
    /usr/local/lib/x64
    /usr/local/X11R6/lib/x64
    /usr/X11R6/lib/x64
    /usr/X11/lib/x64
    /usr/lib/X11/x64
    /usr/lib/x64
    /opt/X11/lib/x64
    /opt/lib/x64
    # FOR WINDOWS
    ${CMAKE_SOURCE_DIR}/external/leap/lib/x64)

SET(LEAP_FOUND "NO")
IF(LEAP_LIBRARIES AND LEAP_INCLUDE_DIRS)
    SET(LEAP_FOUND "YES")
ENDIF()
