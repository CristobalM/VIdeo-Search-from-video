//
// Created by cristobal on 10-04-18.
//

#include "VideoFindResult.h"

VideoFindResult::VideoFindResult(int starting_real_frame, int ending_real_frame, const std::string &filename) :
        starting_real_frame(starting_real_frame),
        ending_real_frame(ending_real_frame),
        filename(filename)  {
}
