#ifndef BODY_CONTROLLER_H
#define BODY_CONTROLLER_H

#include <SDL.h>
#include <controller.h>
#include <controller_general.h>
#include <message_queue.h>
#include <player.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <stdexcept>
#include <thread>

/**
 * @brief Controll the player jumping with yourself.
 * Extend GeneralController class.
 */
class BodyController : GeneralController {
 public:
  /**
   * @brief Destroy the Body Controller object
   * Wait the thread to finish before destroying the obj
   */
  ~BodyController();

  /**
   * @brief start a thread that reads the camera and tries to guess the motion
   *
   * @param device_id camera id (0,1... ls /dev/video*)
   */
  void start(int device_id = 0);

  /**
   * @brief init the pure virtual function of the parent class
   * GeneralController. This is an interface between the camera thread and the
   * game thread.
   *
   * @param running boolean coming from the main loop, if the player died this
   * will be false
   * @param player  GameObject for the player
   */
  void HandleInput(bool &running, Player &player) override;

 private:
  /**
   * @brief detect a blob in the image and estiamte the motion of the blob wrt
   * the previous blob. The image is the result of the difference between a
   * previous frame and the current frame.
   */
  void computeCommand();

  /**
   * @brief Method that is called in the thread.
   * Read the camera frames at the id=device_id
   *
   */
  void readCamera();

  cv::Mat frame_, prev_frame_, difference_, show_;
  cv::VideoCapture cap_;
  bool stop_ = false;

  /**
   * @brief Communication between the main game thread and the camera thread.
   */
  Jump::MessageQueue<Player::Action> queue_;
  Jump::MessageQueue<bool> stop_camera_;

  int image_width_, image_height_;
  /**
   * @brief these parameters are used to refresh the background substruction
   */
  int counter_update_ = 0;
  const int back_update_rate_ = 1;

  /**
   * @brief previous center of the blob
   */
  cv::Point prev_center_;

  /**
   * @brief camera thread
   */
  std::thread *thr_;
};

#endif