#include "FaceDetector.h"
#include "facial_extractor_tools.h"

FaceDetector::FaceDetector(const string &path_to_model){
    dlib::deserialize(path_to_model) >> sp;
}

void FaceDetector::GetFaceLandmark(const dlib::rectangle &face, const cv::Mat &image,
                                     dlib::full_object_detection *shape) {

    dlib::array2d<dlib::rgb_pixel> dlib_image;
    assign_image(dlib_image, dlib::cv_image<dlib::rgb_pixel>(image));
    *shape = sp(dlib_image, face);
}