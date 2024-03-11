#pragma once

#include <atomic>
#include "ds/in_memory_lockless_queue.h"

#include "utils/math.h"

namespace ds {

template <typename T>
InMemoryLocklessQueue<T>::InMemoryLocklessQueue(std::size_t size) : size_(utils::nearest_greater_power_of_2(size))
{
    storage_.resize(size_);
}

template <typename T>
auto InMemoryLocklessQueue<T>::enqueue(const T& data) -> void
{
    auto tail = tail_.fetch_add(1, std::memory_order::acq_rel);
    auto index = tail & (size_ - 1);

    storage_[index].data = data;
    asm volatile("" ::: "memory");
    storage_[index].sequence_number = tail + 1;
}

template <typename T>
auto InMemoryLocklessQueue<T>::enqueue(T&& data) -> void
{
    auto tail = tail_.fetch_add(1, std::memory_order::acq_rel);
    auto index = tail & (size_ - 1);

    storage_[index].data = std::move(data);
    asm volatile("" ::: "memory");
    storage_[index].sequence_number = tail;
}

template <typename T>
auto InMemoryLocklessQueue<T>::capacity() const -> std::size_t
{
    return size_;
}

template <typename T>
auto InMemoryLocklessQueue<T>::front() -> const T*
{
    auto head = head_.load(std::memory_order::relaxed);
    auto index = head & (size_ - 1);

    return &storage_[index].data;
}

template <typename T>
auto InMemoryLocklessQueue<T>::dequeue() -> const T*
{
    auto head = head_.fetch_add(1, std::memory_order::relaxed);
    auto index = head & (size_ - 1);

    return &storage_[index].data;
}

template <typename T>
auto InMemoryLocklessQueue<T>::empty() -> bool
{
    const auto head = head_.load(std::memory_order::acquire);
    const auto index = head & (size_ - 1);

    return storage_[index].sequence_number < head;
}

}  // namespace ds
