project(searchThreats)
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

IF(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Debug build.")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
  message("Release build.")
ELSE()
  message("Some other build type.")
ENDIF()

include_directories(Analyzer/include)

add_executable( scan_util 
                Analyzer/src/Analyzer.cpp
                main.cpp)

target_link_libraries(scan_util -pthread)