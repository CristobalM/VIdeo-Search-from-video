//
// Created by cristobal on 10-04-18.
//

#ifndef TAREA1MIR_VIDEOFINDRESULT_H
#define TAREA1MIR_VIDEOFINDRESULT_H

#include <string>

class VideoFindResult {
public:
  int starting_real_frame;
  int ending_real_frame;
  std::string filename;
  VideoFindResult(int starting_real_frame, int ending_real_frame, const std::string &filename);
};


#endif //TAREA1MIR_VIDEOFINDRESULT_H
