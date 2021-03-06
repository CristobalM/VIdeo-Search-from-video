//
// Created by cristobal on 09-04-18.
//

#include "EuclideanDistance.h"

double EuclideanDistance::distance(cv::Mat &A, cv::Mat &B) {
  assert(A.rows == B.rows && A.cols == B.cols);
  double sum = 0;
  for(int i = 0; i < A.rows; i++){
    for(int j = 0; j < A.cols; j++){
      sum += cv::pow(A.at<float>(i, j) - B.at<float>(i,j), 2);
    }
  }
  return sum;
}
