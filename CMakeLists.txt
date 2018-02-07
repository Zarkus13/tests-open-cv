cmake_minimum_required(VERSION 3.9)
project(TestOpenCV)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(TestOpenCV main.cpp)
add_executable(Calibrate calibrate.cpp)
add_executable(CreateMarker createMarker.cpp)
add_executable(CreateCharucoBoard createCharucoBoard.cpp)
add_executable(DetectMarkers detectMarkers.cpp)

target_link_libraries(TestOpenCV ${OpenCV_LIBS})
target_link_libraries(Calibrate ${OpenCV_LIBS})
target_link_libraries(CreateMarker ${OpenCV_LIBS})
target_link_libraries(CreateCharucoBoard ${OpenCV_LIBS})
target_link_libraries(DetectMarkers ${OpenCV_LIBS})