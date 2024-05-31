cmake_minimum_required(VERSION 3.28)
project(CERT_Alert_System)

set(CMAKE_CXX_STANDARD 17)

add_executable(CERT_Alert_System main.cpp cli.cpp db_init.cpp db_operations.cpp rss_parser.cpp rss_fetcher.cpp)

# Add SQLite3 library
add_library(sqlite3 libs/sqlite3.c)
include_directories(libs)
target_link_libraries(CERT_Alert_System sqlite3)

# Add mailclient-cpp library
include_directories(${CMAKE_SOURCE_DIR}/libs/mailclient-cpp-master/MAIL)
add_library(mailclient-cpp STATIC
        ${CMAKE_SOURCE_DIR}/libs/mailclient-cpp-master/MAIL/SMTPClient.cpp
        ${CMAKE_SOURCE_DIR}/libs/mailclient-cpp-master/MAIL/MAILClient.cpp
        ${CMAKE_SOURCE_DIR}/libs/mailclient-cpp-master/MAIL/POPClient.cpp
        ${CMAKE_SOURCE_DIR}/libs/mailclient-cpp-master/MAIL/IMAPClient.cpp
        ${CMAKE_SOURCE_DIR}/libs/mailclient-cpp-master/MAIL/CurlHandle.cpp
)
target_link_libraries(CERT_Alert_System mailclient-cpp)
