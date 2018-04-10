//
// Created by cristobal on 10-04-18.
//

#include <iostream>
#include <opencv2/highgui.hpp>
#include <fstream>
#include "src/FrameContainer.h"
#include "src/InputFileControl.h"
#include "src/SimilaritySearch.h"
#include "src/EuclideanDistance.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <regex>
#include <sys/stat.h>


int main(int argc, char **argv) {

  if(argc < 3){
    std::cout << "No estan los input necesarios: <Data_Video_Folder> <Query_Video_Folder>" << std::endl;
    return -1;
  }
  std::string data_folder(argv[1]);
  std::string query_folder(argv[2]);
  std::cout << "Reading directories: " <<  data_folder << ", " << query_folder << std::endl;

  boost::filesystem::path targetDirData(data_folder);
  boost::filesystem::recursive_directory_iterator iterData(targetDirData), eod;


  BOOST_FOREACH(boost::filesystem::path const& i, std::make_pair(iterData, eod)){
          if(boost::filesystem::is_regular_file(i)){
            std::string filename_current = i.string();
            std::string extension = boost::filesystem::extension(filename_current);
            if(extension == ".mpg" || extension==".mp4"){
              std::cout << "Loading file with name :" << filename_current << std::endl;

              bool discardAlreadySaved = false;
              InputFileControl inputFileControl(discardAlreadySaved);
              
              FrameIndexes frameIndexes = processOrRetrieveFrameIndexes(inputFileControl, filename_current, query_folder);
            }
          }
        }


  return 0;

}