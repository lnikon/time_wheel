#pragma once

#include <memory>
#include <iostream>

template <class ValueType>
struct RingBuffer
{
    RingBuffer() = delete;
    ~RingBuffer() = default;

    RingBuffer(const RingBuffer& other) = delete;
    const RingBuffer& operator=(const RingBuffer& other) = delete;

    RingBuffer(const std::size_t capacity)
    {
        try 
        {
            capacity_ = capacity;
            buffer_ = std::make_unique<ValueType[]>(capacity_);
        }
        catch(const std::bad_alloc& e)
        {
            std::cerr << "[ERROR] Exception has been thrown in RingBuffer(const std::size_t)\n";
            e.what();
            throw;
        }
    }

    RingBuffer(RingBuffer& other)
        : buffer_{std::move(other.buffer_)},
        size_{std::move(other.size_)},
        capacity_{std::move(other.capacity_)},
        head_{std::move(other.head_)},
        tail_{std::move(other.tail_)},
        full_{std::move(other.tail_)}
    {
        other.buffer_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.head_ = 0;
        other.tail_ = 0;
        other.full = false;
    }

    const RingBuffer& operator=(RingBuffer&& other)
    {
        buffer_ = std::move(other.buffer_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        head_ = other.head_;
        tail_ = other.tail_;
        full_ = other.full_;

        other.buffer_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.head_ = 0;
        other.tail_ = 0;
        other.full = false;
    }

    void push(const ValueType& value)
    {
        buffer_[head_] = value;
        
        if(full_)
        {
            tail_ = (tail_ + 1) % capacity_;
        }

        head_ = (head_ + 1) % capacity_;
        full_ = (head_ == tail_);
    }

    void pop()
    {
        if(empty())
        {
            return;
        }

        full_ = false;
        tail_ = (tail_ + 1) % capacity_;
    }

    ValueType head() const
    {
        auto value = buffer_[head_];

        return value;
    }

    ValueType tail() const
    {
        auto value = buffer_[head_];

        return value;
    }

    bool empty() const
    {
        return (!full_ && (head_ == tail_));
    }

    bool full() const
    {
        return full_;
    }

    std::size_t size() const
    {
        std::size_t size = capacity_;

        if(!full_)
        {
            size = head_ - tail_;
            if(head_ < tail_)
            {
                size = capacity_ + size; 
            }
        }

        return size;
    }

    void printBuffer() const
    {
        auto start = std::min(head_, tail_);
        auto end = std::max(head_, tail_);

        for(; start < end; ++start)
        {
            std::cout << buffer_[start] << ' ';
        }
        std::cout << std::endl;
    }

    private:
    std::unique_ptr<ValueType[]> buffer_{nullptr};
    std::size_t size_{0};
    std::size_t capacity_{0};
    std::size_t head_{0};
    std::size_t tail_{0};
    bool full_{false};
};
