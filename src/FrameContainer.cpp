//
// Created by cristobal on 07-04-18.
//

#include <iostream>
#include "FrameContainer.h"
#include <unistd.h>
#include <fstream>
#include <boost/progress.hpp>

FrameContainer::FrameContainer() {
}



FrameContainer::FrameContainer(cv::Mat &frame, int real_frame_position) : real_frame_position(real_frame_position) {
  cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
  cv::resize(frame, frame, cv::Size(256, 256));
  cv::Size s = frame.size();
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
      cv::Mat cropped = frame(currentROI);
      cv::Mat detected_edges;

      cv::blur(cropped, detected_edges, cv::Size(3, 3));

      int ratio = 3;
      int kernel_size = 3;
      int lower_th = 30;
      cv::Canny(detected_edges, detected_edges, lower_th, lower_th*ratio, kernel_size);
      cv::Mat dst;
      cropped.copyTo(dst, detected_edges);
      cropped = dst;
      /*
      //sobelizado
      cv::Mat sobel_x, sobel_y, grad;

      int ddepth = CV_32F;
      cv::Sobel(cropped, sobel_x, ddepth, 1, 0);
      cv::Sobel(cropped, sobel_y, ddepth, 0, 1);
      cv::convertScaleAbs(sobel_x, sobel_x);
      cv::convertScaleAbs(sobel_y, sobel_y);
      cv::addWeighted(sobel_x, 0.5, sobel_y, 0.5, 0, cropped);
      // end sobelizado
      */

      cv::Mat histo_cropped = getHistogram(cropped);
      aux_hist.push_back(histo_cropped);
    }
    this->histograms.push_back(aux_hist);
  }
}

FrameContainer::FrameContainer(std::vector<vmat> &histograms, int real_frame_position) :
        histograms(histograms), real_frame_position(real_frame_position){

}

cv::Mat collapseHistogramXAxis(cv::Mat &original, int nextRange){
  cv::Mat out = cv::Mat::zeros(cv::Size(1, nextRange), original.type());
  int currentRange = original.rows;
  int step = currentRange/nextRange;
  float acc = original.at<float>(0, 0);
  int counter = 0;
  for(int i = 1; i < currentRange; i++){
    if(i % step == 0){
      out.at<float>(counter, 0) = acc/step;
      acc = 0;
      counter++;
    }
    acc += original.at<float>(i, 0);
  }
  if(acc > 0){
    out.at<float>(counter, 0) = acc/step;
  }
  return out;
}
cv::Mat FrameContainer::getHistogram(cv::Mat &whichImage) {
  cv::Mat toSave;
  int histSize = 256;
  float range[] = {0, 256};
  const float *histRange = {range};
  int channels[] = {0};
  cv::calcHist(&whichImage, 1, channels, cv::Mat(), toSave, 1, &histSize, &histRange, true, false);
  toSave = collapseHistogramXAxis(toSave, 2);
  cv::normalize(toSave, toSave);

  return toSave;
}


std::vector<vmat> &FrameContainer::getHistograms() {
  return this->histograms;
}



const int grab_times[] = {1, 10, 25};
const int FPS = 30;
vecFC getVecFC(cv::VideoCapture &videoCapture){
  vecFC output;
  cv::Mat frame;
  long counter = 0;
  int which = 0;
  long offset = 0;
  int frame_count = (int)(videoCapture.get(cv::CAP_PROP_FRAME_COUNT));

  int real_counter = -1;
  std::cout << "Beginning histogram calculation.. Total number of frames: " << frame_count << std::endl;
  boost::progress_display show_progress(frame_count);
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
    if(counter % 5000 == 0){
      //std::cout << "progress: " << ((double)counter)*100/((double)frame_count) << "%" std::endl;
    }
    counter++;
    ++show_progress;
    offset = 0;
  }
  return output;
}

vecFC getVecFC(const std::string &storedSerialized) {
  std::ifstream ifs(storedSerialized);
  //std::cout << "trying to read filename: '" << storedSerialized << "'" << std::endl;
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
