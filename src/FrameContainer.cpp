//
// Created by cristobal on 07-04-18.
//

#include <iostream>
#include "FrameContainer.h"
#include <unistd.h>
#include <fstream>

FrameContainer::FrameContainer() {
}

FrameContainer::FrameContainer(cv::Mat &frame, std::vector<vmat> &histograms, int norm,
                               double threshold, int real_frame_position) :
        frame(frame),
        histograms(histograms),
        norm(norm),
        threshold(threshold),
        real_frame_position(real_frame_position) {
}

FrameContainer::FrameContainer(cv::Mat &frame, int norm, double threshold, int real_frame_position) :
        norm(norm), threshold(threshold), real_frame_position(real_frame_position) {

  cv::cvtColor(frame, this->frame, cv::COLOR_BGR2GRAY);
  cv::resize(this->frame, this->frame, cv::Size(400, 300));
  cv::Size s = this->frame.size();
  int rows = s.height;
  int cols = s.width;
  int rows_mini = rows / IMAGE_PARTS ;
  int cols_mini = cols / IMAGE_PARTS ;

  for (int i = 0; i < IMAGE_PARTS; i++){
    //vmat row_minis;
    vmat aux_hist;
    int y_start = i*rows_mini;
    int roi_height = std::min<int>(rows_mini, rows - y_start);

    for(int j = 0; j < IMAGE_PARTS; j++){
      int x_start = j*cols_mini;
      int roi_width = std::min<int>(cols_mini, cols - x_start);

      cv::Rect currentROI(x_start, y_start, roi_width, roi_height);
      cv::Mat cropped = this->frame(currentROI);
      cv::Mat histo_cropped = getHistogram(cropped);
      aux_hist.push_back(histo_cropped);
    }
    this->histograms.push_back(aux_hist);
  }
}

FrameContainer::FrameContainer(cv::Mat &frame, int real_frame_position) :
        FrameContainer(frame, cv::NORM_L1, DEFAULT_LOWER_THRESHOLD, real_frame_position) {
}



cv::Mat FrameContainer::getHistogram(cv::Mat &whichImage) {
  cv::Mat toSave;
  int histSize = 16;
  float range[] = {0, 16};
  const float *histRange = {range};
  int channels[] = {0};
  cv::calcHist(&whichImage, 1, channels, cv::Mat(), toSave, 1, &histSize, &histRange, true, false);
  cv::normalize(toSave, toSave);

  return toSave;
}


std::vector<vmat> &FrameContainer::getHistograms() {
  return this->histograms;
}

double FrameContainer::distanceTo(FrameContainer &otherContainer) {
  std::vector<vmat> &theirHistograms = otherContainer.getHistograms();
  std::vector<vmat> &mineHistograms = this->getHistograms();
  double sum = 0;
  auto N = (int) mineHistograms.size();
  auto M = (int) mineHistograms[0].size();
  double max_dist = 1;
  for(int i = 0; i < mineHistograms.size(); i++){
    for(int j = 0; j < mineHistograms[i].size(); j++){
      cv::Mat &mine = mineHistograms[i][j];
      cv::Mat &theirs = theirHistograms[i][j];
      double dist = cv::compareHist(mine, theirs, CV_COMP_CHISQR);
      max_dist = std::max(dist, max_dist);

      //std::cout << "chidist: " << dist << std::endl;


      if(dist > DEFAULT_LOWER_THRESHOLD){
        sum++;
      }

      //sum+= dist;
    }
  }
  return sum / (N*M);
}

cv::Mat &FrameContainer::getFrame() {
  return this->frame;
}

const int grab_times[] = {5, 15, 25};
const int FPS = 30;
vecFC getVecFC(cv::VideoCapture &videoCapture){
  vecFC output;
  cv::Mat frame;
  long counter = 0;
  int which = 0;
  long offset = 0;
  int frame_count = (int)(videoCapture.get(cv::CAP_PROP_FRAME_COUNT));
  double fps = videoCapture.get(cv::CAP_PROP_FPS);

  std::cout << "frame count istristream s: " << frame_count << std::endl;
  std::cout << "fps is: " << fps << std::endl;
  int real_counter = -1;
  while(videoCapture.grab()){
    real_counter++;
    if(!videoCapture.retrieve(frame)){
      offset++;
      continue;
    }
    auto where  = (int) (counter % FPS);
    if(where == (grab_times[which] + offset) % FPS){
      FrameContainer frameContainer(frame, real_counter);
      output.push_back(frameContainer);

      which++;
      which %= 3;
    }
    if(counter % 20000 == 0){
      std::cout << "counter = " << counter << std::endl;
    }
    counter++;
    offset = 0;
  }
  return output;
}

vecFC getVecFC(const std::string &storedSerialized) {
  std::ifstream ifs(storedSerialized);
  std::cout << "trying to read filename: '" << storedSerialized << "'" << std::endl;
  if(!ifs){
    std::cout << "could not read ifs of " << storedSerialized << std::endl;
  }
  vecFC out;
  boost::archive::binary_iarchive ia(ifs);
  ia & out;
  return out;
}

void saveVecFC(const std::string &storedSerialized, vecFC &vecFc) {
  std::ofstream ofs(storedSerialized);
  boost::archive::binary_oarchive oa(ofs);
  oa << vecFc;
}

int FrameContainer::getRealFramePosition() {
  return this->real_frame_position;
}
