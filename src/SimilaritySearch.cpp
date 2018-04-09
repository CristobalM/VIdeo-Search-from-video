//
// Created by cristobal on 09-04-18.
//

#include "SimilaritySearch.h"
#include "EuclideanDistance.h"



SimilaritySearch::SimilaritySearch(std::shared_ptr<vecFC> data, std::shared_ptr<vecvecFC> queries) {
  EuclideanDistance euclideanDistance;
  SimilaritySearch(data, queries, euclideanDistance);
}

SimilaritySearch::SimilaritySearch(std::shared_ptr<vecFC> data, std::shared_ptr<vecvecFC> queries,
                                   QueryDistance &queryDistance) :
        data(data), queries(queries), queryDistance(queryDistance) {
}



FrameIndexes SimilaritySearch::search() {
  FrameIndexes frameIndexes;
  int dataFrameIndex = 0;
  for(auto  &dataFrame: *data){
    double min_dist = std::numeric_limits<double>::infinity();
    int min_dist_video_index = -1;
    int min_dist_in_video_index = -1;
    int queryVideoIndex = 0;
    for(auto  &queryVideo: *queries){
      int queryFrameIndex = 0;
      for(auto  &queryFrame: queryVideo){
        double frameDistance = queryDistance.compare(dataFrame, queryFrame);
        if(frameDistance < min_dist){
          min_dist = frameDistance;
          min_dist_in_video_index = queryFrameIndex;
          min_dist_video_index = queryVideoIndex;
        }
        queryFrameIndex++;
      }
      queryVideoIndex++;
    }

    frameIndexes.setNextIndex(min_dist_in_video_index, min_dist_video_index);

    dataFrameIndex++;
  }
  return frameIndexes;
}