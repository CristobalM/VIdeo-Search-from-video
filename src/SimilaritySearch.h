//
// Created by cristobal on 09-04-18.
//

#ifndef $_TARGET_NAME_SIMILARITYSEARCH_H
#define $_TARGET_NAME_SIMILARITYSEARCH_H


#include "FrameContainer.h"
#include "FrameIndexes.h"
#include "QueryDistance.h"

typedef std::vector<vecFC> vecvecFC;

class SimilaritySearch {
  std::shared_ptr<vecFC> data;
  std::shared_ptr<vecvecFC> queries;

  QueryDistance queryDistance;
public:
  SimilaritySearch(std::shared_ptr<vecFC> data, std::shared_ptr<vecvecFC> queries);
  SimilaritySearch(std::shared_ptr<vecFC> data, std::shared_ptr<vecvecFC> queries, QueryDistance &queryDistance);

  FrameIndexes search();

};


#endif //$_TARGET_NAME_SIMILARITYSEARCH_H
