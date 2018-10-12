#ifndef FACIAL_TRANSFORMATION_FACEDETECTOR_H
#define FACIAL_TRANSFORMATION_FACEDETECTOR_H

#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <opencv2/core/core.hpp>

using std::string;

class FaceDetector {
public:
    FaceDetector(const string& path_to_model);
    void GetFaceLandmark(const dlib::rectangle &face, const cv::Mat &image, dlib::full_object_detection* shape);

private:
    dlib::shape_predictor sp;
};

#endif //FACIAL_TRANSFORMATION_FACEDETECTOR_H
