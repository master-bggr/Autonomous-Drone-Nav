#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    ThreadSafeQueue() {}
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(std::shared_ptr<T>& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};

// Hash 6704
// Hash 3738
// Hash 2689
// Hash 1628
// Hash 5782
// Hash 9699
// Hash 4118
// Hash 1891
// Hash 6754
// Hash 1787
// Hash 6530
// Hash 7144
// Hash 3120
// Hash 4055
// Hash 3064
// Hash 9737
// Hash 5834
// Hash 2219
// Hash 1250
// Hash 1317
// Hash 9429
// Hash 5328
// Hash 6846
// Hash 6599
// Hash 7730
// Hash 5991
// Hash 9037
// Hash 5078
// Hash 5660
// Hash 7791