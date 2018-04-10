//
// Created by cristobal on 09-04-18.
//

#ifndef $_TARGET_NAME_FRAMEINDEXCONTAINER_H
#define $_TARGET_NAME_FRAMEINDEXCONTAINER_H

#include <string>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/binary_object.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

class FrameIndexContainer {
public:
  int dstId;
  int framePosition;
  FrameIndexContainer() = default;
  FrameIndexContainer(int framePosition, int dstId);



  template<class Archive>
  friend void boost::serialization::serialize(Archive &, FrameIndexContainer &, const unsigned int);

};


namespace boost {
  namespace serialization {
    template<class Archive>
    void serialize(Archive &ar, FrameIndexContainer &frameIndexContainer, const unsigned int version) {
      ar & frameIndexContainer.dstId;
      ar & frameIndexContainer.framePosition;
    }
  }
}

#endif //$_TARGET_NAME_FRAMEINDEXCONTAINER_H
