//
// Created by cristobal on 09-04-18.
//

#include <sys/stat.h>
#include <fstream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "InputFileControl.h"
#include "EuclideanDistance.h"
#include "SimilaritySearch.h"
#include "ManhattanDistance.h"


inline bool fileExists(const std::string &filename){
  struct stat buffer;
  return (stat(filename.c_str(), &buffer) == 0);
}


vecFC InputFileControl::processOrRetrieveHData(const std::string &filename, const std::string &suffix) {
  vecFC out;
  std::string histo_file(filename + suffix + HISTOGRAMS_BIN);
  if(fileExists(histo_file)){
    out = getVecFC(histo_file);
  }
  else{
    cv::VideoCapture capture;
    capture.open(filename);
    if(capture.isOpened()){
      out = getVecFC(capture);
      saveVecFC(histo_file, out);
    }
  }
  return out;
}

void loadAllQueryVideosInFolder(const std::string& filename, InputFileControl &inputFileControl){
  boost::filesystem::path targetDir(filename);
  boost::filesystem::recursive_directory_iterator iter(targetDir), eod;
  BOOST_FOREACH(boost::filesystem::path const& i, std::make_pair(iter, eod)){
    if(boost::filesystem::is_regular_file(i)){
      std::string filename_current = i.string();
      std::string extension = boost::filesystem::extension(filename_current);
      if(extension == ".mpg" || extension==".mp4"){
        //std::cout << "Loading file with name :" << filename_current << std::endl;

        inputFileControl.loadQueryVideo(filename_current);
      }
    }
  }
}

const std::string FRAME_INDEXES_STR = "_frame_indexes.bin";

FrameIndexes processOrRetrieveFrameIndexes(InputFileControl &inputFileControl, const std::string& filename_current,
                                           const std::string& query_folder) {

  inputFileControl.loadDataVideo(filename_current);
  loadAllQueryVideosInFolder(query_folder, inputFileControl);

  VideoContainer &dataContainer = inputFileControl.getDataVideoById(0);

  FrameIndexes result(dataContainer);

  std::string findx_file(filename_current + FRAME_INDEXES_STR);
  if(fileExists(findx_file)) {
    result.populateWithFile(findx_file);
  }
  else{

    EuclideanDistance euclideanDistance;
    //ManhattanDistance manhattanDistance;
    SimilaritySearch similaritySearch(&euclideanDistance);

    vecVC &queryVideos = inputFileControl.getQueryVideos();

    similaritySearch.search(result, queryVideos);
    result.saveToFile(findx_file);
  }

  return result;
}

VideoContainer InputFileControl::loadVideo(const std::string &filename, const std::string &type) {
  vecFC video = processOrRetrieveHData(filename, type);
  VideoContainer videoContainer(filename, video);
  return videoContainer;
}

void InputFileControl::loadQueryVideo(const std::string &filename) {
  VideoContainer loadedVideo = loadVideo(filename, QUERY_STR);
  if(!discardOnLoaded)
    queryVideos.push_back(loadedVideo);
}

void InputFileControl::loadDataVideo(const std::string &filename) {
  VideoContainer loadedVideo = loadVideo(filename, DATA_STR);
  if(!discardOnLoaded)
    dataVideos.push_back(loadedVideo );
}

VideoContainer &InputFileControl::getDataVideoById(int id) {
  assert(dataVideos.size() > id && id >= 0);
  return dataVideos[id];
}

VideoContainer &InputFileControl::getQueryVideoById(int id) {
  assert(queryVideos.size() > id && id >= 0);
  return queryVideos[id];
}

void InputFileControl::saveFrameIndexes(const std::string &filenameToSave, FrameIndexes &frameIndexes) {
  std::ofstream ofs(filenameToSave);
  boost::archive::binary_oarchive oa(ofs);
  oa << frameIndexes.indexes;
}

vecVC &InputFileControl::getQueryVideos() {
  return queryVideos;
}

InputFileControl::InputFileControl() : InputFileControl(false) {
}

InputFileControl::InputFileControl(bool discardOnLoaded) : discardOnLoaded(discardOnLoaded) {

}

void InputFileControl::clean() {
  dataVideos.clear();
  queryVideos.clear();
}
