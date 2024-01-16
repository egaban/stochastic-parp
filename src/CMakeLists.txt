add_library(StochasticPARP
  parser.cpp
)

target_include_directories(
  StochasticPARP
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(StochasticPARP
  PUBLIC
    data_structures
)
