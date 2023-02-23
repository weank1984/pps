cmake_minimum_required(VERSION 3.10)

project(appfw)

include_directories(include)

file(GLOB pps_src
    src/proxy/*.cpp)

add_library(pps_proxy ${pps_src})

target_link_libraries(pps_proxy pps)