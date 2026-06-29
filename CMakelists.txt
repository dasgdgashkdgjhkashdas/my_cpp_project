
if(MSVC)
    
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    
   
    add_compile_options(/wd4251 /wd4275)
endif()

cmake_minimum_required(VERSION 3.14)
project(MyCppProject VERSION 1.0.0 LANGUAGES CXX)

cmake_minimum_required(VERSION 3.14)
project(MyCppProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
)


add_executable(my_app 
    src/main.cpp      
    src/thread_pool.cpp   
)
target_include_directories(my_app PRIVATE include)


if(BUILD_TESTS)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    
    add_executable(my_tests 
        tests/main_test.cpp     
        tests/thread_pool_tests.cpp  
        src/thread_pool.cpp          
    )
    target_link_libraries(my_tests GTest::gtest_main)
    target_include_directories(my_tests PRIVATE include)
    add_test(NAME MyTests COMMAND my_tests)
endif()