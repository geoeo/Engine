FIND_PATH( ASSIMP_INCLUDE_DIRS NAMES Importer.hpp scene.h postprocess.h PATHS
    $ENV{ASSIMP}/include
    /usr/local/include
    /usr/local/X11R6/include
    /usr/X11R6/include
    /usr/X11/include
    /usr/include/X11
    /usr/include
    /opt/X11/include
    /opt/include
    ${CMAKE_SOURCE_DIR}/external/assimp/include)

FIND_LIBRARY( ASSIMP_LIBRARY_DIRS NAMES assimp-vc120-mtd PATHS
    $ENV{ASSIMP}/lib/x64
    /usr/local/lib/x64
    /usr/local/X11R6/lib/x64
    /usr/X11R6/lib/x64
    /usr/X11/lib/x64
    /usr/lib/X11/x64
    /usr/lib/x64
    /opt/X11/lib/x64
    /opt/lib/x64
    ${CMAKE_SOURCE_DIR}/external/assimp/lib)



SET(ASSIMP_FOUND "NO")
IF(ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARY_DIRS)
    SET(ASSIMP_FOUND "YES")
ENDIF()
