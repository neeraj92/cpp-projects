#include <gtest/gtest.h>

#include "ds/in_memory_lockless_queue.h"

namespace ds::test {

TEST(LocklessQueueTests, GIVEN_queue_initialized_WHEN_empty_called_THEN_it_is_empty)
{
    InMemoryLocklessQueue<int> queue(1000);
    EXPECT_EQ(queue.capacity(), 1024);
}

TEST(
    LockLessQueueTests,
    GIVEN_queue_initialized_WHEN_elements_pushed_in_and_then_dequeued_THEN_verify_all_elements_are_received)
{
    InMemoryLocklessQueue<int> queue(1000);

    for (auto i = 0; i < 10; i++) {
        queue.enqueue(i);
    }

    for (auto i = 0; i < 10; i++) {
        ASSERT_FALSE(queue.empty());
        auto value = queue.dequeue();
        ASSERT_TRUE(value != nullptr);
        ASSERT_EQ(*value, i);
    }
}

TEST(
    LockLessQueueTests,
    GIVEN_queue_initialized_with_complex_data_type_WHEN_elements_pushed_in_and_dequeued_THEN_verify_correctness_of_data)
{
    InMemoryLocklessQueue<std::string> queue(1000);
    for (auto i = 0; i < 10; i++) {
        queue.enqueue(std::to_string(i));
    }

    for (auto i = 0; i < 10; i++) {
        ASSERT_FALSE(queue.empty());
        auto value = queue.dequeue();
        ASSERT_TRUE(value != nullptr);
        ASSERT_EQ(*value, std::to_string(i));
    }
}

}  // namespace ds::test
