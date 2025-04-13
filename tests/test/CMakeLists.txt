set(SOURSE test_main.cpp test_trees.cpp test_avlTrees.cpp)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../gtest")
add_executable(tests ${SOURSE})

target_link_libraries(tests gtest)
