//
// Created by cristobal on 09-04-18.
//

#include <boost/progress.hpp>
#include "SimilaritySearch.h"




SimilaritySearch::SimilaritySearch(QueryDistance *queryDistance) : queryDistance(queryDistance) {
}



void SimilaritySearch::search(FrameIndexes &frameIndexes, vecVC &queries) {
  //FrameIndexes frameIndexes(dataContainer);
  int dataFrameIndex = 0;
  vecFC &data = frameIndexes.getAssociatedVideo().video;
  double previous_progress = 0;
  std::cout << "Beginning similarity search for " << frameIndexes.getAssociatedVideo().filename << std::endl;
  boost::progress_display show_progress(data.size());
  for(auto &dataFrame: data){
    double min_dist = std::numeric_limits<double>::infinity();
    int min_dist_video_index = -1;
    int min_dist_in_video_index = -1;
    int queryVideoIndex = 0;
    for(auto &queryVideoContainer: queries){
      auto &queryVideo = queryVideoContainer.video;
      int queryFrameIndex = 0;
      for(auto &queryFrame: queryVideo){
        double frameDistance = queryDistance->compare(dataFrame, queryFrame);
        if(frameDistance < min_dist){
          min_dist = frameDistance;
          min_dist_video_index = queryVideoIndex;
          min_dist_in_video_index = queryFrameIndex;
        }
        queryFrameIndex++;
      }
      queryVideoIndex++;
    }

    frameIndexes.setNextIndex(min_dist_video_index, min_dist_in_video_index);

    dataFrameIndex++;
    /*
    if(dataFrameIndex%100 == 0){
      double current_progress = dataFrameIndex*100/data.size();
      if(current_progress- previous_progress >= 10){
        std::cout << "progress: " << current_progress << std::endl;
        previous_progress = current_progress;
      }
    }
     */
    ++show_progress;
  }
}