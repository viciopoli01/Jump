#ifndef BODY_CONTROLLER_H
#define BODY_CONTROLLER_H

#include <SDL.h>
#include <controller.h>
#include <controller_general.h>
#include <snake.h>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <stdexcept>
#include <thread>
#include <player.h>


template <typename T>
class MessageQueue {
 public:
  void send(T &&message) {
    std::lock_guard<std::mutex> lck(_mtx);
    // _queue.clear();
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

class BodyController : GeneralController {
 public:
  ~BodyController() { thr_->join(); };
  void endGame() { end_game_ = true; }
  void start(int device_id = 0);

  void waitForCommands();
  void HandleInput(bool &running, Player &player) override;

 private:
  void computeCommand();
  void drawBox();
  void readCamera();

  cv::Mat frame_, prev_frame_, difference_;
  cv::VideoCapture cap_;
  bool end_game_ = false;

  MessageQueue<Player::Action> queue_;

  int margin_x_, margin_y_, image_width_, image_height_;
  int counter_update_ = 0;
  const int back_update_rate_ = 2;

  cv::Point prev_center_;

  std::thread *thr_;
};

#endif