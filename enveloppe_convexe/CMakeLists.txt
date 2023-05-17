#cmake_minimum_required(VERSION 3.24)
cmake_minimum_required(VERSION 2.6)

project(ConvexHull LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include(FetchContent)
#FetchContent_Declare(
#    DGtal 
#    GIT_REPOSITORY https://github.com/DGtal-team/DGtal.git        
#    GIT_TAG 1.2
#)
#FetchContent_MakeAvailable(DGtal)
#set(DGtal_DIR ${CMAKE_CURRENT_BINARY_DIR}/_deps/dgtal-build)
set(DGtal_DIR /softwares/INFO/Synthese/geoalgo/DGtal/build)
list(APPEND CMAKE_MODULE_PATH ${DGtal_DIR})
message("PATH DGtal: "${DGtal_DIR})
find_package(DGtal REQUIRED)
include_directories(${DGTAL_INCLUDE_DIRS})
link_directories(${DGTAL_LIBRARY_DIRS})

list(APPEND CMAKE_MODULE_PATH /softwares/INFO/Synthese/geoalgo/DGtal/build)
set(DGtal_DIR /softwares/INFO/Synthese/geoalgo/DGtal/build)


find_package(Boost 1.40 COMPONENTS program_options REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )

add_executable(main main.cpp)
add_executable(jarvis jarvis.cpp)
add_executable(graham graham.cpp)

target_link_libraries(main LINK_PUBLIC ${DGTAL_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(jarvis LINK_PUBLIC ${DGTAL_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(graham LINK_PUBLIC ${DGTAL_LIBRARIES} ${Boost_LIBRARIES})