include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.6.0
)
FetchContent_MakeAvailable(catch2)

add_executable(unit_tests
  test_dijkstra_basic.cpp
  test_astar_admissible.cpp
  test_priority_queues.cpp
  test_edge_cases.cpp
  test_solve_astar_easy.cpp
)
target_link_libraries(unit_tests PRIVATE search Catch2::Catch2WithMain)
add_test(NAME unit_tests COMMAND unit_tests)
