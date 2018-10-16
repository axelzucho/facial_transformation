#ifndef FACIAL_TRANSFORMATION_FACEALIGNER_H
#define FACIAL_TRANSFORMATION_FACEALIGNER_H

#include <dlib/image_processing/frontal_face_detector.h>
#include <opencv2/opencv.hpp>

class FaceAligner {
public:
    FaceAligner(const unsigned int size, const double left_eye_after);
    void AlignImage(const dlib::full_object_detection &shape, dlib::array2d<dlib::bgr_pixel>& image, cv::Mat *template_image);

private:
    unsigned int size_;
    double left_eye_after_;
};

#endif //FACIAL_TRANSFORMATION_FACEALIGNER_H
