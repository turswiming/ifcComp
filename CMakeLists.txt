cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
message(STATUS "CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
set(CMAKE_CXX_STANDARD 17)
set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE TRUE)
project(ifcComp)

find_package(CGAL CONFIG  COMPONENTS Core Qt5 REQUIRED)
find_package(Qt5 COMPONENTS Xml Core Gui Script OpenGL Svg Widgets REQUIRED)
if(Qt5_FOUND)
  message("Qt5 found")
else()
  message(FATAL_ERROR "Qt5 not found")
endif()
include(${CGAL_MODULES_DIR}/CGAL_Macros.cmake)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
# Add your source files here
set(SOURCES
ifcComp.cpp
#bspline_fitting.cpp
Reader.cpp
ClusterToVox.cpp
)

# Add your header files here
set(HEADERS
ifcComp.h
Reader.h
ClusterToVox.h
)
add_executable(ifcComp  ${SOURCES} ${HEADERS})

target_link_libraries(ifcComp 
${PCL_LIBRARIES}
        CGAL::CGAL CGAL::CGAL_Core  CGAL::CGAL_Basic_viewer
        Qt5::Core Qt5::Gui Qt5::Widgets
)
# Copy data directory to compile result directory
add_custom_command(TARGET ifcComp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:ifcComp>/data
)
