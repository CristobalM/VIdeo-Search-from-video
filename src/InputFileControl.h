//
// Created by cristobal on 09-04-18.
//

#ifndef $_TARGET_NAME_INPUTFILECONTROL_H
#define $_TARGET_NAME_INPUTFILECONTROL_H


#include "FrameContainer.h"

static const std::string _HISTOGRAMS_TXT = "_histograms.bin";

class InputFileControl {
  vecFC processOrRetrieveHData(const std::string &filename, const std::string &suffix);
public:
  InputFileControl() = default;



};


#endif //$_TARGET_NAME_INPUTFILECONTROL_H
