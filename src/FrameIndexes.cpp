//
// Created by cristobal on 09-04-18.
//

#include <fstream>
#include "FrameIndexes.h"

FrameIndexes::FrameIndexes(VideoContainer& associatedVideo) : associatedVideo(associatedVideo) {
}

void FrameIndexes::setNextIndex(FrameIndexContainer& frameIndexContainer) {
  this->indexes.push_back(frameIndexContainer);
}

void FrameIndexes::setNextIndex( int dstId, int framePosition) {
  FrameIndexContainer frameIndexContainer(dstId, framePosition);
  setNextIndex(frameIndexContainer);
}

VideoContainer&FrameIndexes::getAssociatedVideo() {
  return associatedVideo;
}

void FrameIndexes::populateWithFile(const std::string &filename) {
  std::ifstream ifs(filename);
  std::cout << "trying to read filename: '" << filename << "'" << std::endl;
  if(!ifs){
    std::cout << "could not read ifs of " << filename << std::endl;
  }
  vecFIC out;
  boost::archive::binary_iarchive ia(ifs);
  ia & out;
  indexes = out;
}

void FrameIndexes::saveToFile(const std::string &filename) {
  std::ofstream ofs(filename);
  boost::archive::binary_oarchive oa(ofs);
  oa << indexes;
}

void FrameIndexes::print() {
  for(int i = 0; i < this->indexes.size(); i++){
    std::cout << i << ". \t" << this->indexes[i].dstId << "\t" << this->indexes[i].framePosition << std::endl;
  }

}
