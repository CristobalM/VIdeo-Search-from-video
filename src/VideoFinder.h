//
// Created by cristobal on 10-04-18.
//

#ifndef TAREA1MIR_VIDEOFINDER_H
#define TAREA1MIR_VIDEOFINDER_H


#include "FrameIndexes.h"
#include "InputFileControl.h"
#include "VideoFindResult.h"

typedef std::vector<VideoFindResult> vResult;

class VideoFinder {
  FrameIndexes& frameIndexes;
  InputFileControl& inputFileControl;
public:
  VideoFinder(FrameIndexes &frameIndexes, InputFileControl &inputFileControl);

  vResult find();
};


#endif //TAREA1MIR_VIDEOFINDER_H
