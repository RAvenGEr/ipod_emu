cmake_minimum_required (VERSION 3.10)
project (ipod_emulator)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.66 REQUIRED COMPONENTS
                thread)
set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/iap/packet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/iap/stream.cpp
)
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME}
    Boost::thread
)
