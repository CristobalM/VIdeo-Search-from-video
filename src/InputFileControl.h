//
// Created by cristobal on 09-04-18.
//

#ifndef $_TARGET_NAME_INPUTFILECONTROL_H
#define $_TARGET_NAME_INPUTFILECONTROL_H


#include "FrameContainer.h"
#include "VideoContainer.h"
#include "FrameIndexes.h"

static const std::string HISTOGRAMS_BIN = "_histograms.bin";
static const std::string QUERY_STR = "_query_";
static const std::string DATA_STR = "_data_";

class InputFileControl {
  vecFC processOrRetrieveHData(const std::string &filename, const std::string &suffix);

  std::vector<VideoContainer> dataVideos;
  std::vector<VideoContainer> queryVideos;

  VideoContainer loadVideo(const std::string &filename, const std::string &type);

  bool discardOnLoaded;
public:
  InputFileControl();
  explicit InputFileControl(bool discardOnLoaded);


  void loadQueryVideo(const std::string &filename);
  void loadDataVideo(const std::string &filename);

  VideoContainer &getDataVideoById(int id);
  VideoContainer &getQueryVideoById(int id);
  vecVC &getQueryVideos();

  void saveFrameIndexes(const std::string &filenameToSave, FrameIndexes &frameIndexes);

  void clean();


};

void loadAllQueryVideosInFolder(const std::string& filename, InputFileControl &inputFileControl);
inline bool fileExists(const std::string &filename);
FrameIndexes processOrRetrieveFrameIndexes(InputFileControl &inputFileControl, const std::string& filename_current,
                                           const std::string& query_folder);
#endif //$_TARGET_NAME_INPUTFILECONTROL_H
