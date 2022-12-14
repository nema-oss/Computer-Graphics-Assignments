# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.6)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6...3.20)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget FreeGLUT::freeglut FreeGLUT::freeglut_static)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Create imported target FreeGLUT::freeglut
add_library(FreeGLUT::freeglut SHARED IMPORTED)

set_target_properties(FreeGLUT::freeglut PROPERTIES
  INTERFACE_LINK_LIBRARIES "/usr/lib64/libGL.so;m;/usr/lib64/libX11.so;/usr/lib64/libXrandr.so;/usr/lib64/libXi.so"
)

# Create imported target FreeGLUT::freeglut_static
add_library(FreeGLUT::freeglut_static STATIC IMPORTED)

set_target_properties(FreeGLUT::freeglut_static PROPERTIES
  INTERFACE_LINK_LIBRARIES "/usr/lib64/libGL.so;m;/usr/lib64/libX11.so;/usr/lib64/libXrandr.so;/usr/lib64/libXi.so"
)

# Import target "FreeGLUT::freeglut" for configuration ""
set_property(TARGET FreeGLUT::freeglut APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(FreeGLUT::freeglut PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/home/nema/DevOgl/Common/freeglut-3.2.2/build/lib/libglut.so.3.11.1"
  IMPORTED_SONAME_NOCONFIG "libglut.so.3"
  )

# Import target "FreeGLUT::freeglut_static" for configuration ""
set_property(TARGET FreeGLUT::freeglut_static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(FreeGLUT::freeglut_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "/home/nema/DevOgl/Common/freeglut-3.2.2/build/lib/libglut.a"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
