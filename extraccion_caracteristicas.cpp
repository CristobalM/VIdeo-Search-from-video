//
// Created by cristobal on 09-04-18.
//

#include <iostream>
#include <opencv2/highgui.hpp>
#include <fstream>
#include "src/FrameContainer.h"
#include "src/InputFileControl.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <regex>


int main(int argc, char **argv) {

  if(argc < 3){
    std::cout << "No estan los input necesarios: <Data_Video_Folder> <Query_Video_Folder>" << std::endl;
    return -1;
  }
  std::string data_folder(argv[1]);
  std::string query_folder(argv[2]);
  std::cout << "Reading directories: " <<  data_folder << ", " << query_folder << std::endl;

  boost::filesystem::path targetDirData(data_folder);
  boost::filesystem::path targetDirQuery(query_folder);
  boost::filesystem::recursive_directory_iterator iterData(targetDirData), iterQuery(targetDirQuery), eod1, eod2;

  bool discardAlreadySaved = true;
  InputFileControl inputFileControl(discardAlreadySaved);

  boost::filesystem::recursive_directory_iterator bothIter[] = {iterData, iterQuery};
  boost::filesystem::recursive_directory_iterator bothEOD[] = {eod1, eod2};

  for(int l = 0; l < 2; l++){
    BOOST_FOREACH(boost::filesystem::path const& i, std::make_pair(bothIter[l], bothEOD[l])){
            if(boost::filesystem::is_regular_file(i)){
              std::string filename_current = i.string();
              std::string extension = boost::filesystem::extension(filename_current);
              if(extension == ".mpg" || extension==".mp4"){
                std::cout << "Seen file with name :" << filename_current << std::endl;
                if(l == 0){
                  inputFileControl.loadDataVideo(filename_current);
                }
                else{
                  inputFileControl.loadQueryVideo(filename_current);
                }

              }
            }
          }
  }

  return 0;

}