cmake_minimum_required(VERSION 3.26)

project(StochasticPARP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

# Used so we can remove all debug log calls on release.
if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
  message("Building with debug logs")
  add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)
endif()

add_subdirectory(src/data_structures)

add_executable(main src/main.cpp)

target_link_libraries(main data_structures)

