cmake_minimum_required(VERSION 2.8)
project(source)

# OPTION(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC Runtime Library DLL (/MD or /MDd)" ON)

# Load the common configuration
include(common/settings.cmake)

# Add the project source
add_subdirectory(source)
