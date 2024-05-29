cmake_minimum_required(VERSION 3.28)
project(CERT_Alert_System)

set(CMAKE_CXX_STANDARD 17)

# Add SQLite3 library
add_library(sqlite3 libs/sqlite3.c)
include_directories(libs)

# Add PugiXML library
add_library(pugixml libs/pugixml.cpp)
include_directories(libs)

# Add the executable for the CERT Alert System
add_executable(CERT_Alert_System main.cpp rss_parser.cpp db_init.cpp rss_fetcher.cpp
        db_operations.h
        db_operations.cpp)
target_link_libraries(CERT_Alert_System sqlite3 pugixml wininet)
