#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <cstddef>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <optional>

template <typename T>
class ThreadSafeQueue {
    private:
        std::deque<T> deque_;
        size_t maxSize_;
        mutable std::mutex mutex_;
        std::condition_variable cv_;
        bool stopped_ = false;

    public:
        explicit ThreadSafeQueue(size_t maxSize) : maxSize_(maxSize) {}

        size_t size() const {
            std::lock_guard<std::mutex> guard(mutex_);
            return deque_.size();
        }

        void stop() {
            {
                std::lock_guard<std::mutex> guard(mutex_);
                stopped_ = true;
            }
            cv_.notify_all();
        }

        void push(T value) {
            std::lock_guard<std::mutex> guard(mutex_);

            if (stopped_) {
                return;
            }

            if (deque_.size() >= maxSize_) {
                deque_.pop_front();
            }

            deque_.push_back(std::move(value));
            cv_.notify_one();
        }

        std::optional<T> pop() {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [&] { return !deque_.empty() || stopped_; });

            if (deque_.empty() && stopped_) {
                return std::nullopt;
            }

            T value(std::move(deque_.front()));
            deque_.pop_front();
            return value;
        }

        std::optional<T> peek() {
        
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [&] { return !deque_.empty() || stopped_; });

            if (deque_.empty() && stopped_) {
                return std::nullopt;
            }

            return deque_.front();

        };

        std::deque<T> extractAll() {

            std::deque<T> result;

            std::lock_guard<std::mutex> guard(mutex_);
            result.swap(deque_);
            
            return result;

        };
};

#endif