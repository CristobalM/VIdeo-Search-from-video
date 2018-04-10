//
// Created by cristobal on 09-04-18.
//

#ifndef $_TARGET_NAME_MANHATTANDISTANCE_H
#define $_TARGET_NAME_MANHATTANDISTANCE_H


#include "QueryDistance.h"

class ManhattanDistance: public QueryDistance {
public:
  ManhattanDistance() = default;

  double distance(cv::Mat &A, cv::Mat &B) override;

};


#endif //$_TARGET_NAME_MANHATTANDISTANCE_H
