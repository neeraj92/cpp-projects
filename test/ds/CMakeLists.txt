add_executable(test.ds test_in_memory_lockless_queue.cpp)
target_link_libraries(test.ds GTest::Main GTest::GTest skunkwork.ds)

add_test(Tests test.ds)
