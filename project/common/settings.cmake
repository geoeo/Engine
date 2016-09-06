#---Include ".cmake" modules from the current directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR})

#--- Find GLFW
find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
add_definitions(${GLFW_DEFINITIONS})
if(NOT GLFW_FOUND)
    message(ERROR " GLFW not found!")
endif()

#--- Find SOIL
find_package(SOIL REQUIRED)
include_directories(${SOIL_INCLUDE_DIRS})
add_definitions(${SOIL_DEFINITIONS})
if(NOT SOIL_FOUND)
    message(ERROR " SOIL not found!")
endif()

#--- Find GLEW (STATICALLY LINKED)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(-DGLEW_STATIC)
if(NOT GLEW_FOUND)
    message(ERROR " GLEW not found!")
endif()

#--- stringify shader macro
#--- @src: https://github.com/OpenGP/OpenGP/blob/master/cmake/target_stringify_shader.cmake
macro(target_stringify_shader MYTARGET SHADER)
    set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    set(TARGET_DIR ${CMAKE_CURRENT_BINARY_DIR})
    set(TARGET_NAME stringify_${MYTARGET}_${SHADER})
    add_custom_command(
        # The command produces a shader.h file in output
        OUTPUT ${SHADER}.h
        COMMAND ${CMAKE_COMMAND}
        # Parameters of the script
        -DSHADERNAME=${SHADER}
        -DINPUT_DIR=${SOURCE_DIR}
        -DOUTPUT_DIR=${TARGET_DIR}
         # Executes the script
        -P ${CMAKE_SOURCE_DIR}/common/stringify_shader.cmake
         # And when it does spit out this command
         DEPENDS ${SOURCE_DIR}/${SHADER}.glsl
         COMMENT "Converting ${SHADER}.glsl to a char* in ${SHADER}.h")
    # Creates dummy target (to add dependencies)
    add_custom_target(${TARGET_NAME} DEPENDS ${SHADER}.h)
    # Make shader.h visible to the compile time (NEEDS MACRO!!)
    include_directories(${TARGET_DIR})
    # Creates dependency
    add_dependencies(${MYTARGET} ${TARGET_NAME})
endmacro(target_stringify_shader)

#--- Wraps file deployments
macro(target_deploy_file MYTARGET FILEPATH)
    get_filename_component(FILENAME ${FILEPATH} NAME)
    get_filename_component(FILEDIR ${FILEPATH} DIRECTORY)
    set(TARGET_NAME deployfile_${MYTARGET}_${FILENAME})
    set(TARGET_DIR "${CMAKE_CURRENT_BINARY_DIR}/${FILEDIR}")
    add_custom_command(
        # Execute command after target is built (pre-run)
        TARGET ${MYTARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${FILEPATH} ${TARGET_DIR}
        DEPENDS ${FILEPATH}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Copying ${FILEPATH} to ${TARGET_DIR}")
    #add_dependencies(${MYTARGET} ${TARGET_NAME})
endmacro()

#--- Wraps directory deployments
macro(target_deploy_dir MYTARGET FILEDIR)
    set(TARGET_NAME deployfile_${MYTARGET}_${FILENAME})
    set(TARGET_DIR "${CMAKE_CURRENT_BINARY_DIR}/${FILEDIR}")
    add_custom_command(
        # Execute command after target is built (pre-run)
        TARGET ${MYTARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${FILEDIR} ${TARGET_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Copying ${FILEDIR} to ${TARGET_DIR}")
endmacro()

#--- FIND OPENGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif()

#--- FIND AntTweakBar
find_package(AntTweakBar REQUIRED)
include_directories(${ANTTWEAKBAR_INCLUDE_DIRS})
link_directories(${ANTTWEAKBAR_LIBRARY_DIRS})
if(NOT ANTTWEAKBAR_FOUND)
    message(ERROR " AntTweakBar not found!")
endif()

#--- FIND OPENGP
find_package(OpenGP REQUIRED)
include_directories(${OpenGP_INCLUDE_DIRS})
add_definitions(-DHEADERONLY)
add_definitions(-DUSE_EIGEN)
if(NOT OPENGP_FOUND)
    message(ERROR " OPENGP not found!")
endif()

#--- FIND EIGEN3
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})
if(NOT EIGEN3_FOUND)
    message(ERROR " EIGEN not found!")
endif()

#--- Find Leap
find_package(Leap REQUIRED)
include_directories(${LEAP_INCLUDE_DIRS})
link_directories(${LEAP_LIBRARY_DIRS})
add_definitions(${LEAP_DEFINITIONS})
if(NOT LEAP_FOUND)
    message(ERROR " Leap not found!")
endif()

#--- Find Assimp
find_package(Assimp REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS})
add_definitions(${ASSIMP_DEFINITIONS})
if(NOT ASSIMP_FOUND)
    message(ERROR " Assimp not found!")
endif()

#--- Common headers/libraries for all the exercises
include_directories(${CMAKE_CURRENT_LIST_DIR})

SET(COMMON_LIBS
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${ANTTWEAKBAR_LIBRARIES}
    ${SOIL_LIBRARIES}
    ${LEAP_LIBRARIES}
    ${ASSIMP_LIBRARY_DIRS}
)

#--- Use C++11
#--- @src: http://stackoverflow.com/a/25836953
if(WIN32)
    message(STATUS "Compiling on Windows without C++11 support.")
else()
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
endif()