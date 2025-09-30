cmake_minimum_required(VERSION 3.16)
project(custom-mpl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library target
add_library(search)
target_include_directories(search PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_sources(search PRIVATE
  src/search/utils/stats.cpp
)

# Apps/demos
add_executable(main_adjlist src/apps/main_adjlist_demo.cpp)
target_link_libraries(main_adjlist PRIVATE search)

add_executable(main_user_custom_graph src/apps/main_user_custom_graph.cpp)
target_link_libraries(main_user_custom_graph PRIVATE search)

enable_testing()
add_subdirectory(tests)