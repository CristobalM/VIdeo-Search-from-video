//
// Created by cristobal on 09-04-18.
//

#ifndef $_TARGET_NAME_VIDEOCONTAINER_H
#define $_TARGET_NAME_VIDEOCONTAINER_H


#include "FrameContainer.h"

class VideoContainer {
public:
  std::string filename;
  vecFC video;
  VideoContainer(const std::string &filename, vecFC &video);

  int getNumberOfRealFrames();
};

typedef std::vector<VideoContainer> vecVC;


#endif //$_TARGET_NAME_VIDEOCONTAINER_H
