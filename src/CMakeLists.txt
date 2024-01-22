add_library(StochasticPARP
  config.cpp
  parser.cpp
  model.cpp
)

target_include_directories(
  StochasticPARP
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GUROBI_INCLUDE_DIRS}
)

target_link_libraries(StochasticPARP
  PUBLIC
    data_structures
  PRIVATE
    tomlplusplus::tomlplusplus
    ${GUROBI_CXX_LIBRARY}
    ${GUROBI_LIBRARY}
    ${GUROBI_CXX_LIBRARY}
)
