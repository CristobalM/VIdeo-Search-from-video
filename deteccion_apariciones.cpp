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
#include "src/VideoFinder.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <regex>
#include <sys/stat.h>
#include <iomanip>
#include <regex>

double round_to_one(double x){
  return ((double)((int)((x+0.05)*10)))/((double)10);
}

std::string extractFileName(const std::string& inputString){
  std::regex file_name_no_path("([^\\/\\.]+)\\.");
  std::smatch matchReg;
  std::string data_show_string = inputString;
  if(std::regex_search(inputString, matchReg, file_name_no_path)){
    data_show_string = matchReg[1];
  }
  return data_show_string;
}

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


  std::ofstream outputFile;
  outputFile.open("DeteccionApariciones_output.txt");

  BOOST_FOREACH(boost::filesystem::path const& i, std::make_pair(iterData, eod)){
          if(boost::filesystem::is_regular_file(i)){
            std::string filename_current = i.string();
            std::string extension = boost::filesystem::extension(filename_current);
            if(extension == ".mpg" || extension==".mp4"){
              std::cout << "Loading file with name :" << filename_current << std::endl;

              bool discardAlreadySaved = false;
              InputFileControl inputFileControl(discardAlreadySaved);

              FrameIndexes frameIndexes = processOrRetrieveFrameIndexes(inputFileControl, filename_current, query_folder);

              VideoFinder videoFinder(frameIndexes, inputFileControl);
              vResult result = videoFinder.find();
              std::cout << "Number of results in file " << filename_current << ": " << result.size() << std::endl;
              double fps = 30;
              if(result.size() > 0){
                cv::VideoCapture videoCapture;
                videoCapture.open(filename_current);
                fps = videoCapture.get(cv::CAP_PROP_FPS);

              }

              std::string to_show_data_string = extractFileName(filename_current);

              for(auto &aResult: result){
                double secondsStart = ((double)aResult.starting_real_frame) / fps;
                secondsStart = round_to_one(secondsStart);
                double deltaSeconds = ((double)(aResult.ending_real_frame - aResult.starting_real_frame)) / (fps);
                deltaSeconds = round_to_one(deltaSeconds);
                std::string to_show_query_string_fname = extractFileName(aResult.filename);
                std::cout << to_show_data_string << "\t" << secondsStart << "\t"  <<  deltaSeconds  << "\t" << to_show_query_string_fname  << std::endl;
                outputFile << to_show_data_string << "\t" << secondsStart << "\t"  <<  deltaSeconds  << "\t" << to_show_query_string_fname  << std::endl;
              }
            }
          }
        }
  outputFile.close();

  return 0;

}