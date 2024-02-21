cmake_minimum_required(VERSION 3.10)
project(ifcComp)

set(CMAKE_CXX_STANDARD 11)
set(BUILD_surface_on_nurb ON CACHE BOOL "Build surface on nurb")
find_package(PCL 1.14 REQUIRED) 

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
# Add your source files here
set(SOURCES
ifcComp.cpp
bspline_fitting.cpp
)

# Add your header files here
set(HEADERS
ifcComp.h
)
add_executable(ifcComp  ${SOURCES} ${HEADERS})

target_link_libraries(ifcComp ${PCL_LIBRARIES} NO_DEFAULT_PATH)
