//
// Created by cristobal on 09-04-18.
//

#include "ManhattanDistance.h"


double ManhattanDistance::distance(cv::Mat &A, cv::Mat &B) {
  assert(A.rows == B.rows && A.cols == B.cols);
  double sum = 0;
  for(int i = 0; i < A.rows; i++){
    for(int j = 0; j < A.cols; j++){
      sum += cv::abs(A.at<float>(i, j) - B.at<float>(i,j));
    }
  }
  return sum;
}
