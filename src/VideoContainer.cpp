//
// Created by cristobal on 09-04-18.
//

#include "VideoContainer.h"

VideoContainer::VideoContainer(const std::string &filename, vecFC &video) :
        filename(filename),
        video(video){
}

int VideoContainer::getNumberOfRealFrames() {
  return video[video.size()-1].real_frame_position - video[0].real_frame_position + 1;
}
