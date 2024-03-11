#pragma once

#include <atomic>
#include <cstdio>
#include <vector>

namespace ds {

template <typename T>
class InMemoryLocklessQueue
{
   public:
    InMemoryLocklessQueue(std::size_t);

    auto enqueue(const T& data) -> void;
    auto enqueue(T&& data) -> void;

    [[nodiscard]] auto dequeue() -> const T*;
    [[nodiscard]] auto front() -> const T*;
    [[nodiscard]] auto empty() -> bool;
    [[nodiscard]] auto capacity() const -> std::size_t;

   private:
    struct Node
    {
        T data;
        std::size_t sequence_number{};
    };

    std::atomic_uint64_t tail_{1};
    std::atomic_uint64_t head_{1};

    std::size_t size_;
    std::vector<Node> storage_;
};

}  // namespace ds

#include "ds/in_memory_lockless_queue.hpp"
