cmake_minimum_required(VERSION 3.20)

project(StochasticPARP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Option to enable/disable building tests
option(BUILD_TESTING "Build tests" ON)

if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -fno-omit-frame-pointer")
endif()

# Fetch Google Test
include(FetchContent)

if (BUILD_TESTING)
  message("Fetching Google Test...")
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.x
  )
  FetchContent_MakeAvailable(googletest)

  enable_testing()
  message("Google test fetched")
endif()

message("Fetching Spdlog...")
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.x
)
FetchContent_MakeAvailable(spdlog)
message("Spdlog fetched")

add_subdirectory(src/data_structures)

add_executable(main src/main.cpp)

