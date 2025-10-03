# Apps/demos
add_executable(main_adjlist main_adjlist_demo.cpp)
target_link_libraries(main_adjlist PRIVATE search)

add_executable(main_user_custom_graph main_user_custom_graph.cpp)
target_link_libraries(main_user_custom_graph PRIVATE search)
