add_subdirectory(catch)

link_libraries(LineProtocol catch)

add_executable(LineProtocolTests LineProtocolParse.cpp LineProtocolFormat.cpp)
add_test(LineProtocol LineProtocolTests)
