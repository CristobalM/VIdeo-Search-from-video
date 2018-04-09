//
// Created by cristobal on 09-04-18.
//

#include "FrameIndexes.h"

FrameIndexes::FrameIndexes() {

}

void FrameIndexes::setNextIndex(FrameIndexContainer &frameIndexContainer) {
  this->indexes.push_back(frameIndexContainer);
}

void FrameIndexes::setNextIndex(int framePosition, int dstId) {
  FrameIndexContainer frameIndexContainer(framePosition, dstId);
  setNextIndex(frameIndexContainer);
}
