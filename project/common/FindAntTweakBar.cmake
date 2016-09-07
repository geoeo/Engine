FIND_PATH( ANTTWEAKBAR_INCLUDE_DIRS AntTweakBar.h
    $ENV{ANTTWEAKBARDIR}/include
    /home/$ENV{USER}/.libs/AntTweakBar/include
    /usr/local/include
    /usr/local/X11R6/include
    /usr/X11R6/include
    /usr/X11/include
    /usr/include/X11
    /usr/include
    /opt/X11/include
    /opt/include
    # FOR WINDOWS
    ${CMAKE_SOURCE_DIR}/external/anttb/include)

if(WIN32)
    SET(ANTTWEAKBARLIBNAME AntTweakBar64)
else()
    SET(ANTTWEAKBARLIBNAME AntTweakBar)
endif()

FIND_LIBRARY( ANTTWEAKBAR_LIBRARIES
    NAMES ${ANTTWEAKBARLIBNAME} PATHS
    # On linux: install to /opt/AntTweakBar
    # add to .bashrc
    # export ANTTWEAKBARDIR=/opt/AntTweakBar
    $ENV{ANTTWEAKBARDIR}/lib
    /home/$ENV{USER}/.libs/AntTweakBar/lib
    /usr/local/lib
    /usr/local/X11R6/lib
    /usr/X11R6/lib
    /usr/X11/lib
    /usr/lib/X11
    /usr/lib
    /opt/X11/lib
    /opt/lib
    # FOR WINDOWS
    ${CMAKE_SOURCE_DIR}/external/anttb/lib)

SET(ANTTWEAKBAR_FOUND "NO")
IF(ANTTWEAKBAR_LIBRARIES AND ANTTWEAKBAR_INCLUDE_DIRS)
    SET(ANTTWEAKBAR_FOUND "YES")
ENDIF()