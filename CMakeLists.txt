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

include_directories(Daemon/Analyzer/include)
include_directories(.)
include_directories(Client/Network/include)
include_directories(CommunicateProtocol/Message)
include_directories(Daemon/Network/include)

add_executable( Client
                Client/Client.cpp
                Client/Network/src/NetworkClient.cpp)

add_executable( Daemon
                Daemon/Daemon.cpp
                Daemon/Network/src/NetworkDaemon.cpp
                Daemon/Analyzer/src/Analyzer.cpp)
                target_link_libraries(Daemon -pthread)