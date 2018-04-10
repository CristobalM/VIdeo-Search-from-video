//
// Created by cristobal on 07-04-18.
//

#ifndef $_TARGET_NAME_FRAMECONTAINER_H
#define $_TARGET_NAME_FRAMECONTAINER_H


//#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <memory>
#include <opencv2/videoio.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/binary_object.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

const int IMAGE_PARTS = 10;

typedef std::vector<cv::Mat> vmat;


class FrameContainer {


public:
  cv::Mat frame;
  std::vector<vmat> histograms;
  int real_frame_position;

  explicit FrameContainer();
  explicit FrameContainer(cv::Mat &frame, int real_frame_position);

  explicit FrameContainer(cv::Mat &frame, std::vector<vmat> &histograms, int real_frame_position);

  //std::vector<vmat> &getMiniImages();
  std::vector<vmat> &getHistograms();


  cv::Mat &getFrame();

  template<class Archive>
  friend void boost::serialization::serialize(Archive &, FrameContainer &, const unsigned int);

  cv::Mat getHistogram(cv::Mat &whichImage);

  int getRealFramePosition();


};

typedef std::vector<FrameContainer> vecFC;

vecFC getVecFC(cv::VideoCapture &videoCapture);

vecFC getVecFC(const std::string& storedSerialized);
void saveVecFC(const std::string& storedSerialized, vecFC & vecFc);



namespace boost{
  namespace serialization{
    template<class Archive>
    void serialize(Archive &ar, FrameContainer &frameContainer, const unsigned int version) {
      ar & frameContainer.frame;
      ar & frameContainer.histograms;
      ar & frameContainer.real_frame_position;
    }



    template<class Archive>
    void serialize(Archive &ar, cv::Mat &aMat, const unsigned int version) {
      int rows, cols, type;
      bool continuous;

      if (Archive::is_saving::value) {
        rows = aMat.rows;
        cols = aMat.cols;
        type = aMat.type();
        continuous = aMat.isContinuous();
      }

      ar & BOOST_SERIALIZATION_NVP(rows) & BOOST_SERIALIZATION_NVP(cols) & BOOST_SERIALIZATION_NVP(type) & BOOST_SERIALIZATION_NVP(continuous);

      if (Archive::is_loading::value)
        aMat.create(rows, cols, type);

      if (continuous) {
        const int data_size = rows * cols * static_cast<int>(aMat.elemSize());
        boost::serialization::binary_object mat_data(aMat.data, data_size);
        ar & BOOST_SERIALIZATION_NVP(mat_data);
      }
      else {
        const int row_size = cols * static_cast<int>(aMat.elemSize());
        for (int i = 0; i < rows; i++) {
          boost::serialization::binary_object row_data(aMat.ptr(i), row_size);
          std::string row_name("mat_data_row_" + std::to_string(i));
          ar & make_nvp(row_name.c_str(), row_data);
        }
      }
    }
  }
}


#endif //$_TARGET_NAME_FRAMECONTAINER_H
