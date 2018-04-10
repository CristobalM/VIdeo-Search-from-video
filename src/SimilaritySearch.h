//
// Created by cristobal on 09-04-18.
//

#ifndef $_TARGET_NAME_SIMILARITYSEARCH_H
#define $_TARGET_NAME_SIMILARITYSEARCH_H


#include "FrameContainer.h"
#include "FrameIndexes.h"
#include "QueryDistance.h"
#include "VideoContainer.h"

typedef std::vector<vecFC> vecvecFC;

class SimilaritySearch {
  QueryDistance *queryDistance;
public:
  explicit SimilaritySearch(QueryDistance *queryDistance);

  void search(FrameIndexes &frameIndexes, vecVC &queries);

};


#endif //$_TARGET_NAME_SIMILARITYSEARCH_H
