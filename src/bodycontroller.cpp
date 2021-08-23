#include "bodycontroller.h"

void BodyController::start(int device_id) {
#ifdef DEBUG
  cv::namedWindow("Movements tracker", cv::WINDOW_AUTOSIZE);
#endif
  // open selected camera using selected API
  cap_.open(device_id, cv::CAP_ANY);
  // check if we succeeded
  if (!cap_.isOpened()) {
    throw std::runtime_error("Cannot read the camera...");
  }
  thr_ = new std::thread(&BodyController::readCamera, this);
}

void BodyController::readCamera() {
  bool not_first_ = false;
  while (!end_game_) {
    // wait for a new frame from camera and store it into 'frame'
    cap_ >> frame_;
    cvtColor(frame_, frame_, cv::COLOR_BGR2GRAY);

    // check if we succeeded
    if (frame_.empty()) {
      throw std::runtime_error("Cannot read the camera...");
    }

    if (not_first_ && counter_update_ == back_update_rate_) {
      counter_update_ = 0;
      difference_ = frame_ - prev_frame_;
      computeCommand();

      drawBox();
      cv::imshow("Movements tracker", difference_);
      cv::waitKey(1);

    } else {
      not_first_ = true;
      image_width_ = difference_.size().width;
      image_height_ = difference_.size().height;
      margin_x_ = (int)(0.3 * image_width_);
      margin_y_ = (int)(0.3 * image_height_);
      prev_center_ = cv::Point((int)image_width_ / 2, (int)image_height_ / 2);
    }
    counter_update_++;
    prev_frame_ = frame_;
  }
}

void BodyController::drawBox() {
  cv::Rect r =
      cv::Rect((int)(image_width_ / 2) - margin_x_,
               (int)(image_height_ / 2) - margin_y_, margin_x_, margin_y_);

  cv::rectangle(difference_, r, cv::Scalar(255, 0, 0), 1, 8, 0);
}

void BodyController::computeCommand() {
  // set the command to nothing
  Commands cmd = NOTHING;

  // threshold the image
  cv::threshold(difference_, difference_, 50, 255, cv::THRESH_BINARY);

  // calculate the centroid of the blob
  cv::Moments m = moments(difference_, true);
  int x = m.m10 / m.m00;
  int y = m.m01 / m.m00;
  cv::Point curr_center = cv::Point(x, y);

  // convert the image to 3 channels, in such a way we can color it
  cv::cvtColor(difference_, difference_, cv::COLOR_GRAY2BGR);
  std::cout << "CENTER : " << prev_center_.x << ", " << prev_center_.y
            << std::endl;
  cv::circle(difference_, prev_center_, 5, cv::Scalar(0, 0, 255), -1);

  // compute the difference between the prev and curr point to check the
  // direction of movement
  cv::Point diff = curr_center - prev_center_;

  // check the norm of the movement, is it enoght or it is noise?
  double norm = cv::norm(diff);
  if (norm > 200) prev_center_ = curr_center;

  // the body is moving to the left or the right
  if (abs(diff.x) > abs(diff.y) && prev_command_ != LEFT &&
      prev_command_ != RIGHT) {
    // negative x means movemnt to the right
    if (diff.x < 0) {
      cmd = RIGHT;
    }

    // positive x means movemnt to the left
    if (diff.x > 0) {
      cmd = LEFT;
    }
  }

  // the body is moving up or down
  if (abs(diff.x) < abs(diff.y) && prev_command_ != UP &&
      prev_command_ != DOWN) {
    // negative y means movemnt to the top
    if (diff.y < 0) {
      cmd = UP;
    }

    // positive x means movemnt to the bottom
    if (diff.y > 0) {
      cmd = DOWN;
    }
  }

#ifdef DEBUG
  std::cout << "Norm: " << norm << std::endl;
  std::cout << "Dir: " << cmd << std::endl;
#endif
  prev_center_ = curr_center;
  prev_command_ = cmd;
  queue_.send(std::move(cmd));
}

void BodyController::HandleInput(bool &running, Player &player) {
  SDL_Event e;
  if (SDL_PollEvent(&e) && e.type == SDL_QUIT) {
    running = false;
    end_game_ = true;
  }
  switch (queue_.receive()) {
    case UP:
      std::cout << "UP" << std::endl;
      ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
      break;
    case DOWN:
      std::cout << "DOWN" << std::endl;
      ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
      break;
    case LEFT:
      std::cout << "LEFT" << std::endl;
      ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
      break;
    case RIGHT:
      std::cout << "RIGHT" << std::endl;
      ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
      break;
    default:
      std::cout << "NO COMMAND" << std::endl;
  }
}