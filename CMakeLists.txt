cmake_minimum_required(VERSION 3.22)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)

set(JSON_BuildTests OFF CACHE INTERNAL "")

#static linking to make a standalone executable .exe file
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_subdirectory(nlohmann_json)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(search_engine main.cpp ConverterJSON.cpp InvertedIndex.cpp SearchServer.cpp test2.cpp test3.cpp CustomExceptions.cpp)
#add_executable(search_engine ConverterJSON.cpp InvertedIndex.cpp SearchServer.cpp test2.cpp test3.cpp)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json gtest_main)

include(GoogleTest)
gtest_discover_tests(search_engine)
