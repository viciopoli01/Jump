#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <condition_variable>
#include <deque>
#include <mutex>

namespace Jump {
template <typename T>
class MessageQueue {
 public:
  void send(T &&message) {
    std::lock_guard<std::mutex> lck(_mtx);
    _queue.clear();
    _queue.push_back(std::move(message));
    _cond.notify_one();
  }

  T receive() {
    std::unique_lock<std::mutex> lck(_mtx);
    _cond.wait(lck, [this] { return !_queue.empty(); });

    T msg = std::move(_queue.back());
    _queue.pop_back();

    return msg;
  }

 private:
  std::deque<T> _queue;
  std::condition_variable _cond;
  std::mutex _mtx;
};
}  // namespace Jump

#endif