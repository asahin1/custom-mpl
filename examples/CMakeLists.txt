# Apps/demos
add_executable(main_adjlist main_adjlist_demo.cpp)
target_link_libraries(main_adjlist PRIVATE custom_mpl::custom_mpl)

add_executable(main_large_graph main_large_graph_demo.cpp)
target_link_libraries(main_large_graph PRIVATE custom_mpl::custom_mpl)
