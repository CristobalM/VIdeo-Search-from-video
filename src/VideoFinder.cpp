//
// Created by cristobal on 10-04-18.
//

#include "VideoFinder.h"

const int STARTING_FRAME_ERROR_MARGIN = 10;
const int MAX_DISTANCE_BETWEEN_FRAMES = 15;
const int ERROR_MAX_TOLERANCE = 19;
const int LEFT_OFFSET = 5;

const int MAX_FRAME_DIFF_BETWEEN_VIDEOS = 30*5;


bool startingFrame(FrameIndexContainer &container){
  return container.framePosition >= 0 && container.framePosition <= STARTING_FRAME_ERROR_MARGIN;
}

bool inRightRange(FrameIndexContainer &current, FrameIndexContainer &previous){
  int dist = current.framePosition - previous.framePosition;
  return dist < MAX_DISTANCE_BETWEEN_FRAMES && dist > 0;
}

bool consistentVideoProgression(FrameIndexContainer &current, FrameIndexContainer &previous){
  return current.dstId == previous.dstId;
}


VideoFinder::VideoFinder(FrameIndexes &frameIndexes, InputFileControl &inputFileControl) :
        frameIndexes(frameIndexes),
        inputFileControl(inputFileControl) {
}

vResult VideoFinder::find() {
  vResult result;
  std::cout << std::endl << std::endl;
  //frameIndexes.print();
  std::cout << std::endl << std::endl;
  for(int i = 0; i < frameIndexes.indexes.size(); i++){
    FrameIndexContainer &starting = frameIndexes.indexes[i];
    if(!startingFrame(starting)){
      continue;
    }
    int error_num = 0;
    FrameIndexContainer &lastWorking = frameIndexes.indexes[i];
    int lastWorkingIndex = i;
    for(int j = i+1; error_num < ERROR_MAX_TOLERANCE && j < frameIndexes.indexes.size(); j++){
      FrameIndexContainer &current = frameIndexes.indexes[j];
      FrameIndexContainer &previous = frameIndexes.indexes[j-1];
      if(!inRightRange(current, lastWorking) || !consistentVideoProgression(current, starting)){
        error_num++;
        continue;
      }
      error_num = 0;
      lastWorking = frameIndexes.indexes[j];
      lastWorkingIndex = j;
    }

    VideoContainer &candidate_match = inputFileControl.getQueryVideoById(starting.dstId);
    VideoContainer &dataVideo = frameIndexes.getAssociatedVideo();

    int starting_real_frame = dataVideo.video[i].real_frame_position;
    int ending_real_frame = dataVideo.video[lastWorkingIndex].real_frame_position;

    int numberOfFramesDetected = ending_real_frame - starting_real_frame + 1;

    if(std::abs(candidate_match.getNumberOfRealFrames()-numberOfFramesDetected) < MAX_FRAME_DIFF_BETWEEN_VIDEOS){
      result.push_back(VideoFindResult(starting_real_frame, ending_real_frame, candidate_match.filename));
      i=lastWorkingIndex - LEFT_OFFSET;
    }
  }
  return result;
}
