#include "FaceDetector.h"
#include "facial_extractor_tools.h"

#include <dlib/opencv/cv_image.h>

FaceDetector::FaceDetector(const string &path_to_model){
    dlib::deserialize(path_to_model) >> sp;
}

void FaceDetector::GetFaceLandmark(const dlib::array2d<dlib::bgr_pixel> &image, const dlib::rectangle &face,
                                     dlib::full_object_detection *shape) {
    *shape = sp(image, face);
}