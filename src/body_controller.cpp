#include "body_controller.h"

BodyController::~BodyController() {
  // wait for the thread to finish before
  // destroying the obj
  thr_->join();
};

void BodyController::start(int device_id) {
  cv::namedWindow("Movements tracker", cv::WINDOW_AUTOSIZE);

#ifdef DEBUG
  cv::namedWindow("Blob detection", cv::WINDOW_AUTOSIZE);
#endif
  // open camera
  cap_.open(device_id, cv::CAP_ANY);
  // if cannot open the camera throw an exception
  if (!cap_.isOpened()) {
    throw std::runtime_error("Cannot read the camera...");
  }
  // start the thread
  thr_ = new std::thread(&BodyController::readCamera, this);
}

void BodyController::readCamera() {
  // to check if we are reading the first image
  bool not_first_ = false;

  // itereate untill the game end
  while (!stop_) {
    // read camera new colored frame
    cap_ >> frame_;

    // store the colored image in show_, frame_ is going to be converted in a
    // gray scale image
    show_ = frame_;

    // throw an exception if we are not able to read the image
    if (frame_.empty()) throw std::runtime_error("Cannot read the camera...");

    // if not the first frame we can start doing operation on the image
    if (not_first_) {
      // check whether we can substruct the previous frame according to the
      // back_update_rate_ we set
      if (counter_update_ == back_update_rate_) {
        // reset the counter
        counter_update_ = 0;

        // covert the frame to gray scale
        cvtColor(frame_, frame_, cv::COLOR_BGR2GRAY);

        // substract the previous frame to the current one
        difference_ = frame_ - prev_frame_;

        // update frame
        prev_frame_ = frame_;

        // compute the command to be sent
        computeCommand();

        // show the image
        cv::imshow("Movements tracker", show_);
#ifdef DEBUG
        cv::imshow("Blob detection", difference_);
#endif
        cv::waitKey(1);
      } else {
        // send player action STAY if no other commands are computed
        queue_.send(std::move(Player::Action::STAY));
      }

      // check whether the game has ended
      stop_ = stop_camera_.receive();

    } else {
      // set we have already received a frame
      not_first_ = true;
      // set image size
      image_width_ = difference_.size().width;
      image_height_ = difference_.size().height;

      // init prev_center of the blob to the center of the image
      prev_center_ = cv::Point((int)image_width_ / 2, (int)image_height_ / 2);
    }

    // update the counter
    counter_update_++;
  }
}

void BodyController::computeCommand() {
  // set the command to nothing
  Player::Action cmd = Player::Action::STAY;

  // threshold the image
  cv::threshold(difference_, difference_, 50, 255, cv::THRESH_BINARY);

  // calculate the centroid of the blob
  cv::Moments m = moments(difference_, true);
  int x = m.m10 / m.m00;
  int y = m.m01 / m.m00;
  cv::Point curr_center(x, y);

  // compute the difference between the prev and curr point to check the
  // direction of movement
  cv::Point diff = curr_center - prev_center_;

  // check the norm of the movement, is it enoght or it is noise?
  double norm = cv::norm(diff);

  if (norm > 50 && norm < 100) {
    cv::circle(show_, prev_center_, 5, cv::Scalar(0, 0, 255), -1);
    cv::arrowedLine(show_, prev_center_, curr_center, cv::Scalar(0, 0, 255));
    // the body is moving up or down
    if (abs(diff.x) < abs(diff.y)) {
      // negative y means movemnt to the top
      if (diff.y < 0) {
        cmd = Player::Action::JUMP;
      }
    }
  }
  // update the center position
  prev_center_ = curr_center;
  // send the command
  queue_.send(std::move(cmd));
}

void BodyController::HandleInput(bool &running, Player &player) {
  SDL_Event e;
  if (SDL_PollEvent(&e) && e.type == SDL_QUIT) {
    running = false;
    stop_camera_.send(true);
  } else {
    stop_camera_.send(false);
    ChangeDirection(player, queue_.receive());
  }
}