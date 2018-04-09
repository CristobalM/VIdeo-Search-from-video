//
// Created by cristobal on 09-04-18.
//

#ifndef $_TARGET_NAME_EUCLIDEANDISTANCE_H
#define $_TARGET_NAME_EUCLIDEANDISTANCE_H


#include "QueryDistance.h"

class EuclideanDistance : public QueryDistance {
public:
  virtual EuclideanDistance() = default;
  double compare(FrameContainer &A, FrameContainer &B) override;


};


#endif //$_TARGET_NAME_EUCLIDEANDISTANCE_H
