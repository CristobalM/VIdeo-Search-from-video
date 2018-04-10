//
// Created by cristobal on 09-04-18.
//

#ifndef $_TARGET_NAME_QUERYDISTANCE_H
#define $_TARGET_NAME_QUERYDISTANCE_H


#include "FrameContainer.h"

class QueryDistance {
public:
  double compare(FrameContainer &A, FrameContainer &B);
  virtual double distance(cv::Mat &A, cv::Mat &B) = 0;

};


#endif //$_TARGET_NAME_QUERYDISTANCE_H
