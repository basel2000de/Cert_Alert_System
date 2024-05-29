cmake_minimum_required(VERSION 3.28)
project(CERT_Alert_System)

set(CMAKE_CXX_STANDARD 17)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)

# Add the executable for the CERT Alert System
add_executable(CERT_Alert_System
        main.cpp
        rss_parser.cpp
        db_init.cpp
        rss_fetcher.cpp
        db_operations.cpp
)

target_link_libraries(CERT_Alert_System unofficial::sqlite3::sqlite3 pugixml::pugixml cpr::cpr)
