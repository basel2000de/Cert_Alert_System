cmake_minimum_required(VERSION 3.28)
project(CERT_Alert_System)

set(CMAKE_CXX_STANDARD 17)

add_executable(CERT_Alert_System
        main.cpp
        cli.cpp
        db_init.cpp
        db_operations.cpp
        rss_parser.cpp
        rss_fetcher.cpp
        config.cpp
        log.cpp
        strptime.cpp)  # Add strptime.cpp here

# Add SQLite3 library
add_library(sqlite3 libs/sqlite3.c)
include_directories(libs)
target_link_libraries(CERT_Alert_System sqlite3)

# Link Windows MAPI and WinINet libraries
target_link_libraries(CERT_Alert_System MAPI32 wininet)

# Link PugiXML
add_subdirectory(libs/pugixml)  # Assuming pugixml source is in libs/pugixml
target_link_libraries(CERT_Alert_System pugixml)
