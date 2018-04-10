//
// Created by cristobal on 10-04-18.
//

#include "QueryDistance.h"

double QueryDistance::compare(FrameContainer &A, FrameContainer &B) {
  std::vector<vmat> &histogramsA = A.getHistograms();
  std::vector<vmat> &histogramsB = B.getHistograms();
  double sum = 0;
  auto N = (int) histogramsA.size();
  auto M = (int) histogramsA[0].size();
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      cv::Mat &histA = histogramsA[i][j];
      cv::Mat &histB = histogramsB[i][j];
      sum += distance(histA, histB);
    }
  }
  return sum;
}
