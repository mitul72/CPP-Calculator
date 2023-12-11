cmake_minimum_required(VERSION 3.13)  # CMake version check
project(kafkacpp)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard
set(CMAKE_BUILD_TYPE Debug)


# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES src/main.cpp)
# set(TEST_SOURCES tests)
set(CPPKAFKA_BUILD_SHARED 0)
find_package(Boost COMPONENTS program_options REQUIRED)

file(GLOB TEST_SOURCES
     "tests/*.cpp"
)

file(GLOB_RECURSE LIB_SOURCES
     "src/lib/calculator/*.cpp"
)



set(GTEST_GIT_TAG v1.13.0)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG ${GTEST_GIT_TAG}
)

set(CPPKAFKA_DISABLE_EXAMPLES ON CACHE INTERNAL "Turn off examples")
set(CPPKAFKA_DISABLE_TESTS ON CACHE INTERNAL "Turn off tests")


FetchContent_Declare(
  CppKafka
  GIT_REPOSITORY https://github.com/mfontanini/cppkafka.git
  GIT_TAG        master
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(CppKafka googletest)

add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests
        GTest::gtest_main
)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(kafkacpp ${SOURCE_FILES})
target_link_libraries(kafkacpp
        ${CPPKAFKA_LIBRARY}
        Boost::program_options
)
target_include_directories(kafkacpp PUBLIC src/lib/calculator)
