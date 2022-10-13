cmake_minimum_required(VERSION 3.22)
project(DVA338_Lab3)

set(CMAKE_CXX_STANDARD 17)
include_directories("/home/nema/DevOgl/Common/freeglut-3.2.2/include/GL")
include_directories("/home/nema/Downloads/embree-3.13.3.x86_64.linux/lib")

enable_testing()

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
            STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_library(lib_Ray
        Ray.h
        Ray.cpp
        Vec3.h
        )

add_library(lib_Sphere
        Sphere.h
        Sphere.cpp
        Vec3.h
        Ray.h
        Ray.cpp
        )

find_package(OpenGL)
if(NOT OPENGL_FOUND AND NOT WIN32)
    message("This build script might have a bad time if it cannot even find opengl ...")
else()
    include_directories(${OPENGL_INCLUDE_DIR})
    link_libraries(${OPENGL_LIBRARIES})
endif()

#jmm01: This mess is mostly due to allowing for different OS and build configurations

if(WIN32)
    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/../Common/glew/")
        message("You should set up the Common folder as described in the lab startup document. Exiting ...")
        exit(1)
    endif()
    set(GLEW_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/../Common/glew/include/GL")
    if("${CMAKE_GENERATOR_PLATFORM}" MATCHES "(x86|Win32)")
        set(GLEW_LIBRARIES "${CMAKE_SOURCE_DIR}/../Common/glew/lib/Release/Win32/glew32.lib")
    else()
        set(GLEW_LIBRARIES "${CMAKE_SOURCE_DIR}/../Common/glew/lib/Release/x64/glew32.lib")
    endif()
else()
    #We check if GLEW and GLUT are installed system-wide.
    find_package(GLEW)
    if (GLEW_FOUND)
        include_directories(${GLEW_INCLUDE_DIRS})
        link_libraries(${GLEW_LIBRARIES})
        # We have specific instructions for Windows-setup that should be done before this
    elseif(WIN32)

        # If no system-wide installation found, and not on windows, we build from source and then link
    else()
        if(NOT EXISTS "${CMAKE_SOURCE_DIR}/../Common/Installs")
            execute_process("chmod +x ${CMAKE_SOURCE_DIR}/Lab1_setup_NON_WINDOWS_ONLY/install_prereqs_NON_WINDOWS.sh")
            execute_process("${CMAKE_SOURCE_DIR}/Lab1_setup_NON_WINDOWS_ONLY/install_prereqs_NON_WINDOWS.sh ${CMAKE_SOURCE_DIR}/../Common")
        endif()
        set(GLEW_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/../Common/Installs/include/GL")
        set(GLEW_LIBRARIES "${CMAKE_SOURCE_DIR}/../Common/Installs/lib/libGLEW.so")
    endif()
endif()

if(WIN32)
    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/../Common/freeglut/")
        message("You should set up the Common folder as described in the lab startup document. Exiting ...")
        exit(1)
    endif()
    set(GLUT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../Common/freeglut/include/GL")
    if("${CMAKE_GENERATOR_PLATFORM}" MATCHES "(x86|Win32)")
        set(GLUT_LIBRARIES "${CMAKE_SOURCE_DIR}/../Common/freeglut/lib/freeglut.lib")
    else()
        set(GLUT_LIBRARIES "${CMAKE_SOURCE_DIR}/../Common/freeglut/lib/x64/freeglut.lib")
    endif()
else()
    find_package(GLUT)
    if (GLUT_FOUND)
        include_directories(${GLUT_INCLUDE_DIR})
        link_libraries(${GLUT_LIBRARIES})
    else()
        if(NOT EXISTS "${CMAKE_SOURCE_DIR}/../Common/Installs")
            message("Check ${CMAKE_SOURCE_DIR}/Lab1_setup for scripts for building prerequisites from source")
            exit(1)
        endif()
        set(GLUT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../Common/Installs/include/GL")
        set(GLUT_LIBRARIES "${CMAKE_SOURCE_DIR}/../Common/Installs/lib/freeglut.so")
    endif()
endif()


set(MY_HEADER_FILES
        Image.h
        Ray.cpp
        Sphere.h
        Vec3.h
        Camera.h Light.h Surface.h Triangle.h TriangleLight.h)

set(MY_SOURCE_FILES
        Main.cpp
        Surface.cpp Triangle.cpp)

include_directories(
        ${GLUT_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
)
link_libraries(
        ${GLUT_LIBRARIES}
        ${GLEW_LIBRARIES}
)

add_executable(DVA338_Lab3
        ${MY_HEADER_FILES}
        ${MY_SOURCE_FILES}
        )
target_link_libraries(DVA338_Lab3
        lib_Ray
        lib_Sphere
        )
