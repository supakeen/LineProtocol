add_subdirectory(catch)

link_libraries(LineProtocol catch)

add_executable(LineProtocolTests LineProtocol.cpp)
add_test(LineProtocol LineProtocolTests)
