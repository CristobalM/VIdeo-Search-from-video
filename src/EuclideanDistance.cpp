//
// Created by cristobal on 09-04-18.
//

#include "EuclideanDistance.h"

double euclideanDist(cv::Mat &A, cv::Mat &B){
  assert(A.rows == B.rows && A.cols == B.cols);
  double sum = 0;
  for(int i = 0; i < A.rows; i++){
    for(int j = 0; j < A.cols; j++){
      sum += cv::pow(A.at<uchar>(i, j) - B.at<uchar>(i,j), 2);
    }
  }
  return sum;
}


double EuclideanDistance::compare(FrameContainer &A, FrameContainer &B) {
  std::vector<vmat> &histogramsA = A.getHistograms();
  std::vector<vmat> &histogramsB = B.getHistograms();
  double sum = 0;
  auto N = (int) histogramsA.size();
  auto M = (int) histogramsA[0].size();
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      cv::Mat &histA = histogramsA[i][j];
      cv::Mat &histB = histogramsB[i][j];
      //double dist = cv::compareHist(mine, theirs, CV_COMP_CHISQR);
      sum += euclideanDist(histA, histB);
    }
  }
  return sum;
}
