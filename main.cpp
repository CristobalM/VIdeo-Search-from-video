#include <iostream>
#include <string>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sys/stat.h>
#include <fstream>
#include "src/FrameContainer.h"
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>

typedef boost::mt19937 RNGType;

inline bool fileExists(const std::string &filename){
  struct stat buffer;
  return (stat(filename.c_str(), &buffer) == 0);
}

void saveMat(const std::string &filename,  cv::Mat &m){
  std::ofstream ofs(filename);
  boost::archive::binary_oarchive oa(ofs);
  oa << m;
}

cv::Mat getMat(const std::string &filename){
  std::ifstream ifs(filename);
  boost::archive::binary_iarchive ia(ifs);
  cv::Mat output;
  ia >> output;
  return output;
}

vecFC processOrRetrieveHData(const std::string &filename, const std::string &suffix){
  vecFC out;
  std::string histo_file(filename+ "_"+suffix+"_histograms.txt");
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

int main(int argc, char **argv) {

  if(argc < 3){
    std::cout << "No estan los input necesarios: <Data> <Query>" << std::endl;
    return -1;
  }
  std::string data(argv[1]);
  std::string query(argv[2]);
  std::cout << data << ", " << query << std::endl;

  vecFC dataFrames = processOrRetrieveHData(data, "data");
  vecFC queryFrames = processOrRetrieveHData(query, "query");
  if(dataFrames.empty() || queryFrames.empty() || !fileExists(data) || !fileExists(query)){
    std::cout << "No se puede abrir uno de los archivos " << std::endl;
    return -1;
  }

  cv::VideoCapture videoCaptureData, videoCaptureQuery;
  videoCaptureData.open(data);
  videoCaptureQuery.open(query);

  double data_fps = videoCaptureData.get(CV_CAP_PROP_FPS);


  std::cout << "dataFrames size: " << dataFrames.size() << std::endl;
  std::cout << "queryFrames size: " << queryFrames.size() << std::endl;



  RNGType rng(std::time(0));
  boost::uniform_int<> zero_or_one(0,1);
  boost::variate_generator<RNGType, boost::uniform_int<> > toss(rng, zero_or_one);

  for(int j = 0; j < dataFrames.size(); j++){
    FrameContainer &currentDataFrame = dataFrames[j];

    int first = j;
    int matches = 0;

    //int check_first = (int)(std::sqrt(dataFrames.size())+1);

    int l = 0;
    int r = (int) std::min(dataFrames.size() - first, queryFrames.size());
    while(l < r){
      int m = (l+r)/2;
      double dist = queryFrames[m].distanceTo(dataFrames[first+m]);
      if(dist < 0.4){
        matches++;
      }
      int next = toss();
      if(next == 0){
        r = m;
      }
      else{
        l = m+1;
      }
    }



/*
    for (int k = 0; k < queryFrames.size() && k+first < dataFrames.size(); k++){
      double dist = queryFrames[k].distanceTo(dataFrames[first+k]);

        //std::cout << "distnace = " << dist << std::endl;


      if(dist < 0.4){
        matches++;
      }
    }
    */


    double total_denom = (double)queryFrames.size();
    double log_denom = std::log2(total_denom);

    double likelihood_video_section = ((double)matches) / (log_denom);
    if(likelihood_video_section > 0.7){
      //double seconds = j/3;
      double seconds = dataFrames[first].getRealFramePosition() / data_fps;
      std::cout << "found something at frame number " << first << " likelihood = " << likelihood_video_section << " second: " << seconds <<  std::endl;
      cv::Mat &frame = dataFrames[first].getFrame();
      cv::Mat sobelql;
      cv::Sobel(frame, sobelql,CV_16S, 1, 0);
      cv::imshow("frame number " + std::to_string(first), sobelql);
      j+= queryFrames.size();
    }
  }




  cv::waitKey(0);
  cv::waitKey(0);
  return 0;


}