cmake_minimum_required(VERSION 3.10)

project(CERT_Alert_System)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${PROJECT_SOURCE_DIR}/libs/pugixml)
include_directories(${PROJECT_SOURCE_DIR}/libs/mailclient-cpp-master)
include_directories(${PROJECT_SOURCE_DIR}/libs/SmtpClient-for-Qt)

add_executable(CERT_Alert_System
        main.cpp
        cli.cpp
        config.cpp
        db_init.cpp
        db_operations.cpp
        log.cpp
        rss_parser.cpp
        rss_fetcher.cpp
        strptime.cpp
)

# SQLite3
add_library(sqlite3 STATIC ${PROJECT_SOURCE_DIR}/libs/sqlite3.c)
target_link_libraries(CERT_Alert_System sqlite3)

# PugiXML
add_library(pugixml STATIC ${PROJECT_SOURCE_DIR}/libs/pugixml/src/pugixml.cpp)
target_link_libraries(CERT_Alert_System pugixml)

# WinInet (for InternetOpen etc.)
target_link_libraries(CERT_Alert_System wininet)

# MAPI32 (for email notifications)
target_link_libraries(CERT_Alert_System MAPI32)

# Additional libraries
target_link_libraries(CERT_Alert_System kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32)
