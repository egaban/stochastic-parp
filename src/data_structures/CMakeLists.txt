add_library(data_structures
  src/graph.cpp
)

target_include_directories(data_structures
  PUBLIC
    include/
  PRIVATE
    src
)

target_link_libraries(data_structures
  PUBLIC
    spdlog::spdlog
)

if (BUILD_TESTING)
  add_subdirectory(test)
endif()

