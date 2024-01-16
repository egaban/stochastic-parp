cmake_minimum_required(VERSION 3.26)

project(StochasticPARP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -fno-omit-frame-pointer")
endif()

include(FetchContent)

# Fetch Google Test
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

message("Fetching Toml++...")
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)
message("Toml++ fetched")

# Used so we can remove all debug log calls on release.
if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
  message("Building with debug logs")
  add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)
endif()

add_subdirectory(src/data_structures)

add_executable(main src/main.cpp)

target_link_libraries(main 
  PRIVATE 
    data_structures
    tomlplusplus::tomlplusplus
)

