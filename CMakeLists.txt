cmake_minimum_required(VERSION 3.13)  # CMake version check
project(kafkacpp)               # Create project "simple_example"
set(CMAKE_CXX_COMPILER ${CPP_COMPILER})
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard
set(CMAKE_BUILD_TYPE Debug)


# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES src/main.cpp)
# set(TEST_SOURCES tests)
set(CPPKAFKA_BUILD_SHARED 0)
find_package(Boost COMPONENTS unit_test_framework program_options REQUIRED)

# Copy config.json to the build folder
configure_file(${CMAKE_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/config.json COPYONLY)

file(GLOB TEST_SOURCES
     "tests/*.cpp"
)

file(GLOB KAFKA_SOURCES
  "src/lib/kafka/*.cpp"
)

file(GLOB KAFKA_LIB
  "src/lib/kafka/config_json/config_json.cpp"
)
add_library(kafkalib ${KAFKA_LIB})
file(GLOB_RECURSE LIB_SOURCES
     "src/lib/calculator/*.cpp"
)

add_library(lib ${LIB_SOURCES})


include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.10.4  # Specify the version tag you want to use
)

FetchContent_MakeAvailable(nlohmann_json)

target_link_libraries(kafkalib PRIVATE nlohmann_json::nlohmann_json)

set(GTEST_GIT_TAG v1.13.0)

# cxxopts for argparse
FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
    GIT_TAG v2.2.1
)

FetchContent_MakeAvailable(cxxopts)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG ${GTEST_GIT_TAG}
)

set(RDKAFKA_BUILD_EXAMPLES OFF ON CACHE INTERNAL "Turn off examples")
set(RDKAFKA_BUILD_TESTS OFF CACHE INTERNAL "Turn off tests")
FetchContent_Declare(
    librdkafka
    GIT_REPOSITORY https://github.com/confluentinc/librdkafka
    GIT_TAG        v2.3.0
)


set(CPPKAFKA_DISABLE_EXAMPLES ON CACHE INTERNAL "Turn off examples")
set(CPPKAFKA_DISABLE_TESTS ON CACHE INTERNAL "Turn off tests")


FetchContent_Declare(
  CppKafka
  GIT_REPOSITORY https://github.com/mfontanini/cppkafka.git
  GIT_TAG        v0.3.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(CppKafka googletest librdkafka)
# add_subdirectory(${cppkafka_SOURCE_DIR})
add_executable(tests ${TEST_SOURCES})
target_link_libraries(lib
  ${Boost_LIBRARIES}
)
target_include_directories(lib PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(tests
        GTest::gtest_main
        ${Boost_LIBRARIES}
        Boost::unit_test_framework
        lib
)


target_include_directories(tests PUBLIC src/lib/calculator)
# Add executable target with source files listed in SOURCE_FILES variable
add_executable(kafkacpp ${SOURCE_FILES})

target_include_directories(kafkacpp PUBLIC src/lib/calculator ${Boost_INCLUDE_DIRS})  # Include CppKafka source directory

target_include_directories(tests PUBLIC src/lib/calculator ${Boost_INCLUDE_DIRS})  # Include CppKafka source directory


target_link_libraries(kafkacpp
  ${Boost_LIBRARIES}
)

add_executable(producer-kafka src/lib/kafka/producer.cpp)
target_include_directories(producer-kafka PRIVATE 
  ${nlohmann_json_SOURCE_DIR}/single_include   
  src/lib/kafka/config_json
)


target_link_libraries(producer-kafka
    cppkafka
    rdkafka
    nlohmann_json::nlohmann_json
    kafkalib
)
add_executable(consumer-kafka src/lib/kafka/consumer.cpp)
target_include_directories(consumer-kafka PRIVATE 
  ${nlohmann_json_SOURCE_DIR}/single_include
  src/lib/kafka/config_json
  src/lib/calculator
)

target_link_libraries(consumer-kafka
    cppkafka
    rdkafka
    nlohmann_json::nlohmann_json
    kafkalib
)
