//
// Created by cristobal on 09-04-18.
//

#ifndef $_TARGET_NAME_FRAMEINDEXES_H
#define $_TARGET_NAME_FRAMEINDEXES_H


#include <vector>
#include "FrameIndexContainer.h"

class FrameIndexes {

public:
  std::vector<FrameIndexContainer> indexes;

  FrameIndexes();

  void setNextIndex(FrameIndexContainer & frameIndexContainer);
  void setNextIndex(int framePosition, int dstId);




};


#endif //$_TARGET_NAME_FRAMEINDEXES_H
