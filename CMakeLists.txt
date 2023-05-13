cmake_minimum_required(VERSION 3.25)
project(Music163SongDownload)

set(CMAKE_CXX_STANDARD 23)
find_package(Poco REQUIRED Foundation)
find_package(Poco REQUIRED JSON)
add_library(Music163SongDownload SHARED CloudMusic.cpp CloudMusic.h TextHelper.cpp)
target_link_libraries(Music163SongDownload PRIVATE Poco::Foundation)
target_link_libraries(Music163SongDownload PRIVATE Poco::JSON)