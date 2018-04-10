//
// Created by cristobal on 09-04-18.
//

#ifndef $_TARGET_NAME_FRAMEINDEXES_H
#define $_TARGET_NAME_FRAMEINDEXES_H


#include <vector>
#include "FrameIndexContainer.h"
#include "VideoContainer.h"
#include <boost/serialization/vector.hpp>

typedef std::vector<FrameIndexContainer> vecFIC;

class FrameIndexes {
  VideoContainer& associatedVideo;

public:
  vecFIC indexes;

  explicit FrameIndexes(VideoContainer& associatedVideo);

  void setNextIndex(FrameIndexContainer& frameIndexContainer);
  void setNextIndex(int dstId, int framePosition);

  VideoContainer &getAssociatedVideo();

  void populateWithFile(const std::string& filename);
  void saveToFile(const std::string& filename);

  void print();

};



#endif //$_TARGET_NAME_FRAMEINDEXES_H
