cmake_minimum_required(VERSION 3.30)
project(swerv)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)

add_executable(swerv src/main.cpp)

target_include_directories(swerv PRIVATE 
    ${PNG_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIRS}
)

target_link_libraries(swerv PRIVATE 
    ${PNG_LIBRARY}
    ${ZLIB_LIBRARIES}
)