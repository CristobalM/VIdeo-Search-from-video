//
// Created by cristobal on 09-04-18.
//

#include <sys/stat.h>
#include "InputFileControl.h"





inline bool fileExists(const std::string &filename){
  struct stat buffer;
  return (stat(filename.c_str(), &buffer) == 0);
}


vecFC InputFileControl::processOrRetrieveHData(const std::string &filename, const std::string &suffix) {
  vecFC out;
  std::string histo_file(filename+ "_"+ suffix + _HISTOGRAMS_TXT);
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
