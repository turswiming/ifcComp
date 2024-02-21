cmake_minimum_required(VERSION 3.10)
project(ifcComp)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_surface_on_nurb ON CACHE BOOL "Build surface on nurb")
find_package(Qt5 COMPONENTS Xml Script OpenGL Svg Widgets)
if(Qt5_FOUND)
  message("Qt5 found")
else()
  message(FATAL_ERROR "Qt5 not found")
endif()
find_package(CGAL REQUIRED COMPONENTS Core Qt5)
include(${CGAL_MODULES_DIR}/CGAL_Macros.cmake)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
# Add your source files here
set(SOURCES
ifcComp.cpp
#bspline_fitting.cpp
Reader.cpp
)

# Add your header files here
set(HEADERS
ifcComp.h
Reader.h
)
add_executable(ifcComp  ${SOURCES} ${HEADERS})

target_link_libraries(ifcComp 
${PCL_LIBRARIES}  
CGAL::CGAL CGAL::CGAL_Core  CGAL::CGAL_Basic_viewer)
# Copy data directory to compile result directory
add_custom_command(TARGET ifcComp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:ifcComp>/data
)
